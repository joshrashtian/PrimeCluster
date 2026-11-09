#include "canreader.h"
#include "cansimulator.h"
#include "clusterdata.h"
#include "clustersim-global.h"
#include "mediadata.h"
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include <cstring>

bool simulator = false;

int main(int argc, char *argv[]) {

  QGuiApplication app(argc, argv);

  // bank for all our values
  ClusterData cluster;
  MediaData mediadata;
  // qt qml app engine to run the app itself
  QQmlApplicationEngine engine;
  // can it read values?
  CanReader reader(&cluster);

  // conditionals for rendering
  bool simulateMode = false;
  bool lowPerformance = false;
  bool map = true;

  QString socket = "vcan0";
  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "--simulate") == 0)
      simulateMode = true;
    if (strcmp(argv[i], "--low-performance") == 0)
      lowPerformance = true;
    if (strcmp(argv[i], "--disable-map") == 0)
      map = false;
    if (strcmp(argv[i], "--socket") == 0 && i + 1 < argc)
      socket = argv[++i];
  }

  if (simulateMode) {
    CanSimulator *sim = new CanSimulator(&app);
    qDebug() << "reader start:" << reader.start("virtualcan", "can0");
    qDebug() << "sim start:" << sim->start("virtualcan", "can0");

  } else {
    qDebug() << "reader start: " << reader.start("socketcan", socket);
  }
  engine.setInitialProperties({{"cluster", QVariant::fromValue(&cluster)},
                               {"media", QVariant::fromValue(&mediadata)}});

  engine.loadFromModule("Cluster", "Main");

  if (engine.rootObjects().isEmpty())
    return -1;
  return app.exec();
}
