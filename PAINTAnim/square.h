#ifndef SQUARE_H
#define SQUARE_H

#include <QObject>
#include <QGraphicsItem>
#include "figure.h"

class Square : public Figure
{
    Q_OBJECT
public:
    explicit Square(QPointF point, QObject *parent = nullptr);
    ~Square() override = default;

    QString figureType() const override { return "Square"; }

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // SQUARE_H
