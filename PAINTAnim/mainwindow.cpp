#include "mainwindow.h"
#include <QToolBar>
#include <QColorDialog>
#include <QActionGroup>
#include <QSpinBox>
#include <QLabel>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setGeometry(56, 100, 800, 800);

    // Создаем сцену для рисования
    mGraphicsScene = new paintScene(0, 0, 600, 600, this);

    // Создаем вид и устанавливаем сцену
    mGraphicsView = new QGraphicsView(mGraphicsScene, this);
    mGraphicsView->setGeometry(50, 50, 700, 700);
    mGraphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    mGraphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

    // Добавляем синюю рамку для обозначения границ
    QPen pen;
    pen.setColor(QColor(Qt::blue));
    pen.setWidth(2);
    mGraphicsScene->addRect(0, 0, mGraphicsScene->width(), mGraphicsScene->height(), pen);

    // Создаем панель инструментов
    createToolBar();

    // Настройка таймера для анимации
    mUpdateIntervalMS = 10;
    connect(&mTimer, &QTimer::timeout, this, &MainWindow::gameTick);
    mTimer.start(mUpdateIntervalMS);


}

MainWindow::~MainWindow()
{
    if (mGraphicsView) {
        delete mGraphicsView;
        mGraphicsView = nullptr;
    }
    if (mGraphicsScene) {
        delete mGraphicsScene;
        mGraphicsScene = nullptr;
    }
}

void MainWindow::createToolBar()
{
    QToolBar *toolBar = addToolBar("Tools");

    // Группа действий для выбора фигур
    QActionGroup *figureGroup = new QActionGroup(this);

    QAction *lineAction = new QAction("Line", this);
    lineAction->setCheckable(true);
    lineAction->setChecked(true);
    lineAction->setData(paintScene::LineType);

    QAction *rectAction = new QAction("Rectangle", this);
    rectAction->setCheckable(true);
    rectAction->setData(paintScene::SquareType);

    QAction *triangleAction = new QAction("Triangle", this);
    triangleAction->setCheckable(true);
    triangleAction->setData(paintScene::TriangleType);

    QAction *rombAction = new QAction("Rhombus", this);
    rombAction->setCheckable(true);
    rombAction->setData(paintScene::RombType);

    QAction *eraserAction = new QAction("Eraser", this);
    eraserAction->setCheckable(true);
    eraserAction->setData(paintScene::EraserType);

    figureGroup->addAction(lineAction);
    figureGroup->addAction(rectAction);
    figureGroup->addAction(triangleAction);
    figureGroup->addAction(rombAction);
    figureGroup->addAction(eraserAction);

    // Кнопка выбора цвета
    QAction *colorAction = new QAction("Color", this);
    connect(colorAction, &QAction::triggered, [this]() {
        QColor color = QColorDialog::getColor(Qt::black, this, "Select Color");
        if (color.isValid()) {
            mGraphicsScene->setDrawingColor(color);
        }
    });

    // Спинбокс для выбора толщины линии
    QSpinBox *widthSpin = new QSpinBox(this);
    widthSpin->setRange(1, 20);
    widthSpin->setValue(2);
    connect(widthSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::setPenWidth);

    // Добавляем элементы на панель инструментов
    toolBar->addAction(lineAction);
    toolBar->addAction(rectAction);
    toolBar->addAction(triangleAction);
    toolBar->addAction(rombAction);
    toolBar->addAction(eraserAction);
    toolBar->addSeparator();
    toolBar->addAction(colorAction);
    toolBar->addSeparator();
    toolBar->addWidget(new QLabel("Width:", this));
    toolBar->addWidget(widthSpin);

    // Подключаем выбор фигуры
    connect(figureGroup, &QActionGroup::triggered, [this](QAction *action) {
        setCurrentFigure(action->data().toInt());
    });
}

void MainWindow::setCurrentFigure(int figureType)
{
    mGraphicsScene->setCurrentFigure(figureType);
}

void MainWindow::setDrawingColor(const QColor &color)
{
    mGraphicsScene->setDrawingColor(color);
}

void MainWindow::setPenWidth(int width)
{
    mGraphicsScene->setPenWidth(width);
}

void MainWindow::gameTick()
{
    // Анимируем все фигуры на сцене
    qreal speed = 0.9;

    for (QGraphicsItem *item : mGraphicsScene->items()) {
        if (Figure *figure = dynamic_cast<Figure*>(item)) {
            // Получаем текущую позицию
            QPointF pos = figure->pos();

            // Рассчитываем новую позицию
            qreal newX = pos.x() + speed;
            qreal newY = pos.y() + speed;

            // Проверяем границы
            QRectF bounds = figure->boundingRect();
            QRectF sceneBounds = mGraphicsScene->sceneRect();

            if (newX + bounds.right() > sceneBounds.right()) {
                newX = sceneBounds.right() - bounds.right();
                speed = -speed; // Меняем направление
            }
            else if (newX + bounds.left() < sceneBounds.left()) {
                newX = sceneBounds.left() - bounds.left();
                speed = -speed; // Меняем направление
            }

            if (newY + bounds.bottom() > sceneBounds.bottom()) {
                newY = sceneBounds.bottom() - bounds.bottom();
                speed = -speed; // Меняем направление
            }
            else if (newY + bounds.top() < sceneBounds.top()) {
                newY = sceneBounds.top() - bounds.top();
                speed = -speed; // Меняем направление
            }

            // Устанавливаем новую позицию
            figure->setPos(newX, newY);
        }
    }

    mGraphicsScene->advance();
}

void MainWindow::onColorChanged(const QColor &color)
{
    if (mGraphicsScene) {
        mGraphicsScene->setDrawingColor(color);
    }
}
