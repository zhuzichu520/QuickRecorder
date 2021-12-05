import QtQuick
import QtQuick.Window

Rectangle {

    id:root
    property alias source: view_image.source
    property alias text: view_text.text
    signal clicked
    width: 40
    height: 60
    color: mouse_area.containsMouse ? "#33FFFFFF" : "#00000000"
    radius: 5

    Image {
        id:view_image
        width: 24
        height: 24
        anchors{
            top: parent.top
            topMargin: 5
            horizontalCenter: parent.horizontalCenter
        }
    }

    Text {
        id:view_text
        color: "#FFFFFF"
        anchors{
            bottom: parent.bottom
            bottomMargin: 5
            horizontalCenter: parent.horizontalCenter
        }
    }

    MouseArea{
        id:mouse_area
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked:root.clicked()
    }

}
