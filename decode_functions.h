#ifndef DECODE_FUNCTIONS
#define DECODE_FUNCTIONS

#include "clusterdata.h"
#include <QByteArray>
#include "turnsignals.h"

namespace PriusCan {

//decoding
int decodeSpeed(const QByteArray &payload);
ClusterData::GearType decodeGear(const QByteArray &payload);
TurnSignals decodeTurnSignals(const QByteArray &payload);

//encoding
QByteArray encode_speed(int raw);
QByteArray encode_gear(ClusterData::GearType raw);
QByteArray encodeTurnSignals(TurnSignals s);

//other
QByteArray buildPidRequest(quint8 pid);
} // namespace PriusCan

#endif // !DECODE_FUNCTIONS
