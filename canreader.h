#ifndef CANREADER_H
#define CANREADER_H

#include "bluetoothbaseclass.h"
#include <QCanBusDevice>
#include <QFile>
#include <QTimer>
#include <QObject>
#include <QElapsedTimer>

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
  ClusterData *m_cluster = nullptr;
  QCanBusDevice *m_device = nullptr;
  QFile m_logFile;
  QTextStream m_log;
  QHash<quint32, QByteArray> m_lastPayload;
  void handleObdReply(const QByteArray &payload);
  QTimer m_pollTimer;

    void handleMode01Reply(quint32 sender, const QByteArray &payload);
    void handleMode21Reply(const QByteArray &payload);
    void handleMode22Reply(const QByteArray &payload);

    QList<PollRequest> m_requests;
    QElapsedTimer m_clock;
};

#endif
