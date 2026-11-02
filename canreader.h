#ifndef CANREADER_H
#define CANREADER_H

#include "bluetoothbaseclass.h"
#include <QCanBusDevice>
#include <QObject>

class ClusterData;

class CanReader : public BluetoothBaseClass {
  Q_OBJECT

   QML_ELEMENT
  QML_UNCREATABLE("CanReader is not intended to be created directly")

public:
  explicit CanReader(ClusterData *cluster, QObject *parent = nullptr);
  bool start(const QString &plugin, const QString &interface);

private slots:
  void onFramesReceived();
  void onErrorOccurred(QCanBusDevice::CanBusError error);

private:
  ClusterData *m_cluster = nullptr;
  QCanBusDevice *m_device = nullptr;
};

#endif
