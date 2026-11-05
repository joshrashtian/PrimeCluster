#include "canreader.h"
#include "clusterdata.h"
#include "decode_functions.h"
#include <QCanBus>
#include <QDebug>
#include <QDir>
#include <QDateTime>
CanReader::CanReader(ClusterData *cluster, QObject *parent)
    : BluetoothBaseClass(parent), m_cluster(cluster) {}

bool CanReader::start(const QString &plugin, const QString &interface) {
  QString errorString;
  m_device = QCanBus::instance()->createDevice(plugin, interface, &errorString);
  if (!m_device) {
    // Error handling goes here
    qDebug() << errorString;
    CanReader::setError(errorString);
    CanReader::setIcon(IconError);
    return 0;
  } else {
    m_device->setParent(this);
    qDebug() << "successfully connected device";
    connect(m_device, &QCanBusDevice::framesReceived, this,
            &CanReader::onFramesReceived);
    connect(m_device, &QCanBusDevice::errorOccurred, this,
            &CanReader::onErrorOccurred);
    m_logFile.setFileName(QDir::homePath() + "/can_unknown.log");
    if (m_logFile.open(QIODevice::Append | QIODevice::Text))
      m_log.setDevice(&m_logFile);
    else
      qWarning() << "Could not open CAN log:" << m_logFile.errorString();
    return m_device->connectDevice();
  }
}

void CanReader::onFramesReceived() {
  while (m_device->framesAvailable()) {
    const QCanBusFrame frame = m_device->readFrame();

    // TODO - switch statement for all frames
    //
    // placeholder cases logged from
    // https://github.com/appleguru/opendbc/blob/master/toyota_prius_2017_can1.dbc
    // with help from https://github.com/commaai/opendbc/tree/master/opendbc
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
    default:
      const quint32 id = frame.frameId();
      const QByteArray data = frame.payload();
      if (m_lastPayload.value(id) != data) {
        m_lastPayload[id] = data;
        m_log << QDateTime::currentDateTime().toString(Qt::ISODateWithMs) << " "
              << QString::number(id, 16).toUpper() << " " << data.toHex(' ')
              << "\n";
        m_log.flush();
      }
      break;
    }
  }
}

void CanReader::onErrorOccurred(QCanBusDevice::CanBusError error) {
  Q_UNUSED(error);
  qWarning() << "CAN error:" << m_device->errorString();
  setError(m_device->errorString());
  setIcon(IconError);
}
