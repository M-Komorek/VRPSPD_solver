import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQml.Models 2.15
import QtGraphicalEffects 1.12
import QtQuick.Controls.Styles 1.4

Item {
    id: topItem
    property ListModel clientList: clientListViewModel

    GlobalValues {
        id: gv
    }

    Column {
        anchors.fill: parent
        spacing: 10

        Item {
            id: listViewHeader
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            height: 35

            Rectangle {
                id: border
                width: parent.width
                height: parent.height
                border.color: gv.colorBackground
                border.width: 2
                radius: 1

                Row {
                    anchors.fill: parent

                    BaseText { text: "ID" }
                    BaseText { text: "X" }
                    BaseText { text: "Y" }
                    BaseText { text: "D" }
                    BaseText { text: "P" }
                }
            }
        }

        ScrollView {
            id: scrollView
            anchors.left: parent.left
            anchors.right: parent.right
            height: parent.height - 100
            clip: true

            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            ScrollBar.vertical.policy: ScrollBar.AlwaysOff

            ListView {
                id: clientList
                model: clientListViewModel
                delegate: clientListViewDelegate
                spacing: 5
                add: Transition {
                    NumberAnimation { properties: "x,y"; from: 100; duration: 150 }
                }
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            height: 50
            spacing: 15

            TextField {
                id: clientX
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width / 5 - 12
                height: 35
                placeholderText: qsTr("Enter Client X")
                font.pixelSize: 16
                validator: IntValidator {}
            }

            TextField {
                id: clientY
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width / 5 - 12
                height: 35
                placeholderText: qsTr("Enter Client Y")
                font.pixelSize: 16
                validator: IntValidator {}
            }

            TextField {
                id: clientD
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width / 5 - 12
                height: 35
                placeholderText: qsTr("Enter Client D")
                font.pixelSize: 16
                validator: IntValidator {bottom: 0; top: 99;}
            }

            TextField {
                id: clientP
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width / 5 - 12
                height: 35
                placeholderText: qsTr("Enter Client P")
                font.pixelSize: 16
                validator: IntValidator {bottom: 0; top: 99;}
            }

            RoundButton {
                id: addClient
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width / 5 - 12
                height: 35
                radius: 5
                text: "Add Client"
                font.pixelSize: 18
                palette {
                    button: gv.colorGreen
                    buttonText: gv.colorWhite
                }

                onClicked: {
                    if (clientX.text !== "" &&
                        clientY.text !== "" &&
                        clientD.text !== "" &&
                        clientP.text !== "")
                    {
                        clientListViewModel.append(
                            {"clientId": clientListViewModel.count+1,
                             "clientXValue": clientX.text,
                             "clientYValue": clientY.text,
                             "clientDValue": clientD.text,
                             "clientPValue": clientP.text})
                        VRPSPD_solver.addClient(clientListViewModel.count,
                                                clientX.text,
                                                clientY.text,
                                                clientD.text,
                                                clientP.text)
                        clientX.text = ""
                        clientY.text = ""
                        clientD.text = ""
                        clientP.text = ""
                        clientList.positionViewAtEnd()
                    }
                }

                DropShadow {
                    id: addClientShadow
                    anchors.fill: addClient
                    source: addClient
                    horizontalOffset: 1
                    verticalOffset: 1
                    radius: 5.0
                    samples: 10
                    color: "#40000000"
                }
            }
        }
    }

    ListModel {
         id: clientListViewModel
    }

    Component {
        id: clientListViewDelegate

        Rectangle {
            id: border
            width: parent.width
            height: 35
            border.color: gv.colorBlack
            border.width: 1
            radius: 1

            Row {
                anchors.fill: parent

                BaseText { text: clientId }
                BaseText { text: clientXValue }
                BaseText { text: clientYValue }
                BaseText { text: clientDValue }
                BaseText { text: clientPValue }
            }
        }
    }
}
