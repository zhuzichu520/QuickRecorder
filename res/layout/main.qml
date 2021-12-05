import QtQuick
import QtQuick.Window
import QtQuick.Controls

import "../view"

ApplicationWindow {
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
                window_capture.showWindow()
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
            window_select.capture()
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
        runStatus = 1
    }

    function stop(){
        runStatus = 0

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
