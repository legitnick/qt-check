import QtQuick 2.12
import QtQuick.Window 2.12
import BppTable 0.1

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    property var fruitList: [
    {pkid: 1, name: "Apple", cost: 2.45},
    {pkid: 2, name: "Orange", cost: 3.45},
    {pkid: 3, name: "Banana", cost: 1.459},
    {pkid: 4, name: "Strawberry", cost: 1.1467}
];

CompGrid {
    id: bGrid
    anchors.fill: parent
    anchors.margins: 10

    dataHeight: 30

    Component {
        id: cellItem

        Rectangle {
            implicitHeight: bGrid.dataHeight
            color: bGrid.getCellBk(row, highlight)

            CellText {
                text: bGrid.formatDisplay(display, dataType, 2)
                horizontalAlignment: bGrid.getAlign(dataType)
            }

            CellClicker {
                grid: bGrid
            }
        }
    }

    cellDelegate: cellItem

    fromArray: [
        { role: "pkid", title: "ID", dataType: BTColumn.Int },
        { role: "name", title: "Name", minWidth: 100 },
        { role: "cost", title: "Cost", dataType: BTColumn.Dbl }
     ]
}

Component.onCompleted: {
    bGrid.fillFromJson(fruitList);
}
}
