import QtQuick 2.0
import QtQuick.Controls 2.0 as Controls
import QtQuick.Layouts 1.0
RowLayout {
    id: layout
    spacing: 6;
    width:parent.width;
    height: 200;
    Rectangle{

        Layout.fillWidth: true
        Layout.minimumWidth: 50
        Layout.preferredWidth: 100
        Layout.maximumWidth: 300
        Layout.minimumHeight: 150
    Controls.CheckBox {
        id:chk

        anchors.centerIn: parent;
    }
    }
    Rectangle{

        Layout.fillWidth: true
        Layout.minimumWidth: 50
        Layout.preferredWidth: 100
        Layout.maximumWidth: 300
        Layout.minimumHeight: 150
    Controls.Label{
        text:color

        anchors.centerIn: parent;
    }
    }
    Rectangle{

        Layout.fillWidth: true
        Layout.minimumWidth: 50
        Layout.preferredWidth: 100
        Layout.maximumWidth: 300
        Layout.minimumHeight: 150
    Controls.Label{
        text:name

        anchors.centerIn: parent;
    }
}
    Rectangle{

        Layout.fillWidth: true
        Layout.minimumWidth: 50
        Layout.preferredWidth: 100
        Layout.maximumWidth: 300
        Layout.minimumHeight: 150
    Controls.Label{
        text:number
        anchors.centerIn: parent;
    }
    }

}
