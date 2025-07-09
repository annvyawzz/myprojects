#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "figure.h"
#include "romb.h"
#include "square.h"
#include "triangle.h"

class paintScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum FigureTypes {
        LineType,
        SquareType,
        RombType,
        TriangleType,
        EraserType
    };

    // Два конструктора - с параметрами размеров и без
    explicit paintScene(QObject *parent = nullptr);
    explicit paintScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);

    void setDrawingColor(const QColor &color);
    void setCurrentFigure(int figureType);
    void setPenWidth(int width);
    void saveFiguresToFile(const QString &filename);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int currentFigure;
    int penWidth;
    QColor drawingColor;
    QPointF previousPoint;
    Figure *tempFigure;
};

#endif // PAINTSCENE_H
