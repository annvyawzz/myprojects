#include "paint.h"
#include "paintarea.h"
#include <QColorDialog>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

Paint::Paint(QWidget *parent) : QMainWindow(parent)
{
    // Создаем главный виджет и layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Создаем кнопки управления анимацией
    startAnimationButton = new QPushButton("Начать анимацию", centralWidget);
    stopAnimationButton = new QPushButton("Остановить анимацию", centralWidget);
    startAnimationButton->setFixedSize(150, 30);
    stopAnimationButton->setFixedSize(150, 30);
    stopAnimationButton->setEnabled(false);

    // Создаем кнопку сохранения
    saveButton = new QPushButton("Сохранить фигуры", centralWidget);
    saveButton->setFixedSize(150, 30);

    // Горизонтальный layout для кнопок
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(startAnimationButton);
    buttonLayout->addWidget(stopAnimationButton);
    buttonLayout->addWidget(saveButton);

    // Создаем область рисования
    paintArea = new PaintArea(centralWidget);

    // Добавляем элементы в основной layout
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(paintArea);

    // Устанавливаем центральный виджет
    setCentralWidget(centralWidget);

    // Создаем меню
    createMenus();

    // Подключаем кнопки
    connect(startAnimationButton, &QPushButton::clicked, this, &Paint::startAnimation);
    connect(stopAnimationButton, &QPushButton::clicked, this, &Paint::stopAnimation);
    connect(saveButton, &QPushButton::clicked, this, &Paint::saveToFile);

    setWindowTitle(tr("Paint"));
    resize(800, 600);
}

void Paint::createMenus()
{
    // Меню настроек
    settingsMenu = menuBar()->addMenu(tr("&Настройки"));
    colorAction = new QAction(tr("Изменить цвет"), this);
    smallSizeAction = new QAction(tr("Тонкая линия (2px)"), this);
    mediumSizeAction = new QAction(tr("Средняя линия (5px)"), this);
    largeSizeAction = new QAction(tr("Толстая линия (10px)"), this);

    settingsMenu->addAction(colorAction);
    settingsMenu->addSeparator();
    settingsMenu->addAction(smallSizeAction);
    settingsMenu->addAction(mediumSizeAction);
    settingsMenu->addAction(largeSizeAction);

    // Меню фигур
    shapesMenu = menuBar()->addMenu(tr("&Фигуры"));
    lineAction = new QAction(tr("Линия"), this);
    squareAction = new QAction(tr("Квадрат"), this);
    rombAction = new QAction(tr("Ромб"), this);
    triangleAction = new QAction(tr("Треугольник"), this);
    eraserAction = new QAction(tr("Ластик"), this);

    shapesMenu->addAction(lineAction);
    shapesMenu->addAction(squareAction);
    shapesMenu->addAction(rombAction);
    shapesMenu->addAction(triangleAction);
    shapesMenu->addAction(eraserAction);

    // Подключаем сигналы и слоты
    connect(colorAction, &QAction::triggered, this, &Paint::chooseColor);
    connect(smallSizeAction, &QAction::triggered, this, &Paint::setSmallSize);
    connect(mediumSizeAction, &QAction::triggered, this, &Paint::setMediumSize);
    connect(largeSizeAction, &QAction::triggered, this, &Paint::setLargeSize);

    connect(lineAction, &QAction::triggered, this, &Paint::setLine);
    connect(squareAction, &QAction::triggered, this, &Paint::setSquare);
    connect(rombAction, &QAction::triggered, this, &Paint::setRomb);
    connect(triangleAction, &QAction::triggered, this, &Paint::setTriangle);
    connect(eraserAction, &QAction::triggered, this, &Paint::setEraser);
}

void Paint::chooseColor()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Выберите цвет");
    if (color.isValid()) {
        paintArea->setDrawingColor(color);
    }
}

void Paint::setSmallSize() { paintArea->setPenWidth(2); }
void Paint::setMediumSize() { paintArea->setPenWidth(5); }
void Paint::setLargeSize() { paintArea->setPenWidth(10); }

void Paint::setLine() {
    paintArea->setCurrentFigure(paintScene::LineType);
}

void Paint::setSquare() {
    paintArea->setCurrentFigure(paintScene::SquareType);
}

void Paint::setRomb() {
    paintArea->setCurrentFigure(paintScene::RombType);
}

void Paint::setTriangle() {
    paintArea->setCurrentFigure(paintScene::TriangleType);
}

void Paint::setEraser() {
    paintArea->setCurrentFigure(paintScene::EraserType);
}

void Paint::saveToFile() {
    QString filename = QFileDialog::getSaveFileName(this, "Сохранить фигуры", "", "Текстовые файлы (*.txt)");
    if (!filename.isEmpty()) {
        paintArea->saveToFile(filename);
    }
}

void Paint::startAnimation()
{
    paintArea->startAnimation();
    startAnimationButton->setEnabled(false);
    stopAnimationButton->setEnabled(true);
}

void Paint::stopAnimation()
{
    paintArea->stopAnimation();
    startAnimationButton->setEnabled(true);
    stopAnimationButton->setEnabled(false);
}
