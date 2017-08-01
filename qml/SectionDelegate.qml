/****************************************************************************
**
**
** This file is a part of the Qt Cpu Info project
**
**
****************************************************************************/

import QtQuick 2.7
import QtQuick.Controls 2.1

ToolBar {
    id: background

    Label {
        id: label
        text: qsTr("processor ") + section
        anchors.fill: parent
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
    }
}
