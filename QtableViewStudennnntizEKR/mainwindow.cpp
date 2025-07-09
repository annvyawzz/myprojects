#include "mainwindow.h"
#include "fruit_table_model.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QHeaderView>
#include <sstream>
#include <fstream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
    fruitModel1(nullptr), fruitModel2(nullptr), fruitModelRes(nullptr),
    bagModel1(nullptr), bagModel2(nullptr), bagModelRes(nullptr),
    fruitProxy1(new QSortFilterProxyModel(this)),
    fruitProxy2(new QSortFilterProxyModel(this)),
    fruitProxyRes(new QSortFilterProxyModel(this)),
    bagProxy1(new QSortFilterProxyModel(this)),
    bagProxy2(new QSortFilterProxyModel(this)),
    bagProxyRes(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);

    fruitProxy1->setSortRole(Qt::DisplayRole);
    fruitProxy2->setSortRole(Qt::DisplayRole);
    fruitProxyRes->setSortRole(Qt::DisplayRole);
    bagProxy1->setSortRole(Qt::DisplayRole);
    bagProxy2->setSortRole(Qt::DisplayRole);
    bagProxyRes->setSortRole(Qt::DisplayRole);

    ui->tableView1->setModel(fruitProxy1);
    ui->tableView_1->setModel(fruitProxy2);
    ui->tableViewRes1->setModel(fruitProxyRes);
    ui->tableView2->setModel(bagProxy1);
    ui->tableView_2->setModel(bagProxy2);
    ui->tableViewRes2->setModel(bagProxyRes);

    ui->tableView1->setSortingEnabled(true);
    ui->tableView_1->setSortingEnabled(true);
    ui->tableViewRes1->setSortingEnabled(true);
    ui->tableView2->setSortingEnabled(true);
    ui->tableView_2->setSortingEnabled(true);
    ui->tableViewRes2->setSortingEnabled(true);

    connect(ui->mergeFruitsBtn, &QPushButton::clicked, this, &MainWindow::on_mergeFruits_clicked);
    connect(ui->intersectFruitsBtn, &QPushButton::clicked, this, &MainWindow::on_intersectFruits_clicked);
    connect(ui->mergeBagsBtn, &QPushButton::clicked, this, &MainWindow::on_mergeBags_clicked);
    connect(ui->intersectBagsBtn, &QPushButton::clicked, this, &MainWindow::on_intersectBags_clicked);
    connect(ui->sortFruitsBtn, &QPushButton::clicked, this, &MainWindow::sortFruitsByName);
    connect(ui->sortBagsBtn, &QPushButton::clicked, this, &MainWindow::sortBagsByName);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::on_searchButton_clicked);

    searchResultsModel->setColumnCount(3);
    searchResultsModel->setHorizontalHeaderLabels({"Name", "Number", "Section"});
    ui->searchResultsView->setModel(searchResultsModel);
    ui->searchResultsView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete fruitModel1;
    delete fruitModel2;
    delete fruitModelRes;
    delete bagModel1;
    delete bagModel2;
    delete bagModelRes;
}

void MainWindow::sortFruitsByName()
{
    if (fruitProxy1) fruitProxy1->sort(1, Qt::AscendingOrder);
    if (fruitProxy2) fruitProxy2->sort(1, Qt::AscendingOrder);
    if (fruitProxyRes) fruitProxyRes->sort(1, Qt::AscendingOrder);
}

void MainWindow::sortBagsByName()
{
    if (bagProxy1) bagProxy1->sort(0, Qt::AscendingOrder);
    if (bagProxy2) bagProxy2->sort(0, Qt::AscendingOrder);
    if (bagProxyRes) bagProxyRes->sort(0, Qt::AscendingOrder);
}

QStandardItemModel* MainWindow::createFruitModel(Fruit& fruit)
{
    auto model = new QStandardItemModel(0, 2, this);
    model->setHorizontalHeaderLabels({"Name","Section"});

    for (size_t i = 0; i < fruit.Size(); ++i)
    {
        const auto& item = fruit.GetItem(i);
        QList<QStandardItem*> rowItems;
        rowItems << new QStandardItem(item.Name);
        rowItems << new QStandardItem(item.Section);
        model->appendRow(rowItems);
    }

    return model;
}

QStandardItemModel* MainWindow::createBagModel(Bag& bag)
{
    auto model = new QStandardItemModel(0, 3, this);
    model->setHorizontalHeaderLabels({"Name", "Number", "Section"});

    for (size_t i = 0; i < bag.Size(); ++i)
    {
        const auto& item = bag.GetItem(i);
        QList<QStandardItem*> rowItems;
        rowItems << new QStandardItem(item.Name);
        rowItems << new QStandardItem(QString::number(item.Num));
        rowItems << new QStandardItem(item.Section);
        model->appendRow(rowItems);
    }

    return model;
}

QString MainWindow::readFileAsString(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        throw runtime_error("Не удалось открыть файл " + filename.toStdString());
    }
    QTextStream in(&file);
    QString content = in.readAll();
    file.close();
    return content;
}

void MainWindow::on_mergeFruits_clicked()
{
    processFruits(true);
}

void MainWindow::on_intersectFruits_clicked()
{
    processFruits(false);
}

void MainWindow::on_mergeBags_clicked()
{
    processBags(true);
}

void MainWindow::on_intersectBags_clicked()
{
    processBags(false);
}

void MainWindow::processFruits(bool mergeOperation)
{
    try {
        delete fruitModel1;
        delete fruitModel2;
        delete fruitModelRes;

        QString content1 = readFileAsString("Ob1.txt");
        QString content2 = readFileAsString("Ob2.txt");

        istringstream in1(content1.toStdString());
        istringstream in2(content2.toStdString());

        fruit1.GetData(in1);
        fruit2.GetData(in2);

        fruitModel1 = createFruitModel(fruit1);
        fruitModel2 = createFruitModel(fruit2);

        fruitProxy1->setSourceModel(fruitModel1);
        fruitProxy2->setSourceModel(fruitModel2);

        unique_ptr<ABS_COMP<S1>> result;
        if (mergeOperation) {
            result = fruit1.Merge(&fruit1, &fruit2);
        } else {
            result = fruit1.Intersection(&fruit1, &fruit2);
        }

        Fruit* fruits = dynamic_cast<Fruit*>(result.get());

        ofstream outFile(mergeOperation ? "Ob_merge.txt" : "Ob_intersect.txt");
        if (outFile) {
            result->PutData(outFile);
            outFile.close();
        }

        fruitModelRes = createFruitModel(*fruits);
        fruitProxyRes->setSourceModel(fruitModelRes);

        sortFruitsByName();

        QMessageBox::information(this, "Успех",
                                 mergeOperation ?
                                     "Фрукты успешно объединены и сохранены в Ob_merge.txt" :
                                     "Общие фрукты найдены и сохранены в Ob_intersect.txt");
    } catch (const exception& e) {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка обработки фруктов: ") + e.what());
    }
}

void MainWindow::processBags(bool mergeOperation)
{
    try {
        delete bagModel1;
        delete bagModel2;
        delete bagModelRes;

        QString content3 = readFileAsString("TOb1.txt");
        QString content4 = readFileAsString("TOb2.txt");

        istringstream in3(content3.toStdString());
        istringstream in4(content4.toStdString());

        bag1.GetData(in3);
        bag2.GetData(in4);

        bagModel1 = createBagModel(bag1);
        bagModel2 = createBagModel(bag2);

        bagProxy1->setSourceModel(bagModel1);
        bagProxy2->setSourceModel(bagModel2);

        unique_ptr<ABS_COMP<S2>> result;
        if (mergeOperation) {
            result = bag1.Merge(&bag1, &bag2);
        } else {
            result = bag1.Intersection(&bag1, &bag2);
        }

        Bag* bags = dynamic_cast<Bag*>(result.get());

        ofstream outFile(mergeOperation ? "TOb_merge.txt" : "TOb_intersect.txt");
        if (outFile) {
            result->PutData(outFile);
            outFile.close();
        }

        bagModelRes = createBagModel(*bags);
        bagProxyRes->setSourceModel(bagModelRes);

        sortBagsByName();

        QMessageBox::information(this, "Успех",
                                 mergeOperation ?
                                     "Товары успешно объединены и сохранены в TOb_merge.txt" :
                                     "Общие товары найдены и сохранены в TOb_intersect.txt");
    } catch (const exception& e) {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка обработки товаров: ") + e.what());
    }
}

void MainWindow::on_searchButton_clicked()
{
    bool ok;
    QString searchText = QInputDialog::getText(this, tr("Поиск товара"),
                                               tr("Введите название товара:"),
                                               QLineEdit::Normal, "", &ok);
    if (!ok || searchText.isEmpty())
        return;

    if (!bagModelRes)
    {
        QMessageBox::information(this, tr("Ошибка"),
                                 tr("Сначала обработайте товары (нажмите Process Bags)"));
        return;
    }

    searchResultsModel->clear();
    searchResultsModel->setHorizontalHeaderLabels({"Name", "Num", "Section"});

    bool found = false;

    for (int row = 0; row < bagModelRes->rowCount(); ++row)
    {
        QString itemName = bagProxyRes->index(row, 0).data().toString();
        if (itemName.contains(searchText, Qt::CaseInsensitive))
        {
            found = true;
            QList<QStandardItem*> resultRow;
            resultRow << new QStandardItem(itemName);
            resultRow << new QStandardItem(bagProxyRes->index(row, 1).data().toString());
            resultRow << new QStandardItem(bagProxyRes->index(row, 2).data().toString());
            searchResultsModel->appendRow(resultRow);
        }
    }

    if (!found)
    {
        QMessageBox::information(this, tr("Результаты поиска"),
                                 tr("Товары по запросу '%1' не найдены").arg(searchText));
    }
    else
    {
        ui->searchResultsView->resizeColumnsToContents();
    }
}



