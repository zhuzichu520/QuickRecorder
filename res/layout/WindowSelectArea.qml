import QtQuick
import QtQuick.Window
import QtQuick.Controls
import "../view"

Window {

    id:root
    color: "#00000000"
    flags: Qt.WindowStaysOnTopHint
    transientParent: Window.window

    ItemSelectArea{
        id:item_area
        onClickRighListener: {
            item_area.maskColor = "#00000000"
            item_area.showMenu = false
            root.flags = root.flags | Qt.WindowTransparentForInput
        }
    }

    function showWindow(){
        item_area.retrunParam()
        root.flags = root.flags &~ Qt.WindowTransparentForInput
        showFullScreen()
    }

    function getAreaX(){
        return item_area.getAreaX()
    }

    function getAreaY(){
        return item_area.getAreaY()
    }

    function getAreaWidth(){
        return item_area.getAreaWidth()
    }

    function getAreaHeight(){
        return item_area.getAreaHeight()
    }

}
