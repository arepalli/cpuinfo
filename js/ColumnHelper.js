function getMaxKeyWidth(list, parent)
{
    var maxColumnWidth = 0;
     for (var i = 0; i < list.length; i++)
     {
        var data = list[i]

        if (data.length) {
            var textElement = Qt.createQmlObject(
            'import QtQuick 2.5;'
            + 'import QtQuick.Controls 2.1;'
            + 'Label {'
            + ' text: "' + data + '"; '
            + 'horizontalAlignment: Text.AlignRight '
            + '}',
            parent, "getMaxKeyWidth")
            //console.log(data)
            maxColumnWidth = Math.max(textElement.width, maxColumnWidth)
            textElement.destroy()
         }
     }
     return maxColumnWidth
}
