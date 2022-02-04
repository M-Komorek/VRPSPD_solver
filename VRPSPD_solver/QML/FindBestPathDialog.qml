import QtQuick 2.0
import QtGraphicalEffects 1.12
import QtQuick.Controls 2.15

Rectangle {
    id: findBestPathDialog
    property string dialogText: ""
    signal okClicked()
    signal cancelClicked()

    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
    width: gv.width
    height: gv.height
    color: gv.colorBackgroundShadow

    GlobalValues {
        id: gv
    }

    Rectangle {
        id: backgroundRectangle
        width: 500
        height: 300
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        radius: gv.whiteCardRadius
        color: gv.colorWhite

        Text {
            id: dialogText
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 50
            width: parent.width - 50
            horizontalAlignment: Text.AlignHCenter
            text: findBestPathDialog.dialogText
            font.pixelSize: 24
            font.letterSpacing: 2
            font.weight: Font.Bold
            wrapMode: Text.WordWrap
        }

        Row {
            id: textFieldsRow
            height: 50
            spacing: 50
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: dialogText.bottom
            anchors.topMargin: 20

            TextField {
                id: warehouseX
                width: 150
                height: parent.height
                placeholderText: qsTr("Enter X")
                font.pixelSize: 16
                validator: IntValidator {}
            }

            TextField {
                id: warehouseY
                width: 150
                height: parent.height
                placeholderText: qsTr("Enter Y")
                font.pixelSize: 16
                validator: IntValidator {}
            }

        }

        Row {
            id: buttonsRow
            height: 50
            spacing: 50
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 40

            RoundButton {
                id: okButton
                anchors.top: parent.top
                width: 120
                height: 60
                radius: 5
                palette {
                    button: gv.colorGreen
                    buttonText: gv.colorWhite
                }
                font.pixelSize: 24
                text: qsTr("OK")
                onClicked: {
                    if (warehouseX.text !== "" && warehouseY.text !== "")
                    {
                        VRPSPD_solver.addWarehouse(warehouseX.text, warehouseY.text)
                        warehouseX.clear()
                        warehouseY.clear()
                        findBestPathDialog.okClicked()
                    }
                }

                DropShadow {
                    id: okButtonShadow
                    anchors.fill: okButton
                    source: okButton
                    horizontalOffset: 1
                    verticalOffset: 1
                    radius: 5.0
                    samples: 10
                    color: gv.colorBackgroundShadow
                }
            }

            RoundButton {
                id: cancelButton
                anchors.top: parent.top
                width: 120
                height: 60
                radius: 5
                palette {
                    button: gv.colorRed
                    buttonText: gv.colorWhite
                }
                font.pixelSize: 24
                text: qsTr("Cancel")
                onClicked: findBestPathDialog.cancelClicked()

                DropShadow {
                    id: cancelButtonShadow
                    anchors.fill: cancelButton
                    source: cancelButton
                    horizontalOffset: 1
                    verticalOffset: 1
                    radius: 5.0
                    samples: 10
                    color: gv.colorBackgroundShadow
                }
            }
        }
    }
}
