import QtQuick 2.15
import QtQuick.Controls 2.15 as QQC2
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.0

import common 1.0
import ui_items 1.0

QQC2.Page {
  id: root
  readonly property bool _small_width: AppSingleton.is_width_small(parent.width)
  property int modelIndex: -1
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
    AppSingleton.toLog(`dataManager.deviceModel [${dataManager.deviceModel}]`)
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

    DeviceListView {
      id: interfaceList
      Layout.row: 0
      Layout.column: 0
      Layout.columnSpan: 2
      Layout.rowSpan: 6
      Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
      Layout.fillHeight: true
      Layout.fillWidth: true
      Layout.preferredWidth: 2
      Layout.preferredHeight: 6

      focus: true
      model: dataManager.deviceModel
      headerText: qsTr("Devices")
      spacing: (_small_width) ? __p.padding_amount_2x : __p.padding_amount
      onIndexChanged: {
        root.modelIndex = index
      }
    }

    QQC2.Button {
      ///Todo Change to ImageButton or ShaderButton
      id: refreshButton

      Layout.row: 6
      Layout.column: 0
      Layout.columnSpan: 2
      Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
      Layout.fillHeight: true
      Layout.fillWidth: true
      Layout.preferredWidth: 2
      Layout.preferredHeight: 1
      KeyNavigation.tab: interfaceList
      text: qsTr("Refresh")
      onClicked: {
        dataManager.refreshInterfaces()
        interfaceList.forceActiveFocus()
      }
    }

    SimpleGroupBox {
      id: interfaceConfigurationGroup
      Layout.row: 0
      Layout.column: 2
      Layout.columnSpan: 6
      Layout.rowSpan: 4
      Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
      Layout.fillHeight: true
      Layout.fillWidth: true
      Layout.preferredWidth: 6
      Layout.preferredHeight: 4
      borderText: qsTr("InterfaceConfiguration")
      font {
        family: AppSingleton.droidFont.name
        pointSize: AppSingleton.smallFontSize
      }

      inlineContent: GridLayout {
        id: _innerGrid
        anchors.fill: parent
        anchors.margins: __p.safe_padding
        columnSpacing: __p.spacing
        rowSpacing: __p.spacing
        columns: 8
        rows: 6
        QQC2.RadioButton {
          id: monitoringRadioButton
          Layout.row: 0
          Layout.column: 0
          Layout.columnSpan: 5
          Layout.rowSpan: 1
          Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
          Layout.fillHeight: true
          Layout.fillWidth: true
          Layout.preferredWidth: 1
          Layout.preferredHeight: 5
          text: qsTr("Monitor this Interface")
          checkable: true
        }
        QQC2.RadioButton {
          id: displayTrayNotificationRadioButton
          Layout.row: 1
          Layout.column: 0
          Layout.columnSpan: 5
          Layout.rowSpan: 1
          Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
          Layout.fillHeight: true
          Layout.fillWidth: true
          Layout.preferredWidth: 1
          Layout.preferredHeight: 5
          text: qsTr("Display tray notifications")

          checkable: true
        }
        QQC2.Label {
          id: updateIntervalLabel
          Layout.row: 2
          Layout.column: 0
          Layout.columnSpan: 3
          Layout.rowSpan: 1
          Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
          Layout.fillHeight: true
          Layout.fillWidth: true
          Layout.preferredWidth: 1
          Layout.preferredHeight: 3
          Layout.leftMargin: 10
          horizontalAlignment: Text.AlignLeft
          verticalAlignment: Text.AlignVCenter

          text: qsTr("Update interval:")
        }
        QQC2.SpinBox {
          Layout.row: 2
          Layout.column: 4
          Layout.columnSpan: 3
          Layout.rowSpan: 1
          Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
          Layout.fillHeight: true
          Layout.fillWidth: true
          Layout.preferredWidth: 1
          Layout.preferredHeight: 4
          from: 0
          to: 1000
          stepSize: 125
        }
      }
    }

    Rectangle {
      id: charApperanceGroup
      Layout.row: 4
      Layout.column: 2
      Layout.columnSpan: 6
      Layout.rowSpan: 2
      Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
      Layout.fillHeight: true
      Layout.fillWidth: true
      Layout.preferredWidth: 6
      Layout.preferredHeight: 2
      color: "lightblue"
      opacity: 0.8
      //padding: (_small_width) ? __p.padding_amount_2x : __p.padding_amount
    }
    Rectangle {
      id: buttonsBlock
      Layout.row: 6
      Layout.column: 2
      Layout.columnSpan: 6
      Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
      Layout.fillHeight: true
      Layout.fillWidth: true
      Layout.preferredWidth: 6
      Layout.preferredHeight: 1
      color: "darkblue"
      opacity: 0.8
      //padding: (_small_width) ? __p.padding_amount_2x : __p.padding_amount
    }
  }
}
