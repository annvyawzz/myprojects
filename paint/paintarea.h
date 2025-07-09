#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QGraphicsView>
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

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    paintScene *scene;
    QGraphicsView *view;
};

#endif // PAINTAREA_H
