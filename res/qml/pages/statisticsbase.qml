import QtQuick 2.15
import QtQuick.Controls 2.15 as QQC2
import QtCharts 2.15
import QtQuick.Layouts 1.15

import common 1.0
import io.github.zanyxdev.knetstats 1.0


QQC2.Page {
    id: root
    property bool eggPage: false
    // Property thats used for sizing/margins/layout
    QtObject {
        id: __p
        readonly property int safe_padding: 24
        readonly property int padding_amount: 2
        readonly property int padding_amount_2x: 2 * __p.padding_amount
        readonly property int spacing: 8
        readonly property int spacing_x3: 3 * __p.spacing
        readonly property int cell_size: 64
    }
    Component.onCompleted: {
        AppSingleton.toLog(`StatisticBase page [${root.height}h,${root.width}w]`)
    }
    background: {
        null
    }



}
