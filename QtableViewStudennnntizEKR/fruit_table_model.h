// fruit_table_model.h
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

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        if (parent.isValid()) return 0;
        return m_fruit ? m_fruit->Size() : 0;
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        if (parent.isValid()) return 0;
        return 2;
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
            switch(section) {
            case 0: return "Name";
            case 1: return "Section";
            default: return QVariant();
            }
        }
        return QVariant();
    }

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override {
        if (!index.isValid() || role != Qt::EditRole || !m_fruit)
            return false;

        auto& item = const_cast<S1&>(m_fruit->GetItem(index.row()));
        switch(index.column()) {
        case 0:
            strncpy(item.Name, value.toString().toLocal8Bit().constData(), sizeof(item.Name)-1);
            break;
        case 1:
            strncpy(item.Section, value.toString().toLocal8Bit().constData(), sizeof(item.Section)-1);
            break;
        default:
            return false;
        }

        emit dataChanged(index, index, {role});
        return true;
    }

    Qt::ItemFlags flags(const QModelIndex& index) const override {
        if (!index.isValid())
            return Qt::NoItemFlags;
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    }

private:
    Fruit* m_fruit;
};

#endif // FRUIT_TABLE_MODEL_H
