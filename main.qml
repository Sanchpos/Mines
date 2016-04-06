import QtQuick 2.5
import GameComponents 1.0

Rectangle {
    id: window
    width: 800
    height: 600
    focus: true
    Keys.onPressed: {
        if (event.matches(StandardKey.New)) {
            field.startNewGame();
        }
    }
    Rectangle {
             radius: 10
             anchors.fill: parent
             Item {
                 id: panel
                 width: parent.width
                 height: parent.height * 0.1
                 Text {
                     property string seconds: timer.seconds
                     property string minutes: timer.minutes
                     property string time: {
                         if(field.state === 0) {
                             "00:00"
                         }
                         else {
                             minutes+":"+seconds
                         }
                     }

                     text: "Time: " + time
                     anchors.centerIn: parent
                     font.pixelSize: parent.height * 0.6
                     Timer {
                         id: timer
                         property int seconds: 0
                         property int minutes: 0
                         interval: 1000
                         repeat: true
                         running: {
                             if (field.state === 1) {
                                 "true"
                                 minutes = 0;
                                 seconds = 0;
                             }
                         }
                         onTriggered: {
                         if (seconds === 59) {
                            minutes += 1;
                            seconds = 0;
                         }
                            seconds = seconds + 1
                         }
                     }
                 }
             }

             Item {
                 id: cellContainer
                 anchors.top: panel.bottom
                 anchors.left: parent.left
                 anchors.right: parent.right
                 anchors.bottom: parent.bottom
                 anchors.margins: 10
                 property real windowProportion: width / height
                 property real fieldProportion: field.width * 1.0 / field.height
                 property real fixupFactor: windowProportion > fieldProportion ? 1 : windowProportion / fieldProportion
                 property int preferredSize: height / field.height * fixupFactor

                 Grid {
                     id: fieldItem
                     anchors.centerIn: parent

                     columns: field.width
                     Repeater {
                         id: cellRepeater
                         model: {
                            if (field.resetInProgress() === true) {
                                return 0
                            }
                            else {
                                return field.width * field.height
                            }
                         }

                         CellItem {
                             cell: field.cellAt(index % field.width, index / field.width)
                             size: cellContainer.preferredSize

                         }
                     }
                 }
             }
             Rectangle {
                color: "#c0c0c0"
                opacity: 0.7
                width: parent.width
                height: parent.height
                visible: {
                    switch(field.state) {
                    case 1:
                        return false
                    case 2:
                        return true
                    case 3:
                        return false
                        }
                    }
                }
                Text {
                text: "Game over"
                anchors.centerIn: parent
                font.pixelSize: 64
                visible: {
                    switch(field.state) {
                    case 1:
                        return false
                    case 2:
                        return true
                    case 3:
                        return false
                        }
                    }
                }
            }
        }

//    Rectangle {
//             radius: 10
//             anchors.fill: parent
//        Item {
//            id: cellContainer
//            anchors.fill: parent
//            anchors.margins: 10
//            property real windowProportion: width / height
//            property real fieldProportion: field.width * 1.0 / field.height
//            property real fixupFactor: windowProportion > fieldProportion ? 1 : windowProportion / fieldProportion
//            property int preferredSize: height / field.height * fixupFactor

//            Grid {
//                id: fieldItem
//                anchors.centerIn: parent
//                columns: field.width
//                Repeater {
//                    id: cellRepeater
//                    model: {
//                        if (field.resetInProgress() === true) {
//                            return 0
//                        }
//                        else {
//                            return field.width * field.height
//                        }
//                    }



//                    CellItem {
//                        cell: field.cellAt(index % field.width, index / field.width)
//                        size: cellContainer.preferredSize

//        //        Rectangle {
//        //            color: "#c0c0c0"
//        //            opacity: 0.7
//        //            width: parent.width
//        //            height: parent.height
//        //            visible: {
//        //                switch(field.state) {
//        //                case 1:
//        //                    return false
//        //                case 2:
//        //                    return false
//        //                case 3:
//        //                    return true
//        //                }
//        //            }
//        //        }
//        //        Text {
//        //            text: "Game over"
//        //            visible: {
//        //                switch(field.state) {
//        //                case 1:
//        //                    return false
//        //                case 2:
//        //                    return false
//        //                case 3:
//        //                    return true
//        //                }
//        //            }
//        //        }

//                    }
//                }
//            }
//        }
//    }
//}
