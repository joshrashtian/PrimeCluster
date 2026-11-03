#include "cansimulator.h"
#include "decode_functions.h"
#include <QCanBus>
#include <QCanBusFrame>
#include <QDebug>
#include <QObject>
#include <QTimer>
CanSimulator::CanSimulator(QObject *parent) : QObject(parent) {
  connect(&m_timer, &QTimer::timeout, this, &CanSimulator::tick);
}

bool CanSimulator::start(const QString &serialbus, const QString &interface) {
  QString errorString;
  m_device =
      QCanBus::instance()->createDevice(serialbus, interface, &errorString);

  if (!m_device) {
    qWarning() << "Simulator Error:" << errorString;
    return false;
  }

  m_device->setParent(this);

  connect(m_device, &QCanBusDevice::stateChanged, this,
          [this](QCanBusDevice::CanBusDeviceState state) {
          qDebug() << "sim state:" << state;
            if (state == QCanBusDevice::ConnectedState)
              m_timer.start(100);
          });

  return m_device->connectDevice();
}

void CanSimulator::tick() {


  if(m_rising) {
    m_speed += 1;
  }
  else {
    m_speed -= 1;
  }

  if(m_speed == 80) {
    m_rising = false;
  }

  if(m_speed == 10) {
    m_rising = true;
  }

  QByteArray speedPayload = PriusCan::encode_speed(m_speed);
  QByteArray gearPayload = PriusCan::encode_gear(ClusterData::GearDrive);
  m_device->writeFrame(QCanBusFrame(0xB4, speedPayload));
  if (!gearPayload.isEmpty())
        m_device->writeFrame(QCanBusFrame(0x127, gearPayload));}
