
#include <QGuiApplication>
#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>
#include <objectmodel.h>
//![0]
int main(int argc, char ** argv)
{
     QGuiApplication  app (argc, argv);

     qmlRegisterType<ObjectModel>("Backend", 1, 0, "ObjectModel");


QQuickView view;
view.setResizeMode(QQuickView::SizeRootObjectToView);
//![0]

view.setSource(QUrl("qrc:/main.qml"));
view.show();
    return app.exec();
}
