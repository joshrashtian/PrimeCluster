#include "clusterdata.h"
#include "clustersim-global.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
bool simulator = false;

int main(int argc, char *argv[]) {

  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;
  ClusterData cluster;

  engine.setInitialProperties({{"cluster", QVariant::fromValue(&cluster)}});

  engine.loadFromModule("Cluster", "Main");

  cluster.setGear(ClusterData::GearDrive);
  cluster.setSpeed(27);
  cluster.setMiles(67);
  if (engine.rootObjects().isEmpty())
    return -1;
  return app.exec();
}
