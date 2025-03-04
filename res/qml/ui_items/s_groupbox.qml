import QtQuick 2.15
import QtQuick.Controls 2.15 as QQC2
import QtQuick.Layouts 1.15

Item {
  id: root
  property alias font: innerLabel.font
  property int borderWidth: 2
  property int radius: 4
  property int borderMargins: 8
  property color borderColor: "darkgrey"
  property color labelBgrColor: "white"
  property color labelTextColor: "black"
  property string borderText: qsTr("GroupBox")
  property bool enabled: true
  property Component inlineContent: ContentItem {}

  component ContentItem: Text {
    text: qsTr("Not defined inline content Item")
    color: "red"
  }

  Rectangle {
    id: outerGroup
    anchors.fill: parent
    color: "transparent"
    Rectangle {
      id: innerRectangle
      anchors.fill: parent
      anchors.margins: root.borderMargins

      border {
        color: root.borderColor
        width: root.borderWidth
      }

      radius: root.radius
      color: "transparent"
      Loader {
        id: loader
        anchors.fill: parent
        sourceComponent: inlineContent
      }
    }
    QQC2.Label {
      id: innerLabel
      anchors.top: parent.top
      anchors.left: parent.left
      anchors.leftMargin: root.borderMargins * 4
      background: Rectangle {
        anchors.fill: parent
        color: root.labelBgrColor
      }
      horizontalAlignment: Text.AlignHCenter
      verticalAlignment: Text.AlignVCenter
      color: root.labelTextColor
      text: "  " + root.borderText + "  "
    }
  }
}
