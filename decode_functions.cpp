#include "decode_functions.h"
#include "clusterdata.h"
#include <QByteArray>
#include <QDebug>

namespace PriusCan {
int decodeSpeed(const QByteArray &payload) {
  qDebug() << payload.toHex(' ');
  int i = static_cast<quint8>(payload[5]);
  int j = static_cast<quint8>(payload[6]);

  int raw = (i << 8) | j;
  double kph = raw * 0.01;
  double mph = kph * 0.621371;
  return static_cast<int>(mph);
}

ClusterData::GearType decodeGear(const QByteArray &payload) {
  qDebug() << payload.toHex(' ');
  int value = (static_cast<quint8>(payload[5]) >> 4) & 0x0F;

  switch (value) {
  case 0:
    return ClusterData::GearParking;
  case 1:
    return ClusterData::GearReverse;
  case 2:
    return ClusterData::GearNeutral;
  case 3:
    return ClusterData::GearDrive;
  case 4: /*test this when recieve SD card*/
    return ClusterData::GearB;
  }

  return ClusterData::GearUnknown;
}

QByteArray encode_speed(int mph) {
  QByteArray payload(8, 0);
  int raw = qRound((mph / 0.621371) / 0.01);

  payload[5] = (raw >> 8) & 0xFF; // high byte
  payload[6] = raw & 0xFF;        // low byte
  return payload;
}

QByteArray encode_gear(ClusterData::GearType raw) {
  int value = 0;
  switch (raw) {
  case ClusterData::GearParking:
    value = 0;
    break;
  case ClusterData::GearReverse:
    value = 1;
    break;
  case ClusterData::GearNeutral:
    value = 2;
    break;
  case ClusterData::GearDrive:
    value = 3;
    break;
  case ClusterData::GearB:
    value = 4; break;
  default:
    value = -1; break;
  }

  if (value == -1) {
    qWarning() << "Gear is Invalid";
    return { };
  }

  QByteArray payload(8, 0);

  payload[5] = value << 4;
  return payload;
}
} // namespace PriusCan
