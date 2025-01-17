import QtQuick 2.15
import QtQuick.Controls 2.15 as QQC2
import QtCharts 2.15

import common 1.0
import io.github.zanyxdev.knetstats 1.0

QQC2.Page {
    id:root
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

    ChartView{
        id:chartView
        anchors.top: parent.top
        anchors.left:parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 60

        animationOptions: ChartView.SeriesAnimations
        antialiasing: true
        theme: ChartView.ChartThemeDark
        property bool openGL: false
        property bool openGLSupported: false

        ValueAxis {
            id: axisX
            min: ChartDataModel.xAxis.x
            max: ChartDataModel.xAxis.y
            titleText: qsTr("Delta Time ms")
            tickCount: 10

        }
        ValueAxis {
            id: axisY
            min: ChartDataModel.yAxis.x
            max: ChartDataModel.yAxis.y

            titleText: qsTr("Speed KB/s")
        }
        LineSeries {
            id: cpuUsageSeries
            name: backend.userName
            axisX: axisX
            axisY: axisY
            useOpenGL: chartView.openGL
        }
    }


    QQC2.Button{
        id:tst
        anchors.top:chartView.bottom
        text: qsTr("Press Me")
        onClicked: {
             backend.userName = "text"
        }
    }


    Timer {
        id: refreshTimer
        interval: 1 / 60 * 1000 // 60 Hz
        running: false
        repeat: true
        onTriggered: {

        }
    }

    BackEnd {
        id: backend
    }
}
