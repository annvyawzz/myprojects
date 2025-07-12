// bag_table_model.h
#ifndef BAG_TABLE_MODEL_H
#define BAG_TABLE_MODEL_H

#include <QAbstractTableModel>
#include "bag.h"

class BagTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit BagTableModel(Bag* bag, QObject* parent = nullptr)
        : QAbstractTableModel(parent), m_bag(bag) {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return m_bag ? m_bag->Size() : 0;
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 3;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || !m_bag || role != Qt::DisplayRole)
            return QVariant();

        const auto& item = m_bag->GetItem(index.row());
        switch(index.column()) {
        case 0: return QString::fromLocal8Bit(item.Name);
        case 1: return item.Num;
        case 2: return QString::fromLocal8Bit(item.Section);
        default: return QVariant();
        }
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role != Qt::DisplayRole) return QVariant();
        if (orientation == Qt::Horizontal) {
            switch(section) {
            case 0: return "Name";
            case 1: return "Number";
            case 2: return "Section";
            default: return QVariant();
            }
        }
        return QVariant();
    }

private:
    Bag* m_bag;
};

#endif // BAG_TABLE_MODEL_H
