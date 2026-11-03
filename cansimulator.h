#ifndef CANSIMULATOR_H
#define CANSIMULATOR_H

#include <QCanBusDevice>
#include <QObject>
#include <QTimer>

class CanSimulator : public QObject {
  Q_OBJECT

public:
  explicit CanSimulator(QObject *parent = nullptr);
  bool start(const QString &serialbus, const QString &interface);

private slots:
  void tick();

private:
  QCanBusDevice *m_device = nullptr;
  QTimer m_timer;
  int m_speed = 20;
  bool m_rising = false;
};

#endif
