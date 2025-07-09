#include "simplemenu.h"
#include <QMenuBar>
#include <QColorDialog>
#include <QMessageBox>
#include <QApplication>

SimpleMenu::SimpleMenu(QWidget *parent) : QMainWindow(parent), currentColor(Qt::red)
{
    colorAction = new QAction("&Choose Color", this);
    aboutAction = new QAction("&About", this);
    quitAction = new QAction("&Quit", this);

    QMenu *fileMenu = menuBar()->addMenu("&File");
    QMenu *helpMenu = menuBar()->addMenu("&Help");

    fileMenu->addAction(colorAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);
    helpMenu->addAction(aboutAction);

    connect(colorAction, &QAction::triggered, this, &SimpleMenu::chooseColor);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    connect(aboutAction, &QAction::triggered, this, &SimpleMenu::about);
}

void SimpleMenu::chooseColor() {
    QColor newColor = QColorDialog::getColor(currentColor, this, "Select Drawing Color");
    if (newColor.isValid()) {
        currentColor = newColor;
        emit colorChanged(currentColor);
    }
}

void SimpleMenu::about()
{
    QMessageBox::about(this, "About", "Simple Paint Application with Color Menu");
}
