/****************************************************************************
**
**
** This file is a part of the Qt Cpu Info project
**
**
****************************************************************************/

import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.1

ItemDelegate {
    id: delegate
    property int maxKeyColumnWidth: 150
    contentItem: Row {
        id: row
        height: valueLabel.height
        spacing: 10

        Label {
            id: keyLabel
            width: maxKeyColumnWidth + spacing
            text: key
            elide: Text.ElideRight
            horizontalAlignment: Text.AlignRight
        }

        Label {
            id: seperatorLabel
            text: qsTr(":")
        }

        Label {
            id: valueLabel
            text: value
            wrapMode: Text.Wrap
            width: parent.width - seperatorLabel.width - keyLabel.width - 2 * row.spacing
        }
    }
}
