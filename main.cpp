
#include <QGuiApplication>

#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>
#include "dataobject.h"

//![0]
int main(int argc, char ** argv)
{
     QGuiApplication  app (argc, argv);

QList<QObject *> dataList = {
    new DataObject("Item 1","1", "red"),
    new DataObject("Item 2","2","green"),
    new DataObject("Item 3","3", "blue"),
    new DataObject("Item 4","4", "yellow")
};

QQuickView view;
view.setResizeMode(QQuickView::SizeRootObjectToView);
view.setInitialProperties({{ "model", QVariant::fromValue(dataList) }});
//![0]

view.setSource(QUrl("qrc:/main.qml"));
view.show();
    return app.exec();
}
