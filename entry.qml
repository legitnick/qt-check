import QtQuick 2.0
import QtQuick.Controls 2.0 as Controls
import QtQuick.Layouts 1.0

Rectangle{
    y:10;
    width:100;
    height:100;
    Rectangle{

        anchors.centerIn: parent;
        radius:6;

        border.color: "black"
        border.width: 2
        width:parent.width -5;
        height:  parent.height-5;

RowLayout {
    id: layout
    spacing:6;
    width:parent.width-10;

    anchors.centerIn: parent;
    Rectangle{

        Layout.fillWidth: true
        Layout.minimumWidth: 50
        Layout.preferredWidth: 100
        Layout.maximumWidth: 300
        Layout.minimumHeight: 90
    Controls.Label{
        id:indexlbl
        text:main.model.getN(index);
        anchors.centerIn: parent;
    }
    }

    Rectangle{

        Layout.fillWidth: true
        Layout.minimumWidth: 50
        Layout.preferredWidth: 100
        Layout.maximumWidth: 300
        Layout.minimumHeight: 90
    Controls.Label{
        text:main.model.getName(index);

        anchors.centerIn: parent;
    }
}
    Rectangle{

        Layout.fillWidth: true
        Layout.minimumWidth: 50
        Layout.preferredWidth: 100
        Layout.maximumWidth: 300
        Layout.minimumHeight: 90
    Rectangle{
        implicitWidth: 16;
        implicitHeight: 16;
        color:main.model.getColor(index)

        anchors.centerIn: parent;
    }
    }

    Rectangle{

        Layout.fillWidth: true
        Layout.minimumWidth: 50
        Layout.preferredWidth: 100
        Layout.maximumWidth: 300
        Layout.minimumHeight: 90
    Controls.CheckBox {
        id:chk
        indicator.width: 32;
        indicator.height: 32;
        checkState: main.model.getCheck(index);
        onCheckStateChanged:main.model.check(index);

        anchors.centerIn: parent;
    }
   }
}
}
}
