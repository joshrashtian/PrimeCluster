#include "clusterdata.h"
#include "clustersim-global.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "decode_functions.h"
bool simulator = false;

int main(int argc, char *argv[]) {

  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;
  ClusterData cluster;
  
  

  engine.setInitialProperties({{"cluster", QVariant::fromValue(&cluster)}});

  engine.loadFromModule("Cluster", "Main");

  cluster.setGear(ClusterData::GearDrive);
  cluster.setSpeed(PriusCan::decodeSpeed(QByteArray::fromHex("000000000028DD00")));
  cluster.setMiles(67);
  if (engine.rootObjects().isEmpty())
    return -1;
  return app.exec();
}
