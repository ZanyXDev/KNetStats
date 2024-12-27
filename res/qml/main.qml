import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15 as QQC2
import QtGraphicalEffects 1.15
import Qt.labs.platform 1.1

import common 1.0
import io.github.zanyxdev.knetstats.hal 1.0

//import QSystemTrayIcon 1.0
QQC2.ApplicationWindow {
  id: appWnd
  // ----- Property Declarations

  // Required properties should be at the top.
  readonly property int screenOrientation: Qt.LandscapeOrientation
  readonly property bool appInForeground: Qt.application.state === Qt.ApplicationActive

  property bool appInitialized: false
  property var screenWidth: Screen.width
  property var screenHeight: Screen.height
  property var screenAvailableWidth: Screen.desktopAvailableWidth
  property var screenAvailableHeight: Screen.desktopAvailableHeight

  // ----- Signal declarations
  signal screenOrientationUpdated(int screenOrientation)

  // ----- Size information
  width: 320
  height: 240
  maximumHeight: height
  maximumWidth: width

  minimumHeight: height
  minimumWidth: width
  // ----- Then comes the other properties. There's no predefined order to these.
  visible: true
  visibility: Window.Windowed

  // ----- Then attached properties and attached signal handlers.

  // ----- Signal handlers
  Component.onCompleted: {
    let infoMsg = `Screen.height[${Screen.height}], Screen.width[${Screen.width}]
    Screen [height ${height},width ${width}]
    Build with [${HAL.getAppBuildInfo()}]
    Available physical screens [${Qt.application.screens.length}]
    Available Resolution width: ${Screen.desktopAvailableWidth} height ${Screen.desktopAvailableHeight}
    `
    AppSingleton.toLog(infoMsg)

    appWnd.restoreSettings()
  }

  onAppInForegroundChanged: {
    if (appInForeground) {
      if (!appInitialized) {
        appInitialized = true
      }
    } else {
      if (isDebugMode)
        AppSingleton.toLog(
              `appInForeground: [${appInForeground} , appInitialized: ${appInitialized}]`)
    }
  }

  background: {
    null
  }

  // ----- Visual children
  SystemTrayIcon {
    visible: true
    icon.source: "qrc:/res/img/interfaces_missing.png"

    menu: Menu {
      MenuItem {
        text: qsTr("Quit")
        onTriggered: Qt.quit()
      }
    }
    onActivated: {
      appWnd.show()
      appWnd.raise()
      appWnd.requestActivate()
    }
  }
  //  ----- non visual children

  // ----- JavaScript functions
  function restoreSettings() {//appWnd.enableSounds = mSettings.enableSounds
    //appWnd.enableMusics = mSettings.enableMusics
  }
}
