import QtQuick 2.15
import QtQuick.Controls 2.15 as QQC2
import QtQuick.Layouts 1.15
import common 1.0

FocusScope {
  id: root

  property alias model: listView.model
  property alias footer: listView.footer

  readonly property alias index: listView.currentIndex
  property string headerText
  property color textHeaderColor: "yellow"
  property color textItemColor: "black"
  property color backgroundHeaderColor: "darkblue"
  property color backgroundItemColor: "lightgrey"
  property color borderColor: "blue"
  property color highlightColor: "lightblue"
  property int deviceType
  property int spacing

  ListView {
    id: listView

    anchors.fill: parent
    spacing: root.spacing
    highlightFollowsCurrentItem: true
    clip: true
    focus: true
    keyNavigationEnabled: true // Enable key up and key down

    delegate: deviceDelegate
    header: headerComponent
    highlight: highlightComponent

    QQC2.ScrollBar.vertical: QQC2.ScrollBar {
      policy: listView.contentHeight > listView.height ? QQC2.ScrollBar.AlwaysOn : QQC2.ScrollBar.AlwaysOff
    }

    Keys.onUpPressed: listView.decrementCurrentIndex()
    Keys.onDownPressed: listView.incrementCurrentIndex()
  }

  Component {
    id: headerComponent
    ColumnLayout {
      width: ListView.view ? ListView.view.width : 0
      spacing: root.spacing

      QQC2.Label {
        id: headerLabel
        Layout.fillWidth: true
        background: Rectangle {
          anchors.fill: parent
          radius: 4
          border.color: root.borderColor
          border.width: 2
          color: root.backgroundHeaderColor
        }
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: root.textHeaderColor
        text: root.headerText
        font {
          family: AppSingleton.droidFont.name
          pointSize: AppSingleton.averageFontSize
        }
      }
      Item {
        Layout.fillWidth: true
      }
    }
  }

  Component {
    id: deviceDelegate
    RowLayout {
      id: deviceRowLayout
      property bool isCurrentItem: ListView.isCurrentItem && listView.activeFocus
      width: ListView.view ? ListView.view.width : 0
      spacing: root.spacing
      Item {
        Layout.fillHeight: true
      }
      Image {
        id: itemImage
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        smooth: true
        source: model.cardtype ? "qrc:/network-wired.svg" : "qrc:/network-wireless.svg"
        fillMode: Image.Pad
        sourceSize: Qt.size(36, 36)
      }
      QQC2.Label {
        Layout.fillWidth: true
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        color: root.textItemColor
        text: model.interfacename
        font {
          family: AppSingleton.droidFont.name
          pointSize: AppSingleton.averageFontSize
        }
        MouseArea {
          id: mA
          anchors.fill: parent
          onClicked: {
            listView.currentIndex = index
          }
        }
      }
      Item {
        Layout.fillHeight: true
      }
    }
  }

  Component {
    id: highlightComponent

    Rectangle {
      z: 2
      color: root.highlightColor
      opacity: 0.72
      y: listView.currentItem.y
      radius: 4
      width: ListView.view ? ListView.view.width : 0

      Behavior on y {
        SpringAnimation {
          spring: 3
          damping: 0.2
        }
      }
    }
  }
}
