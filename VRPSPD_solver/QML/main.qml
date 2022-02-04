import QtQuick 2.15
import QtQuick.Controls 1.4

ApplicationWindow {
    id: applicationWindow
    title: qsTr("VRPSPD solver")
    width: 1200
    height: 900
    visible: true

    HomeScreen {
        id: homeScreen
    }

    Component.onCompleted: console.log("DONE")
}
