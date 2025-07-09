#include "figure.h"

Figure::Figure(QPointF point, QObject *parent)
    : QObject(parent), QGraphicsItem(),
    m_pen(Qt::black, 2)
{
    setStartPoint(mapFromScene(point));
    setEndPoint(mapFromScene(point));
    connect(this, &Figure::pointChanged, this, &Figure::updateFigure);
}

void Figure::updateFigure()
{
    this->update(boundingRect());
}

QRectF Figure::boundingRect() const
{
    return QRectF((endPoint().x() > startPoint().x() ? startPoint().x() : endPoint().x()) - 5,
                  (endPoint().y() > startPoint().y() ? startPoint().y() : endPoint().y()) - 5,
                  qAbs(endPoint().x() - startPoint().x()) + 10,
                  qAbs(endPoint().y() - startPoint().y()) + 10);
}

QPointF Figure::startPoint() const
{
    return m_startPoint;
}

QPointF Figure::endPoint() const
{
    return m_endPoint;
}

void Figure::setStartPoint(const QPointF point)
{
    m_startPoint = mapFromScene(point);
    emit pointChanged();
}

void Figure::setEndPoint(const QPointF point)
{
    m_endPoint = mapFromScene(point);
    emit pointChanged();
}

void Figure::setPen(const QPen &pen)
{
    m_pen = pen;
    update();
}

QPen Figure::pen() const
{
    return m_pen;
}
