import QtQuick 2.0
import GameComponents 1.0

Rectangle {
    width: 64
    height: 64
    border.color: "black"
    border.width: 2

    property Cell cell: null

    Rectangle {
        anchors.fill: parent
        anchors.margins: 2
        //visible: cell.isOpen & cell.haveMine
        color: { if (cell.isOpen) {
                    if (cell.haveMine) {
                        if (cell.isExploded() === false ){
                            "red"
                        }
                        else {
                            "green"
                        }
                    }
                }
            }

        Rectangle {
            id: cellrect
            color: "#c0c0c0"
            visible:  !cell.isOpen
            anchors.fill: parent
            anchors.margins: 2
            Text {
                text: text()
                anchors.centerIn: cellrect
                font.pixelSize: 50
                function text(){
                    switch (cell.mark){
                    case 0:
                        return ""
                    case 1:
                        return "!"
                    case 2:
                        return "?"
                    }
                }
            }
        }
    }


    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: {
            if (mouse.button & Qt.RightButton) {
               cell.toggleMark()
            }
            else {
                if (cell.isOpen){
                    cell.tryToOpenAround();
                }
                else {
                    cell.open();
                }
            }
        }
    }
}
