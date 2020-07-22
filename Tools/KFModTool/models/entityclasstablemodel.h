#ifndef ENTITYCLASSTABLEMODEL_H
#define ENTITYCLASSTABLEMODEL_H

#include <QAbstractTableModel>
#include <kftypes.h>

class EntityClassTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit EntityClassTableModel(QObject *parent,
                                      KingsField::EntityClassDeclaration &entityClassDecl_) :
        QAbstractTableModel(parent),
        entityClassDecl(entityClassDecl_) {}

    int columnCount(const QModelIndex &parent) const override
    {
        Q_UNUSED(parent)
        return 1;
    }

    QVariant data(const QModelIndex &index, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override
    {
        if (!index.isValid())
            return Qt::NoItemFlags;
        return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const
    {
        Q_UNUSED(parent)
        return createIndex(row, column);
    }

    int rowCount(const QModelIndex &parent) const override
    {
        Q_UNUSED(parent)
        return 56;
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override
    {
        Q_UNUSED(section) Q_UNUSED(value) Q_UNUSED(role)
        return false;
    }

private:
    KingsField::EntityClassDeclaration &entityClassDecl;

    const QString getSomePointer(size_t somePtrIndex) const
    {
        if (somePtrIndex < 16)
        {
            auto somePtrValue = entityClassDecl.SomePointers[somePtrIndex];
            if (somePtrValue == static_cast<unsigned int>(-1))
                return "Null";
            else
                return QString::number(somePtrValue)
                       + " (0x" + QString::number(somePtrValue, 16) +")";
        }

        return "Ivan screwed up! Report this on GitHub!";
    }
};

#endif // ENTITYCLASSTABLEMODEL_H
