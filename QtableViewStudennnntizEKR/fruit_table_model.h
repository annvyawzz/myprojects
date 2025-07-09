#ifndef FRUIT_TABLE_MODEL_H
#define FRUIT_TABLE_MODEL_H

#include <QAbstractTableModel>
#include "fruit.h"

class FruitTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit FruitTableModel(Fruit* fruit, QObject* parent = nullptr)
        : QAbstractTableModel(parent), m_fruit(fruit) {}

    // Обязательные методы:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return m_fruit ? m_fruit->Size() : 0;
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 2; // "Name" и "Section"
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || !m_fruit || role != Qt::DisplayRole)
            return QVariant();

        const auto& item = m_fruit->GetItem(index.row());
        switch(index.column()) {
        case 0: return QString::fromLocal8Bit(item.Name);
        case 1: return QString::fromLocal8Bit(item.Section);
        default: return QVariant();
        }
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role != Qt::DisplayRole) return QVariant();
        if (orientation == Qt::Horizontal) {
            return section == 0 ? "Name" : "Section";
        }
        return QVariant();
    }

private:
    Fruit* m_fruit;
};

#endif // FRUIT_TABLE_MODEL_H
