#include "canreader.h"
#include "cansimulator.h"
#include "clusterdata.h"
#include "clustersim-global.h"
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <cstring>
bool simulator = false;

int main(int argc, char *argv[]) {

  QGuiApplication app(argc, argv);

  // bank for all our values
  ClusterData cluster;
  // qt qml app engine to run the app itself
  QQmlApplicationEngine engine;
  // can it read values?
  CanReader reader(&cluster);

  // conditionals for rendering
  bool simulateMode = false;
  bool lowPerformance = false;

  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "--simulate") == 0)
      simulateMode = true;
    if(strcmp(argv[i], "--low-performance") == 0) 
      lowPerformance = true;
  }

  if (simulateMode) {
    CanSimulator *sim = new CanSimulator(&app);
    qDebug() << "reader start:" << reader.start("virtualcan", "can0");
    qDebug() << "sim start:" << sim->start("virtualcan", "can0");

  } else {
    qDebug() << "reader start: " << reader.start("socketcan", "vcan0");
  }
  engine.setInitialProperties({{"cluster", QVariant::fromValue(&cluster)}});

  engine.loadFromModule("Cluster", "Main");

  if (engine.rootObjects().isEmpty())
    return -1;
  return app.exec();
}
