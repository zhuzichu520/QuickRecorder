import QtQuick
import QtQuick.Window
import QtQuick.Controls
import "../view"

Window {

    id:root
    property int startX
    property int startY
    property int endX
    property int endY
    property string maskColor: "#88000000"
    property string borderColor: "red"
    property string dragColor : "blue"
    property bool enableSelect: true

    property bool showMenu: false

    color: "#00000000"
    flags: Qt.WindowStaysOnTopHint
    transientParent: Window.window

    Image {
        id:image_screen
        anchors.fill: parent
    }

    ItemSelectArea{
        id:select_area
        onClickRighListener: {
            capture()
        }
    }

    Action {
        shortcut: "ESC"
        onTriggered: root.close()
    }

    function showWindow(){
        select_area.retrunParam()
        showFullScreen()
        image_screen.source = "image://screen/%1".arg(String(new Date().getTime()))
    }

    function capture(){
        tool.captureRect(
                    select_area.getAreaX(),
                    select_area.getAreaY(),
                    select_area.getAreaWidth(),
                    select_area.getAreaHeight()
                    )
    }

    Connections{
        target: tool
        function onCaptureResult(isSuccess){
            console.debug("截图成功")
            root.close()
        }
    }

}
