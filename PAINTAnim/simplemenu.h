#ifndef SIMPLEMENU_H
#define SIMPLEMENU_H

#include <QMainWindow>
#include <QColor>

class QAction;
class QMenu;

class SimpleMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimpleMenu(QWidget *parent = nullptr);

signals:
    void colorChanged(const QColor &color);

private slots:
    void chooseColor();
    void about();

private:
    QAction *colorAction;
    QAction *aboutAction;
    QAction *quitAction;
    QColor currentColor;
    QAction *fugureAction;
};

#endif // SIMPLEMENU_H
