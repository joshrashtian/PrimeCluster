#include "canreader.h"
#include "clusterdata.h"
#include "decode_functions.h"
#include <QCanBus>
#include <QDateTime>
#include <QDebug>
#include <QDir>

CanReader::CanReader(ClusterData *cluster, QObject *parent)
    : BluetoothBaseClass(parent), m_cluster(cluster) {
  m_requests = {
      {0x7DF, PriusCan::buildPidRequest(0x0D), 100},
      {0x7D2, PriusCan::buildMode22Request(0x1F5B), 2000},
      {0x7C0, PriusCan::buildMode21Request(0x29), 5000},
      {0x7DF, PriusCan::buildPidRequest(0x46), 30000},
  };

  connect(&m_pollTimer, &QTimer::timeout, this, &CanReader::poll);
}

bool CanReader::start(const QString &plugin, const QString &interface) {
  QString errorString;
  m_device = QCanBus::instance()->createDevice(plugin, interface, &errorString);
  if (!m_device) {
    qWarning() << errorString;
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
  m_clock.start();
  m_pollTimer.start(50);
  return true;
}

void CanReader::poll() {
  const qint64 now = m_clock.elapsed();
  PollRequest *next = nullptr;
  qint64 mostOverdue = -1;

  for (PollRequest &r : m_requests) {
    const qint64 overdue = now - r.lastSentMs - r.intervalMs;
    if (overdue >= 0 && overdue > mostOverdue) {
      mostOverdue = overdue;
      next = &r;
    }
  }

  if (!next)
    return;

  next->lastSentMs = now;
  m_device->writeFrame(QCanBusFrame(next->requestId, next->payload));
}

void CanReader::handleMode01Reply(quint32 sender, const QByteArray &p) {
  if (p.size() < 4 || static_cast<quint8>(p[1]) != 0x41)
    return;

  switch (static_cast<quint8>(p[2])) {
  case 0x0D:
    if (sender == 0x7ED)
      m_cluster->setSpeed(PriusCan::decodeObdSpeed(p));
    break;
  case 0x46:
    if (sender == 0x7EA)
      m_cluster->setOutsideTemp(PriusCan::decodeOutsideTemp(p));
    break;
  }
}

void CanReader::handleMode21Reply(const QByteArray &p) {
  if (p.size() < 4 || static_cast<quint8>(p[1]) != 0x61)
    return;

  if (static_cast<quint8>(p[2]) == 0x29)
    m_cluster->setFuelLiters(PriusCan::decodeFuelLiters(p));
}

void CanReader::handleMode22Reply(const QByteArray &p) {
  if (p.size() < 5 || static_cast<quint8>(p[1]) != 0x62)
    return;

  const quint16 did =
      (static_cast<quint8>(p[2]) << 8) | static_cast<quint8>(p[3]);
  if (did == 0x1F5B)
    m_cluster->setBatterySoc(PriusCan::decodeBatterySoc(p));
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
    case 0x7EA:
    case 0x7EB:
    case 0x7ED:
    case 0x7EE:
    case 0x7EF:
      handleMode01Reply(frame.frameId(), frame.payload());
      break;
    case 0x7C8:
      handleMode21Reply(frame.payload());
      break;
    case 0x7DA:
      handleMode22Reply(frame.payload());
      break;
    default: {
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
}

void CanReader::onErrorOccurred(QCanBusDevice::CanBusError error) {
  Q_UNUSED(error);
  qWarning() << "CAN error:" << m_device->errorString();
  setError(m_device->errorString());
  setIcon(IconError);
}
