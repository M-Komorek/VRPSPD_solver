import QtQuick 2.0
import QtGraphicalEffects 1.12

Item {
    id: topItem
    property string text: "text"

    GlobalValues {
        id: gw
    }

    Text {
        id: clientListText
        anchors.verticalCenter: parent.verticalCenter
        horizontalAlignment: Text.AlignHCenter
        color: gw.colorBlack
        font.letterSpacing: 2
        font.pixelSize: 16
        font.weight: Font.Black
        text: topItem.text
    }
}
