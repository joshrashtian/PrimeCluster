#include "canreader.h"
#include "clusterdata.h"
#include "clustersim-global.h"
#include "decode_functions.h"
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
bool simulator = false;

int main(int argc, char *argv[]) {

  QGuiApplication app(argc, argv);

  ClusterData cluster;

  CanReader reader(&cluster);
  if (!reader.start("virtualcan", "can0"))
    qWarning() << "CAN failed to start: " << reader.error();

  QQmlApplicationEngine engine;

  engine.setInitialProperties({{"cluster", QVariant::fromValue(&cluster)}});

  engine.loadFromModule("Cluster", "Main");

  cluster.setGear(ClusterData::GearDrive);
  cluster.setSpeed(
      PriusCan::decodeSpeed(QByteArray::fromHex("000000000028DD00")));
  cluster.setMiles(67);

  if (engine.rootObjects().isEmpty())
    return -1;
  return app.exec();
}
