#include "paintscene.h"
#include <QFile>
#include <QTextStream>
#include <QTextStream>

paintScene::paintScene(QObject *parent) :
    QGraphicsScene(parent),
    currentFigure(LineType),
    penWidth(2),
    drawingColor(Qt::black),
    tempFigure(nullptr)
{
}

void paintScene::setCurrentFigure(int figureType)
{
    currentFigure = figureType;
}

void paintScene::setDrawingColor(const QColor &color)
{
    drawingColor = color;
}

void paintScene::setPenWidth(int width)
{
    penWidth = width;
}

void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (currentFigure == LineType) {

        previousPoint = event->scenePos();
    }
    else if (currentFigure == EraserType) {
        previousPoint = event->scenePos();
    }
    else {
        switch(currentFigure) {
        case SquareType:
            tempFigure = new Square(event->scenePos());
            break;
        case TriangleType:
            tempFigure = new Triangle(event->scenePos());
            break;
        case RombType:
            tempFigure = new Romb(event->scenePos());
            break;
        }
        tempFigure->setPen(QPen(drawingColor, penWidth));
        addItem(tempFigure);
    }
}

void paintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (currentFigure == LineType) {
        addLine(previousPoint.x(), previousPoint.y(),
                event->scenePos().x(), event->scenePos().y(),
                QPen(drawingColor, penWidth, Qt::SolidLine, Qt::RoundCap));
        previousPoint = event->scenePos();
    }
    else if (currentFigure == EraserType) {
        addLine(previousPoint.x(), previousPoint.y(),
                event->scenePos().x(), event->scenePos().y(),
                QPen(Qt::white, penWidth*2, Qt::SolidLine, Qt::RoundCap));
        previousPoint = event->scenePos();
    }
    else if (tempFigure) {
        tempFigure->setEndPoint(event->scenePos());
    }
}

void paintScene::saveFiguresToFile(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл для записи";
        return;
    }

    QTextStream out(&file);
    // Убрали установку кодировки - по умолчанию будет UTF-8

    int figureCount = 0;
    for (QGraphicsItem *item : items()) {
        if (Figure *figure = dynamic_cast<Figure*>(item)) {
            out << "Фигура " << ++figureCount << ":\n";
            out << "  Тип: " << figure->figureType() << "\n";
            out << "  Начало: (" << figure->startPoint().x() << ", "
                << figure->startPoint().y() << ")\n";
            out << "  Конец: (" << figure->endPoint().x() << ", "
                << figure->endPoint().y() << ")\n";
            out << "  Цвет: " << figure->pen().color().name() << "\n";
            out << "  Толщина: " << figure->pen().width() << "\n";
            out << "------------------------\n";
        }
    }

    if (figureCount == 0) {
        out << "На сцене нет фигур.\n";
    }

    file.close();
    qDebug() << "Сохранено" << figureCount << "фигур в файл:" << filename;
}
