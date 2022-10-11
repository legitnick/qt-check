import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import com.mycompany.messaging 1.0
    ListView{

        width:920;
        height: 1080;
        Component.onCompleted: console.log("listView loaded");
        y:10;
        id:main;
        model:ObjectModel{}
        delegate:Entry{}
}
