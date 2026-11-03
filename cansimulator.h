#ifndef CANSIMULATOR_H
#define CANSIMULATOR_H

#include <QObject>
#include <QCanBusDevice>
#include <QTimer>

class CanSimulator : public QObject {
  Q_OBJECT

public:
  explicit CanSimulator(QObject *parent = nullptr);

  private slots:
    void tick();

private:
  QCanBusDevice * m_device = nullptr;
  QTimer m_timer;
};

#endif
