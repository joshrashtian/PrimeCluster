#include "decode_functions.h"
#include "clusterdata.h"
#include <QByteArray>
#include <iostream>
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
} // namespace PriusCan
