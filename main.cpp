#include "canreader.h"
#include "cansimulator.h"
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
  CanSimulator sim;
    QQmlApplicationEngine engine;

qDebug() << "sim start:" << sim.start("virtualcan", "can0");
qDebug() << "reader start:" << reader.start("virtualcan", "can0");

  engine.setInitialProperties({{"cluster", QVariant::fromValue(&cluster)}});

  engine.loadFromModule("Cluster", "Main");

  if (engine.rootObjects().isEmpty())
    return -1;
  return app.exec();
}
