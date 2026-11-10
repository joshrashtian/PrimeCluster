#ifndef CANREADER_H
#define CANREADER_H

#include "bluetoothbaseclass.h"
#include <QByteArray>
#include <QCanBusDevice>
#include <QElapsedTimer>
#include <QFile>
#include <QHash>
#include <QList>
#include <QObject>
#include <QQmlEngine>
#include <QTextStream>
#include <QTimer>

class ClusterData;

struct PollRequest {
  quint32 requestId;
  QByteArray payload;
  int intervalMs;
  qint64 lastSentMs = 0;
};

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
  void poll();

private:
  void handleMode01Reply(quint32 sender, const QByteArray &payload);
  void handleMode21Reply(const QByteArray &payload);
  void handleMode22Reply(const QByteArray &payload);

  ClusterData *m_cluster = nullptr;
  QCanBusDevice *m_device = nullptr;
  QFile m_logFile;
  QTextStream m_log;
  QHash<quint32, QByteArray> m_lastPayload;
  QTimer m_pollTimer;
  QElapsedTimer m_clock;
  QList<PollRequest> m_requests;
};

#endif
