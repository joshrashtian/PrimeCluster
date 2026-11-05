#include "amsclient.h"

AMSClient::AMSClient(MediaData *media, QObject *parent)
    : BluetoothBaseClass(parent), m_media(media) {}

bool AMSClient::start() { return false; }

void AMSClient::onConnected() {}
void AMSClient::onDisconnected() {}
void AMSClient::onServiceDiscovered(const QBluetoothUuid &uuid) {
  Q_UNUSED(uuid);
}
void AMSClient::onServiceStateChanged(QLowEnergyService::ServiceState state) {
  Q_UNUSED(state);
}
void AMSClient::onCharacteristicChanged(const QLowEnergyCharacteristic &c,
                                        const QByteArray &value) {
  Q_UNUSED(c);
  Q_UNUSED(value);
}
void AMSClient::sendCommand(int commandId) { Q_UNUSED(commandId); }
