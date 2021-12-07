import QtQuick
import QtQuick.Window
import QtQuick.Controls
import Qt.labs.platform

import "../view"

ApplicationWindow {

    id:root
    width: 640
    height: 160
    visible: true
    title: qsTr("快录")
    maximumWidth: 640
    minimumWidth: 640
    maximumHeight: 160
    minimumHeight: 160

    color: "#111111"

    property int secondCount : 0

    //0停止，1播放，2暂停
    property int runStatus : 0

    SystemTrayIcon {
        visible: true
        icon.source: "qrc:/drawable/ic_logo.png"
        tooltip:"快录"
        onActivated:
            (reason)=>{
                if(reason===3){
                    root.show()
                    root.raise()
                    root.requestActivate()
                }
            }
        menu: Menu {
            MenuItem {
                text: "屏幕截图"
                onTriggered:window_capture.showWindow()
            }
            MenuItem {
                text: "退出"
                onTriggered: Qt.quit()
            }
        }
    }




    onRunStatusChanged: {
        switch(runStatus){
        case 0:
            timer_second.stop()
            secondCount = 0
            break
        case 1:
            timer_second.start()
            break
        case 2:
            timer_second.stop()
            break
        default:
            break
        }
    }

    Text {
        text: formatSeconds(secondCount)
        color: "#FFFFFF"
        font{
            pixelSize: 16
            bold: true
        }
        anchors{
            left: parent.left
            top: parent.top
            leftMargin: 20
            topMargin: 20
        }
    }

    Text {
        id: text_area
        text: qsTr("区域选择")
        color: "#FFFFFF"
        anchors{
            verticalCenter: parent.verticalCenter
            right: parent.right
            rightMargin: 30
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                window_select.showWindow()
            }
        }
    }

    ButtonImage{
        id:btn_start
        source: "qrc:/drawable/btn_record_start.png"
        anchors{
            top: parent.top
            left: parent.left
            topMargin: 50
            leftMargin: 40
        }
        text: "开始"
        visible: runStatus == 0
        onClicked: {
            start()
        }
    }

    ButtonImage{
        id:btn_restore_pause
        property bool isPause : runStatus == 2
        source: isPause ? "qrc:/drawable/btn_record_restore.png" : "qrc:/drawable/btn_record_pause.png"
        anchors{
            top: btn_start.top
            left: btn_start.left
        }
        text: isPause ? "继续" : "暂停"
        visible: runStatus != 0
        onClicked: {
            if(isPause){
                start()
            }else{
                pause()
            }
        }
    }

    ButtonImage{
        id:btn_stop
        source: "qrc:/drawable/btn_record_stop.png"
        anchors{
            top: btn_restore_pause.top
            left: btn_restore_pause.right
            leftMargin: 20
        }
        text: "停止"
        visible: runStatus != 0
        onClicked: {
            stop()
        }
    }

    Timer{
        id:timer_second
        interval: 1000
        repeat: true
        onTriggered: {
            secondCount++
        }
    }

    WindowSelectArea{
        id:window_select
    }

    WindowScreenCapture{
        id:window_capture
    }

    function start(){
        var path = "%1/%2.%3".
        arg(StandardPaths.standardLocations(StandardPaths.MoviesLocation)[0]).
        arg(String(new Date().getTime())).
        arg("mp4")
        console.debug(path)
        runStatus = 1
        var x = Math.ceil(window_select.getAreaX()/2)*2
        var y = Math.ceil(window_select.getAreaY()/2)*2
        var width = Math.ceil(window_select.getAreaWidth()/2)*2
        var height = Math.ceil(window_select.getAreaHeight()/2)*2
        console.debug("x:%1,y:%2,width:%3,height:%4".arg(x).arg(y).arg(width).arg(height))
        tool.start(path,x,y,width,height)
    }

    function stop(){
        runStatus = 0
        tool.stop()
    }

    function restore(){
        runStatus = 1

    }

    function pause(){
        runStatus = 2
    }

    function formatSeconds(seconds){
        let hour = Math.floor(seconds / 3600) >= 10 ? Math.floor(seconds / 3600) : '0' + Math.floor(seconds / 3600)
        seconds -= 3600 * hour
        let min = Math.floor(seconds / 60) >= 10 ? Math.floor(seconds / 60) : '0' + Math.floor(seconds / 60)
        seconds -= 60 * min
        let sec = seconds >= 10 ? seconds : '0' + seconds
        return hour + ':' + min + ':' + sec
    }

}
