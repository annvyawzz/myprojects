#include "paintarea.h"
#include <QVBoxLayout>

PaintArea::PaintArea(QWidget *parent) : QWidget(parent)
{
    // Инициализация в правильном порядке
    view = new QGraphicsView(this);
    scene = new paintScene(this);
    view->setScene(scene);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(view);
    setLayout(layout);

    scene->setSceneRect(0, 0, view->width(), view->height());
}

void PaintArea::setDrawingColor(const QColor &color)
{
    scene->setDrawingColor(color);
}

void PaintArea::setPenWidth(int width)
{
    scene->setPenWidth(width);
}

void PaintArea::setCurrentFigure(int figureType)
{
    scene->setCurrentFigure(figureType);
}

void PaintArea::resizeEvent(QResizeEvent *event)
{
    scene->setSceneRect(0, 0, view->width(), view->height());
    QWidget::resizeEvent(event);
}

void PaintArea::saveToFile(const QString &filename) {
    scene->saveFiguresToFile(filename);
}
