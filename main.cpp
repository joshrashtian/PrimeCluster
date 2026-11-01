#include "clustersim-global.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>

bool simulator = false;

int main(int argc, char *argv[]) {

  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;
  engine.loadFromModule("Cluster", "Main");
  if (engine.rootObjects().isEmpty())
    return -1;
  return app.exec();
}
