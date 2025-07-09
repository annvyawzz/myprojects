#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "fruit.h"
#include "bag.h"
#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QInputDialog>
#include <QSortFilterProxyModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_mergeFruits_clicked();
    void on_intersectFruits_clicked();
    void on_mergeBags_clicked();
    void on_intersectBags_clicked();
    void sortFruitsByName();
    void sortBagsByName();
    void on_searchButton_clicked();


private:
    Ui::MainWindow *ui;
    Fruit fruit1, fruit2;
    Bag bag1, bag2;

    QStandardItemModel* fruitModel1;
    QStandardItemModel* fruitModel2;
    QStandardItemModel* fruitModelRes;
    QStandardItemModel* bagModel1;
    QStandardItemModel* bagModel2;
    QStandardItemModel* bagModelRes;

    QSortFilterProxyModel* fruitProxy1;
    QSortFilterProxyModel* fruitProxy2;
    QSortFilterProxyModel* fruitProxyRes;
    QSortFilterProxyModel* bagProxy1;
    QSortFilterProxyModel* bagProxy2;
    QSortFilterProxyModel* bagProxyRes;

    QStandardItemModel* createFruitModel(Fruit& fruit);
    QStandardItemModel* createBagModel(Bag& bag);
    QString readFileAsString(const QString& filename);
    QStandardItemModel* searchResultsModel = new QStandardItemModel(this);

    void processFruits(bool mergeOperation);
    void processBags(bool mergeOperation);
};

#endif // MAINWINDOW_H
