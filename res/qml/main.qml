import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15 as QQC2
import QtGraphicalEffects 1.15
import Qt.labs.platform 1.1
import Qt.labs.settings 1.1

import common 1.0
import pages 1.0
import io.github.zanyxdev.knetstats 1.0

QQC2.ApplicationWindow {
    id: appWnd
    // ----- Property Declarations

    // Required properties should be at the top.
    readonly property int screenOrientation: Qt.LandscapeOrientation
    readonly property bool appInForeground: Qt.application.state === Qt.ApplicationActive

    property bool appInitialized: false
    property bool needSetup: true
    property int themeIcon: 1
    property var screenWidth: Screen.width
    property var screenHeight: Screen.height
    property var screenAvailableWidth: Screen.desktopAvailableWidth
    property var screenAvailableHeight: Screen.desktopAvailableHeight

    // ----- Signal declarations
    signal screenOrientationUpdated(int screenOrientation)

    // ----- Size information
    width: 640
    height: 480
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
    Loader {
        id: loader

        anchors.fill: parent
        anchors.topMargin: 4
        Component.onCompleted: {
            if (isDebugMode) {
                sysTrayIcon.showMessage(qsTr("statisticsbase.qml"), appWnd.toolTipsText)
                setSource("qrc:/res/qml/pages/statisticsbase.qml", {
                              "opacity": 0.9,
                              "eggPage":true
                          })
            } else {
                appWnd.needSetup ? setSource("qrc:/res/qml/pages/configurebase.qml", {
                                                 "opacity": 0.9
                                             }) : setSource(
                                       "qrc:/res/qml/pages/statisticsbase.qml", {
                                           "opacity": 0.9
                                       })
            }
        }
    }

    SystemTrayIcon {
        id:sysTrayIcon
        visible: true

        icon.source: appWnd.needSetup ? "qrc:/res/img/interfaces_missing.png" : "qrc:/res/img/theme"
                                        + appWnd.themeIcon + "_both.png"
        Component.onCompleted: {
            if (!isDebugMode) {
                (appWnd.needSetup) ? appWnd.showAppWindow() : appWnd.hide()
                showMessage(qsTr("KNetStats"), appWnd.toolTipsText)
            }
        }
        menu: Menu {
            MenuItem {
                enabled: appWnd.needSetup
                text: qsTr("Configure Interfaces")
                onTriggered: appWnd.needSetup = false
            }
            MenuItem {
                text: qsTr("Quit")
                onTriggered: Qt.quit()
            }
        }
        onActivated: appWnd.showAppWindow()
    }
    //  ----- non visual children
    Settings {
        id: mSettings
        category: "Settings"
        property alias needSetup: appWnd.needSetup
        property alias themeIcon: appWnd.themeIcon
    }
    // ----- JavaScript functions
    function restoreSettings() {
        appWnd.needSetup = mSettings.needSetup
        appWnd.themeIcon = mSettings.themeIcon
    }

    function showAppWindow() {
        appWnd.show()
        appWnd.raise()
        appWnd.requestActivate()
    }
}
