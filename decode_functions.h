#ifndef DECODE_FUNCTIONS
#define DECODE_FUNCTIONS

#include "clusterdata.h"
#include <QByteArray>

namespace PriusCan {

int decodeSpeed(const QByteArray &payload);
ClusterData::GearType decodeGear(const QByteArray &payload);

} // namespace PriusCan

#endif // !DECODE_FUNCTIONS
