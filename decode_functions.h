#ifndef DECODE_FUNCTIONS
#define DECODE_FUNCTIONS

#include "clusterdata.h"
#include <QByteArray>

struct TurnSignals {
  bool left = false;
  bool right = false;
};

namespace PriusCan {

//decoding
int decodeSpeed(const QByteArray &payload);
ClusterData::GearType decodeGear(const QByteArray &payload);
TurnSignals decodeTurnSignals(const QByteArray &payload);

//encoding
QByteArray encode_speed(int raw);
QByteArray encode_gear(ClusterData::GearType raw);
QByteArray encodeTurnSignals(TurnSignals s);
} // namespace PriusCan

#endif // !DECODE_FUNCTIONS
