import QtQuick 2.15
import QtQuick.Controls 2.15 as QQC2
import common 1.0

QQC2.Page {
  id: root

  Component.onCompleted: {
    AppSingleton.toLog(`ConfigureBase page [${root.height}h,${root.width}w]`)
  }
}
