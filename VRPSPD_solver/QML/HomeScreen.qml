import QtQuick 2.15
import QtGraphicalEffects 1.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4

Item {
    id: topItem
    anchors.fill: parent

    GlobalValues {
        id: gv
    }

    Rectangle {
        id: background
        anchors.fill: parent
        color: gv.colorBackground

        Item {
            id: clientListItem
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 20
            height: parent.height * 0.6 - 30

            Rectangle {
                id: clientListCardRectangle
                anchors.fill: parent
                color: gv.colorWhite
                radius: gv.whiteCardRadius

                HeadingText {
                    id: clientListCardText
                    width: parent.width
                    height: 30
                    text: qsTr("Client List")
                }

                ClientListCard {
                    id: clientListCard
                    anchors.top: clientListCardText.bottom
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: 20
                }
            }

            DropShadow {
                id: clientListCardShadow
                anchors.fill: clientListCardRectangle
                source: clientListCardRectangle
                horizontalOffset: 4
                verticalOffset: 4
                radius: 6.0
                samples: 10
                color: "#40000000"
            }
        }

        Item {
            id: resultItem
            anchors.top: clientListItem.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 20
            height: parent.height * 0.4 - 30

            Rectangle {
                id: resultCardRectangle
                anchors.fill: parent
                color: gv.colorWhite
                radius: gv.whiteCardRadius

                HeadingText {
                    id: resultCardText
                    width: parent.width
                    height: 30
                    text: qsTr("Best Routes")
                }

                Item {
                    id: scrollViewItem
                    anchors.top: resultCardText.bottom
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.right: runSolver.left
                    anchors.margins: 20

                    ScrollView {
                        id: scorllView
                        anchors.fill: parent
                        clip: true

                        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                        ScrollBar.vertical.policy: ScrollBar.AlwaysOff

                        ListView {
                            id: resultListView
                            model: routeListViewModel
                            spacing: 10
                            delegate: resultListViewDelegate
                        }
                    }
                }


                RoundButton {
                    id: runSolver
                    anchors.top: parent.top
                    anchors.topMargin: 50
                    anchors.right: parent.right
                    anchors.margins: 20
                    width: parent.width / 5 - 20
                    height: parent.height / 4
                    radius: 5
                    text: "Find Best Paths"
                    font.pixelSize: 24
                    palette {
                        button: gv.colorBlue
                        buttonText: gv.colorWhite
                    }

                    onClicked: findBestPathDialog.visible = true

                    DropShadow {
                        id: runSolverShadow
                        anchors.fill: runSolver
                        source: runSolver
                        horizontalOffset: 1
                        verticalOffset: 1
                        radius: 5.0
                        samples: 10
                        color: "#40000000"
                    }
                }

                RoundButton {
                    id: clearData
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 50
                    anchors.right: parent.right
                    anchors.margins: 20
                    width: parent.width / 5 - 20
                    height: parent.height / 4
                    radius: 5
                    text: "Clear"
                    font.pixelSize: 24
                    palette {
                        button: gv.colorRed
                        buttonText: gv.colorWhite
                    }
                    onClicked: {
                        routeListViewModel.clear()
                        clientListCard.clientList.clear()
                        VRPSPD_solver.clear()
                    }

                    DropShadow {
                        id: clearDataShadow
                        anchors.fill: clearData
                        source: clearData
                        horizontalOffset: 1
                        verticalOffset: 1
                        radius: 5.0
                        samples: 10
                        color: "#40000000"
                    }
                }
            }

            DropShadow {
                id: routeCardShadow
                anchors.fill: resultCardRectangle
                source: resultCardRectangle
                horizontalOffset: 4
                verticalOffset: 4
                radius: 6.0
                samples: 10
                color: "#40000000"
            }
        }
    }

    FindBestPathDialog {
        id: findBestPathDialog
        visible: false
        dialogText: qsTr("You have to add warehouse coordinates")
        onOkClicked: {
            var routeList = VRPSPD_solver.findBestRoutes()
            for (var i=0; i<routeList.length; i++)
            {
                routeListViewModel.append({"route": routeList[i]})
            }
            VRPSPD_solver.clear()
            visible = false
        }
        onCancelClicked: visible = false
    }

    ListModel {
         id: routeListViewModel
    }

    Component {
        id: resultListViewDelegate

        Rectangle {
            id: border
            width: parent.width
            height: 50
            border.color: gv.colorBlack
            border.width: 1
            radius: 1

            BaseText {
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                text: route
            }
        }
    }
}
