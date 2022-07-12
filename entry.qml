import QtQuick 2.0
import QtQuick.Controls 2.0 as Controls
import QtQuick.Layouts 1.0
RowLayout {
    id: layout
    spacing: 6;
    anchors.fill:parent;
    Layout.fillWidth: true;
    Controls.CheckBox {
        Layout.fillWidth: true;
        id:chk
    }
    Controls.Label{
        text:color

        Layout.fillWidth:true;
    width:180
    height:100

    }
    Controls.Label{
        text:name

        Layout.fillWidth: true;
    width:300
    height:100
    }
    Controls.Label{
        text:number

        Layout.fillWidth: true;
    width:100
    height:100
    }

}
