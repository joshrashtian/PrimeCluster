#include "canreader.h"
#include "clusterdata.h"
#include "decode_functions.h"
#include <QCanBus>
#include <QDebug>
#include <QDir>
#include <QDateTime>

CanReader::CanReader(ClusterData *cluster, QObject *parent)
    : BluetoothBaseClass(parent), m_cluster(cluster) {
  connect(&m_pollTimer, &QTimer::timeout, this, &CanReader::poll);
}

bool CanReader::start(const QString &plugin, const QString &interface) {
  QString errorString;
  m_device = QCanBus::instance()->createDevice(plugin, interface, &errorString);
  if (!m_device) {
    qDebug() << errorString;
    setError(errorString);
    setIcon(IconError);
    return false;
  }

  m_device->setParent(this);
  connect(m_device, &QCanBusDevice::framesReceived, this,
          &CanReader::onFramesReceived);
  connect(m_device, &QCanBusDevice::errorOccurred, this,
          &CanReader::onErrorOccurred);

  m_logFile.setFileName(QDir::homePath() + "/can_unknown.log");
  if (m_logFile.open(QIODevice::Append | QIODevice::Text))
    m_log.setDevice(&m_logFile);
  else
    qWarning() << "Could not open CAN log:" << m_logFile.errorString();

  if (!m_device->connectDevice()) {
    qWarning() << "CAN connect failed:" << m_device->errorString();
    return false;
  }
  qDebug() << "CAN device connected on" << interface;
  m_pollTimer.start(100);
  return true;
}

void CanReader::poll() {
  m_device->writeFrame(QCanBusFrame(0x7DF, PriusCan::buildPidRequest(0x0D)));
}

void CanReader::handleObdReply(const QByteArray &payload) {
  if (payload.size() < 4)
    return;
  if (static_cast<quint8>(payload[1]) != 0x41)
    return;

  switch (static_cast<quint8>(payload[2])) {
  case 0x0D:
    m_cluster->setSpeed(PriusCan::decodeObdSpeed(payload));
    break;
  }
}

void CanReader::onFramesReceived() {
  while (m_device->framesAvailable()) {
    const QCanBusFrame frame = m_device->readFrame();
    if (frame.frameType() != QCanBusFrame::DataFrame)
      continue;

    switch (frame.frameId()) {
    case 0xB4:
      m_cluster->setSpeed(PriusCan::decodeSpeed(frame.payload()));
      break;
    case 0x127:
      m_cluster->setGear(PriusCan::decodeGear(frame.payload()));
      break;
    case 0x614:
      m_cluster->setTurnSignals(PriusCan::decodeTurnSignals(frame.payload()));
      break;
    case 0x7E8:
      handleObdReply(frame.payload());
      break;
    default: {
      const quint32 id = frame.frameId();
      const QByteArray data = frame.payload();
      if (m_lastPayload.value(id) != data) {
        m_lastPayload[id] = data;
        m_log << QDateTime::currentDateTime().toString(Qt::ISODateWithMs)
              << " " << QString::number(id, 16).toUpper() << " "
              << data.toHex(' ') << "\n";
        m_log.flush();
      }
      break;
    }
    }
  }
}

void CanReader::onErrorOccurred(QCanBusDevice::CanBusError error) {
  Q_UNUSED(error);
  qWarning() << "CAN error:" << m_device->errorString();
  setError(m_device->errorString());
  setIcon(IconError);
}
