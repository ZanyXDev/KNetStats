import QtQuick 2.15
import QtQuick.Controls 2.15 as QQC2
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3
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
    property bool m_chartTransparentBackground
    property int m_theme
    property string m_chartUplColor
    property string m_chartDldColor
    property string m_chartBgColor
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
      Layout.preferredHeight: 3
      spacing: __p.spacing
      DeviceListView {
        id: interfaceList
        Layout.topMargin: 10
        Layout.preferredHeight: 8
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
        Layout.preferredHeight: 2
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
      Layout.preferredWidth: 6
      spacing: __p.spacing
      SimpleGroupBox {
        id: interfaceConfigurationGroup
        Layout.preferredHeight: 4
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
        borderText: qsTr("InterfaceConfiguration")

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
            text: qsTr("Preview:[Error,None,Tx,Rx,Both]")
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
            }
            IconImage {
              id: iconNone
              source: "qrc:/res/img/theme" + currentDevice.m_theme + "_none.png"
            }
            IconImage {
              id: iconTx
              source: "qrc:/res/img/theme" + currentDevice.m_theme + "_tx.png"
            }
            IconImage {
              id: iconRx
              source: "qrc:/res/img/theme" + currentDevice.m_theme + "_rx.png"
            }
            IconImage {
              id: iconBoth
              source: "qrc:/res/img/theme" + currentDevice.m_theme + "_both.png"
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

        contentItem: GridLayout {
          anchors.fill: parent
          anchors.margins: __p.padding_amount_2x * 3
          anchors.topMargin: __p.padding_amount_2x * 5
          rowSpacing: __p.spacing
          columns: 6
          rows: 4
          QQC2.Label {
            id: uploadLineColorLabel
            Layout.row: 1
            Layout.column: 0
            Layout.columnSpan: 3

            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true

            Layout.preferredHeight: 4
            Layout.leftMargin: 10
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            text: qsTr("Upload line color")
            font {
              family: AppSingleton.droidFont.name
              pointSize: AppSingleton.smallFontSize
            }
          }
          ColorButton {
            id: uploadColorButton
            Layout.row: 1
            Layout.column: 4
            Layout.columnSpan: 4
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: 4
            //KeyNavigation.tab: interfaceList
            color: currentDevice.m_chartUplColor
            onAccepted: {
              dataManager.setChartUplColor(root.modelIndex, color)
            }
          }
          QQC2.Label {
            id: downloadLineColorLabel
            Layout.row: 2
            Layout.column: 0
            Layout.columnSpan: 3

            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true

            Layout.preferredHeight: 4
            Layout.leftMargin: 10
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            text: qsTr("Download line color")
            font {
              family: AppSingleton.droidFont.name
              pointSize: AppSingleton.smallFontSize
            }
          }
          ColorButton {
            id: downloadColorButton
            Layout.row: 2
            Layout.column: 4
            Layout.columnSpan: 4
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: 4

            //KeyNavigation.tab: interfaceList
            color: currentDevice.m_chartDldColor
            onAccepted: {
              dataManager.setChartUplColor(root.modelIndex, color)
            }
          }
          QQC2.Label {
            id: backgroundLineColorLabel
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
            text: qsTr("Background line color")
            font {
              family: AppSingleton.droidFont.name
              pointSize: AppSingleton.smallFontSize
            }
          }
          ColorButton {
            id: backgroundColorButton
            Layout.row: 3
            Layout.column: 4
            Layout.columnSpan: 4

            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: 4
            //KeyNavigation.tab: interfaceList
            color: currentDevice.m_chartBgColor
            onAccepted: {
              dataManager.setChartUplColor(root.modelIndex, color)
            }
          }
          QQC2.CheckBox {
            id: transparentBackground
            Layout.row: 4
            Layout.column: 0
            Layout.columnSpan: 6
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            focus: true
            KeyNavigation.tab: displayTrayNotificationCheckButton
            text: qsTr("Transparent background")
            checkable: true
            checked: currentDevice.m_chartTransparentBackground
            onCheckedChanged: {
              dataManager.setTransparentBackground(root.modelIndex, checked)
            }
          }
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
    currentDevice.m_chartTransparentBackground = itemData.charttransparentbackground
    currentDevice.m_chartUplColor = itemData.chartuplcolor
    currentDevice.m_chartDldColor = itemData.chartdldcolor
    currentDevice.m_chartBgColor = itemData.chartbgcolor
  }
}
