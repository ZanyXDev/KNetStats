import QtQuick 2.15
import QtQuick.Controls 2.15 as QQC2
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.0

import common 1.0
import ui_items 1.0

QQC2.Page {
  id: root
  readonly property bool _small_width: AppSingleton.is_width_small(parent.width)
  property int modelIndex: 0
  QtObject {
    id: __p
    readonly property int safe_padding: 24
    readonly property int padding_amount: 2
    readonly property int padding_amount_2x: 2 * __p.padding_amount
    readonly property int spacing: 8
    readonly property int spacing_x3: 3 * __p.spacing
    readonly property int cell_size: 64
  }
  QtObject {
    id: currentDevice
    property string m_interfaceName
    property string m_sysDevPath
    property int m_updateInterval
    property bool m_monitoring
    property bool m_notifications
    property int m_theme
  }

  // ----- Signal handlers
  Component.onCompleted: {
    AppSingleton.toLog(`ConfigureBase page [${root.height}h,${root.width}w]`)
    AppSingleton.toLog(`dataManager.deviceModel [${dataManager.deviceModel}]`)
    dataManager.refreshInterfaces()
    getValuesFromIndex()
  }
  onModelIndexChanged: {
    getValuesFromIndex()
  }
  background: {
    null
  }
  Connections {
    target: dataManager
    function onDataChanged() {
      getValuesFromIndex()
    }
  }
  // ----- Visual children
  RowLayout {
    id: mainLayout
    anchors {
      fill: parent
      margins: __p.padding_amount_2x * 2
    }
    spacing: (_small_width) ? __p.padding_amount_2x : __p.padding_amount
    ColumnLayout {
      id: leftLayout
      Layout.fillHeight: true
      Layout.fillWidth: true
      Layout.preferredHeight: 2
      spacing: __p.spacing
      DeviceListView {
        id: interfaceList
        Layout.preferredHeight: 9
        Layout.preferredWidth: 2
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
        KeyNavigation.tab: buttonRefresh
        focus: true
        model: dataManager.deviceModel
        headerText: qsTr("Devices")
        spacing: (_small_width) ? __p.padding_amount_2x : __p.padding_amount

        onIndexChanged: {
          root.modelIndex = index
        }
        Component.onCompleted: {
          interfaceList.forceActiveFocus()
        }
      }
      QQC2.Button {
        id: buttonRefresh
        Layout.preferredHeight: 1
        Layout.preferredWidth: 2
        Layout.fillHeight: true
        Layout.fillWidth: true
        KeyNavigation.tab: monitoringCheckButton
        text: qsTr("Resfresh")
      }
    }
    ColumnLayout {
      id: rightLayout
      Layout.fillHeight: true
      Layout.fillWidth: true
      Layout.preferredWidth: 8
      spacing: __p.spacing
      SimpleGroupBox {
        id: interfaceConfigurationGroup
        Layout.preferredHeight: 4
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
        borderText: qsTr("InterfaceConfiguration")
        font {
          family: AppSingleton.droidFont.name
          pointSize: AppSingleton.smallFontSize
        }

        contentItem: GridLayout {
          anchors.fill: parent
          anchors.margins: __p.padding_amount_2x * 3
          rowSpacing: __p.spacing
          columns: 6
          rows: 6
          QQC2.CheckBox {
            id: monitoringCheckButton
            Layout.row: 0
            Layout.column: 0
            Layout.columnSpan: 6
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            focus: true
            KeyNavigation.tab: displayTrayNotificationCheckButton
            text: qsTr("Monitor this Interface")
            checkable: true
            checked: currentDevice.m_monitoring
            onCheckedChanged: {
              dataManager.setMonitoring(root.modelIndex, checked)
            }
          }
          QQC2.CheckBox {
            id: displayTrayNotificationCheckButton
            Layout.row: 1
            Layout.column: 0
            Layout.columnSpan: 6
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            KeyNavigation.tab: updateIntervalSpinBox
            text: qsTr("Display tray notifications")
            checkable: true
            checked: currentDevice.m_notifications
            onCheckedChanged: {
              dataManager.setNotifications(root.modelIndex, checked)
            }
          }
          QQC2.Label {
            id: updateIntervalLabel
            Layout.row: 2
            Layout.column: 0
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredHeight: 3
            Layout.leftMargin: 10
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            text: qsTr("Update interval:")
          }
          QQC2.SpinBox {
            id: updateIntervalSpinBox
            Layout.row: 2
            Layout.column: 3
            Layout.columnSpan: 5
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: 5
            KeyNavigation.tab: comboBoxTheme
            from: 0
            to: 1000
            stepSize: 125
            value: currentDevice.m_updateInterval
            onValueChanged: {
              dataManager.setUpdateInterval(root.modelIndex, value)
            }
          }
          QQC2.Label {
            id: iconThemeLabel
            Layout.row: 3
            Layout.column: 0
            Layout.columnSpan: 3

            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true

            Layout.preferredHeight: 4
            Layout.leftMargin: 10
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            text: qsTr("Icon theme:")
          }
          QQC2.ComboBox {
            id: comboBoxTheme
            Layout.row: 3
            Layout.column: 3
            Layout.columnSpan: 5

            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: 5

            KeyNavigation.tab: interfaceList
            model: [qsTr("Classic"), qsTr("Modern"), qsTr("Network"), qsTr("Wireless"), qsTr("Kppp")]
            currentIndex: currentDevice.m_theme
            onCurrentIndexChanged: {
              dataManager.setTheme(root.modelIndex, comboBoxTheme.currentIndex)
            }
          }
          QQC2.Label {
            id: previewLabel
            Layout.row: 4
            Layout.column: 0
            Layout.columnSpan: 2

            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: 3
            Layout.leftMargin: 10
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            text: qsTr("Preview:")
          }
          RowLayout {
            id: iconsRowLayout
            Layout.row: 4
            Layout.column: 3
            Layout.columnSpan: 5

            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: 5
            spacing: __p.spacing
            component IconImage: Image {
              height: 32
              width: 32
              fillMode: Image.PreserveAspectFit
              sourceSize.width: width
              sourceSize.height: height
            }
            Item {
              Layout.fillWidth: true
            }
            IconImage {
              id: iconError
              source: "qrc:/res/img/theme" + currentDevice.m_theme + "_error.png"
              QQC2.ToolTip.visible: hovered
              QQC2.ToolTip.text: qsTr("Error state image")
            }
            IconImage {
              id: iconNone
              source: "qrc:/res/img/theme" + currentDevice.m_theme + "_none.png"
              QQC2.ToolTip.visible: hovered
              QQC2.ToolTip.text: qsTr("None device image")
            }
            IconImage {
              id: iconTx
              source: "qrc:/res/img/theme" + currentDevice.m_theme + "_tx.png"
              QQC2.ToolTip.visible: hovered
              QQC2.ToolTip.text: qsTr("Device Tx mode image")
            }
            IconImage {
              id: iconRx
              source: "qrc:/res/img/theme" + currentDevice.m_theme + "_rx.png"
              QQC2.ToolTip.visible: hovered
              QQC2.ToolTip.text: qsTr("Device Rx mode image")
            }
            IconImage {
              id: iconBoth
              source: "qrc:/res/img/theme" + currentDevice.m_theme + "_both.png"
              QQC2.ToolTip.visible: hovered
              QQC2.ToolTip.text: qsTr("Device Both (Tx and Rx) mode image")
            }
            Item {
              Layout.fillWidth: true
            }
          }
        }
      }
      SimpleGroupBox {
        id: mAppearanceGroup
        Layout.preferredHeight: 4
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
        borderText: qsTr("Chart appearance")
        font {
          family: AppSingleton.droidFont.name
          pointSize: AppSingleton.smallFontSize
        }
        contentItem: Rectangle {
          anchors.fill: parent
          anchors.margins: __p.padding_amount_2x * 3
          opacity: 0.8
          color: "green"
        }
      }
      Rectangle {
        id: buttonRect
        Layout.preferredHeight: 1
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
        border {
          color: "darkgrey"
          width: 2
        }
        radius: 4
        color: "blue"
      }
    }
  }

  // ----- JavaScript functions
  function getValuesFromIndex() {

    var itemData = dataManager.get(modelIndex)
    currentDevice.m_interfaceName = itemData.interfacename
    currentDevice.m_sysDevPath = itemData.sysdevpath
    currentDevice.m_updateInterval = itemData.updateinterval
    currentDevice.m_monitoring = itemData.monitoring
    currentDevice.m_notifications = itemData.notification
    currentDevice.m_theme = itemData.theme
  }
}
