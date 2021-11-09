#ifndef ENTITYCLASSTABLEMODEL_H
#define ENTITYCLASSTABLEMODEL_H

#include "datahandlers/map.h"
#include "games/kf2.h"
#include <QAbstractTableModel>

class EntityClassTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit EntityClassTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

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

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override
    {
        Q_UNUSED(parent)
        return createIndex(row, column);
    }

    int rowCount(const QModelIndex &parent) const override
    {
        Q_UNUSED(parent)
        if (entityClass == nullptr) return 0;
        return 47;
    }

    void set(KingsFieldII::EntityClass& entityClass_) { entityClass = &entityClass_; }

    void setFromEntity(KingsFieldII::EntityInstance& entity, Map& map)
    {
        entityClass = &map.getEntityClassDeclaration(entity.EntityClass);
        emit layoutChanged();
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

private:
    KingsFieldII::EntityClass* entityClass = nullptr;

    static const QString nullStr;
    const QString getSomePointer(size_t somePtrIndex) const
    {
        if (!entityClass) return nullStr;
        if (somePtrIndex >= 16) return QStringLiteral("Ivan screwed up! Report this on GitHub!");

        auto somePtrValue = entityClass->SomePointers[somePtrIndex];
        if (somePtrValue == static_cast<unsigned int>(-1))
            return nullStr;
        else
            return QString::asprintf("%04u (0x%x)", somePtrValue, somePtrValue);
    }
};

#endif // ENTITYCLASSTABLEMODEL_H
