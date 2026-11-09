#ifndef AMSCLIENT_H
#define AMSCLIENT_H

#include "bluetoothbaseclass.h"
#include "mediadata.h"
#include <QByteArray>
#include <QObject>
#include <QQmlEngine>
#include <QString>
#include <QStringList>
#include <QVariantMap>

class AMSClient : public BluetoothBaseClass {
  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("Created in C++")

public:
  AMSClient(MediaData *media, const QString &devicePath,
            QObject *parent = nullptr);

  Q_INVOKABLE void sendCommand(int command);

public slots:
  bool start();
  void onCharacteristicChanged(const QString &interface,
                               const QVariantMap &changed,
                               const QStringList &invalidated);

private:
  bool findCharacteristics();
  void writeValue(const QString &path, const QByteArray &value);

  MediaData *m_media = nullptr;
  QString m_devicePath;
  QString m_remoteCommandPath;
  QString m_entityUpdatePath;
  QString m_entityAttributePath;
};

#endif
