#include "paintarea.h"
#include <QVBoxLayout>
#include <QRandomGenerator>

PaintArea::PaintArea(QWidget *parent) : QWidget(parent)
{
    view = new QGraphicsView(this);
    scene = new paintScene(0, 0, view->width(), view->height(), this);
    view->setScene(scene);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(view);
    setLayout(layout);

    connect(&animationTimer, &QTimer::timeout, this, &PaintArea::animateFigures);
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

void PaintArea::startAnimation()
{
    figureSpeeds.clear();
    for (QGraphicsItem *item : scene->items()) {
        if (Figure *figure = dynamic_cast<Figure*>(item)) {
            //генерируем случайные скорости от -3 до 3
            qreal speedX = QRandomGenerator::global()->bounded(6) - 3;
            qreal speedY = QRandomGenerator::global()->bounded(6) - 3;

            if (speedX == 0) speedX = 1;
            if (speedY == 0) speedY = 1;

            figureSpeeds[figure] = QPointF(speedX, speedY);
        }
    }
    if (!animationTimer.isActive()) {
        animationTimer.start(16);
    }
}

void PaintArea::stopAnimation()
{
    if (animationTimer.isActive()) {
        animationTimer.stop();
    }
}

void PaintArea::animateFigures()
{
    for (auto it = figureSpeeds.begin(); it != figureSpeeds.end(); ++it) {
        Figure *figure = it.key();
        QPointF speed = it.value();

        // Получаем текущую позицию
        QPointF pos = figure->pos();

        // Рассчитываем новую позицию
        qreal newX = pos.x() + speed.x();
        qreal newY = pos.y() + speed.y();

        QRectF bounds = figure->boundingRect();
        QRectF sceneBounds = scene->sceneRect();

        if (newX + bounds.right() > sceneBounds.right()) {
            newX = sceneBounds.right() - bounds.right();
            speed.setX(-speed.x()); // Меняем направление по X
        }
        else if (newX + bounds.left() < sceneBounds.left()) {
            newX = sceneBounds.left() - bounds.left();
            speed.setX(-speed.x()); // Меняем направление по X
        }

        if (newY + bounds.bottom() > sceneBounds.bottom()) {
            newY = sceneBounds.bottom() - bounds.bottom();
            speed.setY(-speed.y()); // Меняем направление по Y
        }
        else if (newY + bounds.top() < sceneBounds.top()) {
            newY = sceneBounds.top() - bounds.top();
            speed.setY(-speed.y()); // Меняем направление по Y
        }

        // Обновляем скорость в карте
        figureSpeeds[figure] = speed;

        // Устанавливаем новую позицию
        figure->setPos(newX, newY);
    }

    scene->update();
}
