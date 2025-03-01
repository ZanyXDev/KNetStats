import QtQuick 2.15
import QtQuick.Controls 2.15 as QQC2
import QtQuick.Layouts 1.15
import common 1.0

Item{
    id:root

    property alias model:listView.model
    property string headerText
    property color textHeaderColor: "yellow"
    property color textItemColor: "black"
    property color backgroundHeaderColor: "darkblue"
    property color backgroundItemColor: "darkgrey"
    property color borderColor: "blue"
    property int deviceType
    property int spacing
    ListView{
        id: listView
        currentIndex: 1
        onCurrentIndexChanged: { console.log("currentIndex changed") }
        anchors.fill: parent
        spacing:  root.spacing
        delegate: deviceDelegate
        header: headerComponent
        highlight: highlightComponent
        //footer: footerComponent
    }

    Component{
        id:headerComponent
        ColumnLayout {
            width: ListView.view ? ListView.view.width : 0
            spacing:  (_small_width) ? __p.padding_amount_2x : __p.padding_amount
            QQC2.Label {
                Layout.fillWidth: true
                background: Rectangle {
                    anchors.fill: parent
                    radius: 4
                    border.color: root.borderColor
                    border.width: 2
                    color: root.backgroundHeaderColor
                }
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignTop
                color: root.textHeaderColor
                text:root.headerText
                font {
                    family: AppSingleton.droidFont.name
                    pointSize: AppSingleton.middleFontSize
                }
            }
            Item{
                Layout.fillWidth: true
            }

        }
    }

    Component{
        id:deviceDelegate
        RowLayout{
            width: ListView.view ? ListView.view.width : 0
            spacing:  root.spacing
            Item{ Layout.fillHeight: true }
            Image {
                id:itemImage
                Layout.alignment:  Qt.AlignHCenter | Qt.AlignVCenter
                smooth: true
                source: model.cardtype ? "qrc:/network-wired.svg" : "qrc:/network-wireless.svg"
                fillMode: Image.Pad
                sourceSize: Qt.size(32,32)
            }
            QQC2.Label {
                Layout.fillWidth: true
                background: Rectangle {
                    anchors.fill: parent
                    radius: 4
                    // border.color: root.borderColor
                    // border.width: 2
                    color: root.backgroundItemColor
                }
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignTop
                color: root.textItemColor
                text:model.interfacename
                font {
                    family: AppSingleton.droidFont.name
                    pointSize: AppSingleton.averageFontSize
                }
            }
        }
    }

    Component{
        id:highlightComponent
        Rectangle{
            radius: 4
            color: "lightblue"
            width: ListView.view ? ListView.view.width : 0
        }
    }
}
