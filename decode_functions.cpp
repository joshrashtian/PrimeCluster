#include "decode_functions.h"
#include "clusterdata.h"
#include <QByteArray>
#include <QDebug>

namespace PriusCan {
int decodeSpeed(const QByteArray &payload) {

  int i = static_cast<quint8>(payload[5]);
  int j = static_cast<quint8>(payload[6]);

  int raw = (i << 8) | j;
  double kph = raw * 0.01;
  double mph = kph * 0.621371;
  return static_cast<int>(mph);
}

ClusterData::GearType decodeGear(const QByteArray &payload) {

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

TurnSignals decodeTurnSignals(const QByteArray &payload) {
  if (payload.size() < 4)
    return {};
  // 29|2@0+  -> byte 29/8 = 3, start bit 29%8 = 5 (MSB, big-endian)
  //          -> 2 bits: bits 5..4, lowest bit = 5 - 2 + 1 = 4
  //          -> shift right 4, mask 0x03; '+' = unsigned
  int value = (static_cast<quint8>(payload[3]) >> 4) & 0x03;

  TurnSignals s;
  s.left = (value == 1);
  s.right = (value == 2);

  return s;
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
    value = 4;
    break;
  default:
    value = -1;
    break;
  }

  if (value == -1) {
    qWarning() << "Gear is Invalid";
    return {};
  }

  QByteArray payload(8, 0);

  payload[5] = value << 4;
  return payload;
}

QByteArray encodeTurnSignals(const TurnSignals s) {
  int value = 3;
  if (s.left)
    value = 1;
  if (s.right)
    value = 2;

  QByteArray payload(8, 0);
  payload[3] = value << 4;
  return payload;
}

int decodeObdSpeed(const QByteArray &payload)
{
    int kph = static_cast<quint8>(payload[3]);
    return qRound(kph * 0.621371);
}

QByteArray buildPidRequest(quint8 pid)
{
    QByteArray payload(8, 0);
    payload[0] = 0x02;   // 2 bytes follow
    payload[1] = 0x01;   // mode 01: current data
    payload[2] = pid;
    return payload;
}

} // namespace PriusCan
