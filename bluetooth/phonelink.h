#ifndef PHONELINK_H
#define PHONELINK_H

#include <QObject>
#include <QQmlEngine>
#include <QString>
#include <QStringList>
#include <QVariantMap>

class PhoneLink : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("Created in C++")
  Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)

public:
  explicit PhoneLink(const QString &devicePath, QObject *parent = nullptr);

  bool connected() const { return m_connected; }

signals:
  void connectedChanged();

public slots:
  void onPropertiesChanged(const QString &interface, const QVariantMap &changed,
                           const QStringList &invalidated);

private:
  void setConnected(bool connected);
  void readInitialState();

  QString m_devicePath;
  bool m_connected = false;
};

#endif
