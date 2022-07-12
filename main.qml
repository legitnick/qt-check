import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.0 as Controlsv

    ListView{
        width:900;
        height: 1080;
        id:main;
        required model
        delegate:Entry{}

}

