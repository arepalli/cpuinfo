var defaultMaxKeyWidth = 150

function getMaxKeyWidth(list, parent)
{
    if (list === null || parent === null)
        return defaultMaxKeyWidth;

    var maxColumnWidth = 0;
     for (var i = 0; i < list.length; i++)
     {
        var data = list[i]

        if (data.length) {
            try {
                var textElement = Qt.createQmlObject(
                'import QtQuick 5.5;'
                + 'import QtQuick.Controls 2.1;'
                + 'Label {'
                + ' text: "' + data + '"; '
                + 'horizontalAlignment: Text.AlignRight '
                + '}',
                parent, "getMaxKeyWidth")
                //console.log(data)

                maxColumnWidth = Math.max(textElement.width, maxColumnWidth)
                textElement.destroy()
            } catch(e) {
                console.log(e)
                maxColumnWidth = defaultMaxKeyWidth;
                break;
            }
         }
     }
     return maxColumnWidth
}
