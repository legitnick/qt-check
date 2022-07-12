import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.0 as Controlsv

ApplicationWindow{
    visible: true
       title: "Basic layouts"
       property int margin: 11
       width: mainLayout.implicitWidth + 2 * margin
       height: mainLayout.implicitHeight + 2 * margin
       minimumWidth: mainLayout.Layout.minimumWidth + 2 * margin
       minimumHeight: mainLayout.Layout.minimumHeight + 2 * margin

    ListView{

        anchors.fill: parent
        anchors.margins: margin
        required model
        delegate: Component{
        Loader{
        source:"Entry.qml"
        }
        }

    }

}

