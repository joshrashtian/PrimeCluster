#ifndef AMSCLIENT_H
#define AMSCLIENT_H

#include "bluetoothbaseclass.h"
#include <QFile>
#include <QLowEnergyController>
#include <QLowEnergyService>
#include <QObject>

class MediaData;

class AMSClient : public BluetoothBaseClass {
  Q_OBJECT

  QML_ELEMENT
  QML_UNCREATABLE("AMSClient is not intended to be created directly")

public:
  explicit AMSClient(MediaData *media, QObject *parent = nullptr);
  bool start();
  Q_INVOKABLE void sendCommand(int commandId);

private slots:
  void onConnected();
  void onDisconnected();
  void onServiceDiscovered(const QBluetoothUuid &uuid);
  void onServiceStateChanged(QLowEnergyService::ServiceState state);
  void onCharacteristicChanged(const QLowEnergyCharacteristic &c,
                               const QByteArray &value);

private:
  MediaData *m_media = nullptr;
  QLowEnergyController *m_controller = nullptr;
  QLowEnergyService *m_service = nullptr;
};

#endif
