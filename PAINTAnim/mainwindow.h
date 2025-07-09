#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QTimer>
#include "paintscene.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QGraphicsView *mGraphicsView;
    paintScene *mGraphicsScene;  // Изменено на paintScene
    QTimer mTimer;
    long mUpdateIntervalMS;

    // Для управления рисованием
    void createToolBar();
    void setCurrentFigure(int figureType);
    void setDrawingColor(const QColor &color);
    void setPenWidth(int width);

private slots:
    void gameTick();
    void onColorChanged(const QColor &color);
};

#endif // MAINWINDOW_H
