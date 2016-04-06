import QtQuick 2.0
import GameComponents 1.0

Rectangle {
    property int size: 64
    width: size
    height: size
    border.color: "black"
    border.width: 2

    property Cell cell: null

    Rectangle {
        anchors.fill: parent
        anchors.margins: (size * 0.14) < 2 ? 2 : size * 0.04
        //visible: cell.isOpen & cell.haveMine
        color: { if (cell.isOpen === true) {
                    if (cell.haveMine === true) {
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
                text: {
                    switch (cell.mark){
                    case 0:
                        return ""
                    case 1:
                        return "!"
                    case 2:
                        return "?"
                    }
                }
                anchors.centerIn: cellrect
                font.pixelSize: size * 0.8
            }
        }
        Text {
            text: cell.minesAround
            visible: cell.isOpen && cell.minesAround !== 0
            anchors.centerIn: cellrect
            font.pixelSize: size * 0.8
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
