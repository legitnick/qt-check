
#include <QDebug>
#include <QGuiApplication>
#include <QShortcut>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>
#include <objectmodel.h>
#include <qqml.h>
#include <qqmlcontext.h>
#include <qqmlengine.h>

//![0]
int main(int argc, char **argv) {
  QGuiApplication app(argc, argv);
  //ObjectModel model;
  qmlRegisterType<ObjectModel>("Backend", 1, 0, "ObjectModel");

  QQuickView view;
  view.setResizeMode(QQuickView::SizeRootObjectToView);
  //![0]

  view.setSource(QUrl("qrc:/main.qml"));
  view.show();
  return app.exec();
}
