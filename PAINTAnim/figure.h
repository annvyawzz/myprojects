#ifndef FIGURE_H
#define FIGURE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPen>

class Figure : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

    Q_PROPERTY(QPointF startPoint READ startPoint WRITE setStartPoint NOTIFY pointChanged)
    Q_PROPERTY(QPointF endPoint READ endPoint WRITE setEndPoint NOTIFY pointChanged)

public:
    explicit Figure(QPointF point, QObject *parent = nullptr);
    virtual ~Figure() = default;

    // Методы для работы с точками
    QPointF startPoint() const;
    QPointF endPoint() const;
    void setStartPoint(const QPointF point);
    void setEndPoint(const QPointF point);

    // Методы для работы с пером
    void setPen(const QPen &pen);
    QPen pen() const;

    // Метод для обновления фигуры
    void updateFigure();

    // Чисто виртуальный метод для получения типа фигуры
    virtual QString figureType() const = 0;

    // Переопределение методов QGraphicsItem
    QRectF boundingRect() const override;

signals:
    void pointChanged();

private:
    QPointF m_startPoint;
    QPointF m_endPoint;
    QPen m_pen;
};

#endif // FIGURE_H
