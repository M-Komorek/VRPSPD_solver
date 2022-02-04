import QtQuick 2.0
import QtGraphicalEffects 1.12

Item {
    id: topItem
    property string text: "text"

    GlobalValues {
        id: gw
    }

    Text {
        id: headerText
        font.letterSpacing: 2
        color: gw.colorTextGray
        font.pixelSize: 18
        font.weight: Font.Black
        text: topItem.text
        anchors.top: parent.top
        anchors.topMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 20
    }

    DropShadow {
        anchors.fill: headerText
        source: headerText
        horizontalOffset: 2
        verticalOffset: 1
        radius: 4.0
        samples: 10
        color: "#40000000"
    }
}
