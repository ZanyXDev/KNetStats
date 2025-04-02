
/*
    SPDX-FileCopyrightText: 2015 David Edmundson <davidedmundson@kde.org>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/
// @link https://api.kde.org/frameworks/kdeclarative/html/ColorButton_8qml_source.html
import QtQuick 2.15
import QtQuick.Controls 2.15 as QQC2
import QtQuick.Dialogs 1.3 as QtDialogs
import QtGraphicalEffects 1.15
import common 1.0


/**
 * @short A pushbutton to display or allow user selection of a color.
 *
 * This widget can be used to display or allow user selection of a color.
 *
 * Example usage:
 * @code
 * import org.kde.kquickcontrols
 *
 * ColorButton {
 *   onColorChanged: console.log(color)
 * }
 * @endcode
 *
 * @inherits QtQuick.Controls.Button
 */
Item {
  id: root


  /**
   * The user selected color
   */
  property color color


  /**
   * Title to show in the dialog
   */
  property alias dialogTitle: colorDialog.title


  /**
   * Allow the user to configure an alpha value
   */
  property bool showAlphaChannel: true

  property bool isActive: root.enabled && mArea.containsMouse


  /**
      * @var mouseArea Mouse area element covering the button.
      */
  property alias mouseArea: mArea


  /**
   * This signal is emitted when the color dialog has been accepted
   *
   * @since 5.61
   */
  signal accepted(color color)
  signal hoverChanged

  implicitWidth: 40 // to perfectly clone kcolorbutton from kwidgetaddons
  implicitHeight: 90

  Accessible.role: Accessible.Button
  Accessible.name: qsTr("Color button")
  Accessible.description: enabled ? qsTr(("Current color is %1. This button will open a color chooser dialog.").arg(
                                           color)) : qsTr(("Current color is %1.").arg(color))

  onColorChanged: {
    colorDialog.setColor(color)
  }
  Rectangle {
    id: bgrRect
    radius: 4
    color: "transparent"
    anchors.fill: parent
    border {
      width: 2
      color: "darkgrey" /// TODO clear alpha channal
    }
  }
  // create a checkerboard background for alpha to be adjusted
  Rectangle {
    id: colorBlock
    property double verticalMargin: parent.height / 4
    property double horizontalMargin: parent.width / 4

    anchors {
      centerIn: bgrRect
      topMargin: verticalMargin
      bottomMargin: verticalMargin
      leftMargin: horizontalMargin
      rightMargin: horizontalMargin
      fill: parent
    }
    radius: 4
    CheckerPattern {
      id: checkerPattern
      anchors.fill: colorBlock
      visible: colorDialog.currentColor.a < 1
      squareColor: colorDialog.currentColor
    }
    color: root.enabled ? colorDialog.currentColor : disabledPalette.button
    onColorChanged: {
      checkerPattern.requestPaint()
    }
    SystemPalette {
      id: disabledPalette
      colorGroup: SystemPalette.Disabled
    }
    MouseArea {
      id: mArea
      anchors.fill: parent
      hoverEnabled: true
      cursorShape: isActive ? Qt.PointingHandCursor : Qt.ArrowCursor

      onClicked: {
        colorDialog.open()
        enabled = false
      }

      onHoveredChanged: root.hoverChanged()
    }
  }

  QtDialogs.ColorDialog {
    id: colorDialog

    onAccepted: {
      root.accepted(color)
      checkerPattern.requestPaint()
      mArea.enabled = true
    }
    onRejected: {
      mArea.enabled = true
    }
    showAlphaChannel: root.showAlphaChannel
  }

  state: mArea.pressed ? "buttonDown" : "buttonUp"
  states: [
    State {
      name: "buttonDown"
      PropertyChanges {
        target: bgrRect
        scale: 0.6
      }
      PropertyChanges {
        target: colorBlock
        scale: 0.8
      }
    },
    State {
      name: "buttonUp"
      PropertyChanges {
        target: bgrRect
        scale: 1.0
      }
      PropertyChanges {
        target: colorBlock
        scale: 1.0
      }
    }
  ]
  transitions: Transition {
    NumberAnimation {
      properties: scale
      easing.type: Easing.InOutQuad
      duration: AppSingleton.timer200
    }
  }
}
