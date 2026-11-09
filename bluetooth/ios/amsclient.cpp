#include "amsclient.h"
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusMessage>
#include <QDBusMetaType>
#include <QDBusObjectPath>
#include <QDBusReply>
#include <QDebug>
#include <QMap>

using InterfaceMap = QMap<QString, QVariantMap>;
using ManagedObjects = QMap<QDBusObjectPath, InterfaceMap>;
Q_DECLARE_METATYPE(InterfaceMap)
Q_DECLARE_METATYPE(ManagedObjects)

static const QString kRemoteCommand = "9B3C81D8-57B1-4A8A-B8DF-0E56F7CA51C2";
static const QString kEntityUpdate = "2F7CABCE-808D-411F-9A0C-BB92BA96C102";
static const QString kEntityAttribute = "C6B2F38C-23AB-46D8-A6AB-A3A870BBD5D7";

AMSClient::AMSClient(MediaData *media, const QString &devicePath,
                     QObject *parent)
    : BluetoothBaseClass(parent), m_media(media), m_devicePath(devicePath) {
  qDBusRegisterMetaType<InterfaceMap>();
  qDBusRegisterMetaType<ManagedObjects>();
}

bool AMSClient::start() {
  if (!findCharacteristics()) {
    qWarning() << "AMS: characteristics not found";
    return false;
  }

  QDBusConnection::systemBus().connect(
      "org.bluez", m_entityUpdatePath, "org.freedesktop.DBus.Properties",
      "PropertiesChanged", this,
      SLOT(onCharacteristicChanged(QString, QVariantMap, QStringList)));

  QDBusInterface ch("org.bluez", m_entityUpdatePath,
                    "org.bluez.GattCharacteristic1",
                    QDBusConnection::systemBus());
  QDBusMessage reply = ch.call("StartNotify");
  if (reply.type() == QDBusMessage::ErrorMessage) {
    qWarning() << "AMS: StartNotify failed:" << reply.errorMessage();
    return false;
  }

  writeValue(m_entityUpdatePath, QByteArray::fromHex("02000102"));
  writeValue(m_entityUpdatePath, QByteArray::fromHex("000001"));
  qDebug() << "AMS: subscribed";
  return true;
}

bool AMSClient::findCharacteristics() {
  QDBusInterface om("org.bluez", "/", "org.freedesktop.DBus.ObjectManager",
                    QDBusConnection::systemBus());
  QDBusReply<ManagedObjects> reply = om.call("GetManagedObjects");
  if (!reply.isValid()) {
    qWarning() << "AMS: GetManagedObjects failed:" << reply.error().message();
    return false;
  }

  const ManagedObjects objects = reply.value();
  for (auto it = objects.cbegin(); it != objects.cend(); ++it) {
    const QString path = it.key().path();
    if (!path.startsWith(m_devicePath))
      continue;
    if (!it.value().contains("org.bluez.GattCharacteristic1"))
      continue;

    const QString uuid = it.value()["org.bluez.GattCharacteristic1"]["UUID"]
                             .toString()
                             .toUpper();
    if (uuid == kRemoteCommand)
      m_remoteCommandPath = path;
    else if (uuid == kEntityUpdate)
      m_entityUpdatePath = path;
    else if (uuid == kEntityAttribute)
      m_entityAttributePath = path;
  }
  return !m_entityUpdatePath.isEmpty() && !m_remoteCommandPath.isEmpty();
}

void AMSClient::writeValue(const QString &path, const QByteArray &value) {
  QDBusInterface ch("org.bluez", path, "org.bluez.GattCharacteristic1",
                    QDBusConnection::systemBus());
  QDBusMessage reply = ch.call("WriteValue", value, QVariantMap());
  if (reply.type() == QDBusMessage::ErrorMessage)
    qWarning() << "AMS: write failed:" << reply.errorMessage();
}

void AMSClient::onCharacteristicChanged(const QString &interface,
                                        const QVariantMap &changed,
                                        const QStringList &invalidated) {
  Q_UNUSED(invalidated);
  if (interface != "org.bluez.GattCharacteristic1" ||
      !changed.contains("Value"))
    return;

  const QByteArray v = changed.value("Value").toByteArray();
  if (v.size() < 3)
    return;

  const quint8 entity = static_cast<quint8>(v[0]);
  const quint8 attr = static_cast<quint8>(v[1]);
  const QString text = QString::fromUtf8(v.mid(3));

  if (entity == 2) {
    switch (attr) {
    case 0: m_media->setArtist(text); break;
    case 1: m_media->setAlbum(text); break;
    case 2: m_media->setTitle(text); break;
    case 3: m_media->setDuration(text.toDouble()); break;
    }
  } else if (entity == 0) {
    switch (attr) {
    case 0:
      m_media->setAppName(text);
      break;
    case 1: {
      const QStringList parts = text.split(',');
      if (parts.size() == 3) {
        m_media->setPlaying(parts[0].toInt() == 1);
        m_media->setElapsed(parts[2].toDouble());
      }
      break;
    }
    }
  }
}

void AMSClient::sendCommand(int command) {
  if (m_remoteCommandPath.isEmpty())
    return;
  writeValue(m_remoteCommandPath, QByteArray(1, static_cast<char>(command)));
}
