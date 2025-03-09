
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
QQC2.Button {
  id: root


  /**
   * The user selected color
   */
  property alias color: colorDialog.currentColor


  /**
   * Title to show in the dialog
   */
  property alias dialogTitle: colorDialog.title


  /**
   * Allow the user to configure an alpha value
   */
  property bool showAlphaChannel: true


  /**
   * This signal is emitted when the color dialog has been accepted
   *
   * @since 5.61
   */
  signal accepted(color color)

  implicitWidth: 40 // to perfectly clone kcolorbutton from kwidgetaddons

  Accessible.role: Accessible.Button
  Accessible.name: qsTr("Color button")
  Accessible.description: enabled ? qsTr(("Current color is %1. This button will open a color chooser dialog.").arg(
                                           color)) : qsTr(("Current color is %1.").arg(color))
  background: Rectangle {
    id: bgrRect
    radius: 4
    color: "transparent"
    anchors.fill: parent
    border {
      width: 2
      color: "black"
    }
  }
  // create a checkerboard background for alpha to be adjusted
  Rectangle {
    id: colorBlock

    anchors.centerIn: bgrRect
    anchors.fill: bgrRect

    anchors.margins: 8
    CheckerPattern {
      id: checkerPattern
      anchors.fill: colorBlock
      visible: colorDialog.currentColor.a < 1
      onVisibleChanged: {
        console.log(`checkerPattern.visible ${checkerPattern.visible}`)
        console.log(`colorDialog.currentColor.a ${colorDialog.currentColor.a}`)
      }
    }
    color: root.enabled ? colorDialog.currentColor : disabledPalette.button

    SystemPalette {
      id: disabledPalette
      colorGroup: SystemPalette.Disabled
    }
  }

  QtDialogs.ColorDialog {
    id: colorDialog
    onAccepted: root.accepted(color)
    showAlphaChannel: root.showAlphaChannel
  }

  onClicked: {
    colorDialog.open()
    checkerPattern.requestPaint()
  }
}
