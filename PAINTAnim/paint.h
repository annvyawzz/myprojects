#ifndef PAINT_H
#define PAINT_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPushButton>

class PaintArea;

class Paint : public QMainWindow
{
    Q_OBJECT

public:
    explicit Paint(QWidget *parent = nullptr);

private slots:
    void setLine();
    void setSquare();
    void setRomb();
    void setTriangle();
    void chooseColor();
    void setSmallSize();
    void setMediumSize();
    void setLargeSize();

    void setEraser();
    void saveToFile();
    void startAnimation();
    void stopAnimation();

private:
    void createMenus();

    PaintArea *paintArea;
    QMenu *settingsMenu;
    QMenu *shapesMenu;

    QAction *lineAction;
    QAction *squareAction;
    QAction *rombAction;
    QAction *triangleAction;

    QAction *colorAction;
    QAction *smallSizeAction;
    QAction *mediumSizeAction;
    QAction *largeSizeAction;

    QAction *eraserAction;

    QPushButton *saveButton;
    QPushButton *startAnimationButton;
    QPushButton *stopAnimationButton;
};

#endif // PAINT_H
