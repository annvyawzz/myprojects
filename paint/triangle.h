#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QObject>
#include <QGraphicsItem>
#include "figure.h"

class Triangle : public Figure
{
    Q_OBJECT
public:
    explicit Triangle(QPointF point, QObject *parent = nullptr);
    ~Triangle() override = default;

    QString figureType() const override { return "Triangle"; }

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // TRIANGLE_H
