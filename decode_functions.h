#ifndef DECODE_FUNCTIONS
#define DECODE_FUNCTIONS

#include "clusterdata.h"
#include "turnsignals.h"
#include <QByteArray>

namespace PriusCan {

// decoding
int decodeSpeed(const QByteArray &payload);
ClusterData::GearType decodeGear(const QByteArray &payload);
TurnSignals decodeTurnSignals(const QByteArray &payload);

// encoding
QByteArray encode_speed(int raw);
QByteArray encode_gear(ClusterData::GearType raw);
QByteArray encodeTurnSignals(TurnSignals s);
QByteArray buildMode21Request(quint8 pid);
QByteArray buildMode22Request(quint16 did);

double decodeFuelLiters(const QByteArray &p);
int decodeBatterySoc(const QByteArray &p);
int decodeOutsideTemp(const QByteArray &p);

// other
int decodeObdSpeed(const QByteArray &payload);
QByteArray buildPidRequest(quint8 pid);
} // namespace PriusCan

#endif // !DECODE_FUNCTIONS
