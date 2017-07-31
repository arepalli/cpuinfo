/****************************************************************************
**
**
** This file is a part of the Qt Cpu Info project
**
**
****************************************************************************/

import QtQuick 2.5
import QtQuick.Controls 2.1
import Backend 1.0

ListView {
    id: listView

    focus: true
    boundsBehavior: Flickable.StopAtBounds
    interactive: true

    section.property: "processor"
    section.criteria: ViewSection.FullString
    section.delegate: SectionDelegate {
        width: listView.width
    }

    delegate: CpuInfoListDelegate {
        id: delegate
        width: listView.width
    }

    model: CpuInfoModel {
        id: cpuInfoModel
    }

    ScrollBar.vertical: ScrollBar { }
}
