#ifndef DECODE_FUNCTIONS
#define DECODE_FUNCTIONS

#include "clusterdata.h"
#include <QByteArray>

namespace PriusCan {

//decoding
int decodeSpeed(const QByteArray &payload);
ClusterData::GearType decodeGear(const QByteArray &payload);

//encoding
QByteArray encode_speed(int raw);
QByteArray encode_gear(ClusterData::GearType raw);
} // namespace PriusCan

#endif // !DECODE_FUNCTIONS
