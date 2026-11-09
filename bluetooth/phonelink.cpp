#include "phonelink.h"
#include <QDBusInterface>
#include <QDBusReply>
#include <QDBusVariant>
#include <QDebug>

PhoneLink::PhoneLink(const QString &devicePath, QObject *parent)
    : QObject(parent), m_devicePath(devicePath) {
  QDBusConnection::systemBus().connect(
      "org.bluez", m_devicePath, "org.freedesktop.DBus.Properties",
      "PropertiesChanged", this,
      SLOT(onPropertiesChanged(QString, QVariantMap, QStringList)));
}

void PhoneLink::onPropertiesChanged(const QString &interface,
                                    const QVariantMap &changed,
                                    const QStringList &) {
  if (interface != "org.bluez.Device1")
    return;
  if (changed.contains("Connected"))
    setConnected(changed.value("Connected").toBool());
}

void PhoneLink::readInitialState() {
  QDBusInterface props("org.bluez", m_devicePath,
                       "org.freedesktop.DBus.Properties",
                       QDBusConnection::systemBus());

  QDBusReply<QDBusVariant> reply =
      props.call("Get", "org.bluez.Device1", "Connected");

  if (reply.isValid())
    setConnected(reply.value().variant().toBool());
  else
    qWarning() << "PhoneLink: could not read state:" << reply.error().message();
}

void PhoneLink::setConnected(bool connected) {
  if (m_connected == connected)
    return;
  m_connected = connected;
  qDebug() << "Phone connected:" << m_connected;
  emit connectedChanged();
}
