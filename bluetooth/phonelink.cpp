#include <QDBusConnection>
#include <QVariantMap>
#include "phonelink.h"

PhoneLink::PhoneLink(QObject *parent) : QObject(parent)
{
    QDBusConnection::systemBus().connect(
        "org.bluez",
        "/org/bluez/hci0/dev_20_46_3A_08_9E_CD",
        "org.freedesktop.DBus.Properties",
        "PropertiesChanged",
        this,
        SLOT(onPropertiesChanged(QString, QVariantMap, QStringList)));
}

void PhoneLink::onPropertiesChanged(const QString &interface,
                                    const QVariantMap &changed,
                                    const QStringList &)
{
    if (interface != "org.bluez.Device1")
        return;
    if (changed.contains("Connected"))
        setConnected(changed.value("Connected").toBool());
}
