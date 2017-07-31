/****************************************************************************
**
**
** This file is a part of the Qt/Qml Cpu Info project
**
**
****************************************************************************/

import QtQuick 2.7
import QtQuick.Controls 2.1

ApplicationWindow {
    id: window
    visible: true
    property int processorCount: cpuInfoView.count/26 //TODO: set this count correctly

    width: 600
    height: 480

    title: qsTr("Cpu Info")

    CpuInfoView {
        id: cpuInfoView
        anchors.fill: parent
        width: parent.width - 20
        height: parent.height
        highlightMoveVelocity: 1000

        onContentYChanged: {
            if (!flicking)
                return;

            var currentIndexAtTop = indexAt(1, contentY)
            if (processorCount > 0 && count > 0 && currentIndexAtTop >= 0)
                procSelectionComboBox.currentIndex = (currentIndexAtTop+1) / (count / processorCount);
        }
    }

    ComboBox {
        id: procSelectionComboBox
        model: processorModel()
        opacity: 0.75
        anchors.margins: 10
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        onActivated: {
            if (processorCount > 0)
                cpuInfoView.currentIndex = currentIndex * cpuInfoView.count / processorCount;
        }
        function processorModel(a) {
            var procModel = [];
            for (var i = 0; i < processorCount; i++)
                procModel.push("processor " + i);

            return procModel;
        }
    }
}
