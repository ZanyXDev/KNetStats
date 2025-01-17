import QtQuick 2.15
import QtQuick.Controls 2.15 as QQC2
import QtQuick.Layouts 1.15

import common 1.0

QQC2.Page {
  id: root
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
  // ----- Signal handlers
  Component.onCompleted: {
    AppSingleton.toLog(`ConfigureBase page [${root.height}h,${root.width}w]`)
  }
  background: {
    null
  }
  // ----- Visual children
  GridLayout {
    id: _grid
    anchors.fill: parent
    anchors.margins: __p.safe_padding
    columnSpacing: __p.spacing
    rowSpacing: __p.spacing
    columns: 8
    rows: 6

    Rectangle {
      id: interfaceList
      Layout.row: 0
      Layout.column: 0
      Layout.columnSpan: 3
      Layout.rowSpan: 4
      Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
      Layout.fillHeight: true
      Layout.fillWidth: true
      Layout.preferredWidth: 3
      Layout.preferredHeight: 5
      color: "green"
      opacity: 0.8
      //padding: (_small_width) ? __p.padding_amount_2x : __p.padding_amount
    }
    Rectangle {
      id: interfaceListRefresh
      Layout.row: 4
      Layout.column: 0
      Layout.columnSpan: 3
      Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
      Layout.fillHeight: true
      Layout.fillWidth: true
      Layout.preferredWidth: 3
      Layout.preferredHeight: 1
      color: "brown"
      opacity: 0.8
      //padding: (_small_width) ? __p.padding_amount_2x : __p.padding_amount
    }
    Rectangle {
      id: emptyBlock
      Layout.row: 5
      Layout.column: 0
      Layout.columnSpan: 3
      Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
      Layout.fillHeight: true
      Layout.fillWidth: true
      Layout.preferredWidth: 3
      Layout.preferredHeight: 1
      color: "darkgreen"
      opacity: 0.8
      //padding: (_small_width) ? __p.padding_amount_2x : __p.padding_amount
    }
    Rectangle {
      id: interfaceConfigurationGroup
      Layout.row: 0
      Layout.column: 3
      Layout.columnSpan: 5
      Layout.rowSpan: 3
      Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
      Layout.fillHeight: true
      Layout.fillWidth: true
      Layout.preferredWidth: 5
      Layout.preferredHeight: 3
      color: "yellow"
      opacity: 0.8
      //padding: (_small_width) ? __p.padding_amount_2x : __p.padding_amount
    }
    Rectangle {
      id: charApperanceGroup
      Layout.row: 3
      Layout.column: 3
      Layout.columnSpan: 5
      Layout.rowSpan: 2
      Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
      Layout.fillHeight: true
      Layout.fillWidth: true
      Layout.preferredWidth: 5
      Layout.preferredHeight: 2
      color: "lightblue"
      opacity: 0.8
      //padding: (_small_width) ? __p.padding_amount_2x : __p.padding_amount
    }
    Rectangle {
      id: buttonsBlock
      Layout.row: 5
      Layout.column: 3
      Layout.columnSpan: 5
      Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
      Layout.fillHeight: true
      Layout.fillWidth: true
      Layout.preferredWidth: 5
      Layout.preferredHeight: 1
      color: "darkblue"
      opacity: 0.8
      //padding: (_small_width) ? __p.padding_amount_2x : __p.padding_amount
    }
  }
}
