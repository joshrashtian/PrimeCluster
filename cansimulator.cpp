#include "cansimulator.h"
#include <QTimer>
#include <QObject>
  
CanSimulator::CanSimulator(QObject * parent) : QObject(parent) {
  connect(&m_timer, &QTimer::timeout, this, &CanSimulator::tick
    );
}

void CanSimulator::tick() {
    
}
