import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.0
import com.mycompany.messaging 1.0

    ListView{
        Component.onCompleted: console.log("listView loaded");
        y:10;
        width:900;
        height: 1080;
        id:main;
        model:ObjectModel{}
        delegate:Entry{}

}

