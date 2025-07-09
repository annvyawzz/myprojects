#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QGraphicsView>
#include <QTimer>
#include "paintscene.h"

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    explicit PaintArea(QWidget *parent = nullptr);
    void setDrawingColor(const QColor &color);
    void setPenWidth(int width);
    void setCurrentFigure(int figureType);
    void saveToFile(const QString &filename);

    void startAnimation();
    void stopAnimation();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void animateFigures();

private:
    paintScene *scene;
    QGraphicsView *view;

    QTimer animationTimer;
    QMap<Figure*, QPointF> figureSpeeds; // Храним скорости для каждой фигуры
};

#endif // PAINTAREA_H
