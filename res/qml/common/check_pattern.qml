import QtQuick 2.15

// CheckeredPattern.qml
Canvas {
  id: root
  anchors.fill: parent

  property real cellSize: 16
  property real squareSize: cellSize / 2
  property color backgroundColor: "white"
  property color squareColor: "black"

  onPaint: {
    var ctx = getContext('2d')
    ctx.fillStyle = root.backgroundColor
    ctx.globalAlpha = 0.7 // Добавляем прозрачность
    ctx.fillRect(0, 0, width, height)

    ctx.fillStyle = root.squareColor
    ctx.globalAlpha = 1.0 // Возвращаем полную непрозрачность для квадратов

    for (var j = 0; j < width; j += cellSize) {
      for (var i = 0; i < height; i += cellSize) {
        ctx.fillRect(j, i, squareSize, squareSize)
        ctx.fillRect(j + squareSize, i + squareSize, squareSize, squareSize)
      }
    }
  }
}
