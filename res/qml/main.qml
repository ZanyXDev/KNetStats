import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15 as QQC2
import QtGraphicalEffects 1.15
import Qt.labs.platform 1.1

import common 1.0
import pages 1.0
import io.github.zanyxdev.knetstats 1.0
import io.github.zanyxdev.knetstats.MessageReciver 1.0


QQC2.ApplicationWindow {
    id: appWnd
    // ----- Property Declarations

    // Required properties should be at the top.
    readonly property int screenOrientation: Qt.LandscapeOrientation
    readonly property bool appInForeground: Qt.application.state === Qt.ApplicationActive

    property bool appInitialized: false
    property bool needSetup: false
    property int themeIcon: 1
    property var screenWidth: Screen.width
    property var screenHeight: Screen.height
    property var screenAvailableWidth: Screen.desktopAvailableWidth
    property var screenAvailableHeight: Screen.desktopAvailableHeight

    property string message: MessageReciver.message

    // ----- Signal declarations
    signal screenOrientationUpdated(int screenOrientation)

    // ----- Size information
    width: 800
    height: 600
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
        needSetup = !dataManager.loadSettings(dirAppConfig)
    }
    onVisibilityChanged: {
        updatePosition()
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
    onMessageChanged: {
        console.log(`recive msg ${message}`)
        sysTrayIcon.showMessage(qsTr("recive msg"), message, 3000)
    }
    background: {
        null
    }

    // ----- Connections

    // ----- Visual children
    // Rectangle {
    //     anchors.fill: parent
    //     anchors.topMargin: 4
    //     color: "grey"
    //     ListView{
    //         id:view
    //         anchors.fill: parent
    //         model:dataManager.deviceModel
    //         delegate: Rectangle{
    //             implicitHeight:14

    //             width: parent.width
    //             color: "red"
    //             Text {
    //                 id: test
    //                 text: model.interfacename
    //             }
    //         }
    //         Component.onCompleted: {
    //             dataManager.refreshInterfaces()
    //             console.trace()
    //             AppSingleton.toLog(` model [${model}]`)
    //             AppSingleton.toLog(` dataManager.deviceModel [${dataManager.deviceModel}]`)
    //         }
    //     }


    // }


    Loader {
        id: loader
        anchors.fill: parent
        source: appWnd.needSetup ? "qrc:/res/qml/pages/configurebase.qml" : "qrc:/res/qml/pages/statisticsbase.qml"

        anchors.topMargin: 4
        onLoaded: {

        }
    }
    //Another place in your code
    //sysTray.showMessage(title, message, SystemTrayIcon.Information, 1000)
    SystemTrayIcon {
        id: sysTrayIcon
        visible: true

        icon.source: appWnd.needSetup ? "qrc:/res/img/interfaces_missing.png" : "qrc:/res/img/theme"
                                        + appWnd.themeIcon + "_both.png"
        Component.onCompleted: {
            appWnd.needSetup ? appWnd.showAppWindow() : appWnd.hide()

            showMessage(qsTr("KNetStats"), qsTr("Need setup interfaces!"),
                        SystemTrayIcon.Warning, 3000)
        }
        menu: Menu {
            MenuItem {
                enabled: appWnd.needSetup
                text: qsTr("Configure Interfaces")
                onTriggered: appWnd.needSetup = false
            }
            MenuItem {
                text: qsTr("Quit")
                onTriggered: {
                    console.trace()
                    //backend.setCurrentDevName(dirAppData + "/devices.json")
                    Qt.quit()
                }
            }
        }
        onActivated: appWnd.showAppWindow()
    }
    // ----- non visual children
    BackEnd {
        id: backend
        Component.onCompleted: {
            backend.loadFromJson(dirAppData + "/devices.json")
        }
    }

    DataManager{
        id:dataManager
    }

    // ----- JavaScript functions
    function moveToCenter() {
        appWnd.y = (screenAvailableHeight / 2) - (height / 2)
        appWnd.x = (screenAvailableWidth / 2) - (width / 2)
    }

    function showAppWindow() {
        appWnd.show()
        appWnd.raise()
        appWnd.requestActivate()
    }

    function updatePosition() {
        x = (Screen.desktopAvailableWidth - width) / 2
        y = (Screen.desktopAvailableHeight - height) / 2
    }
}
