#ifndef TEXTURELISTMODEL_H
#define TEXTURELISTMODEL_H

#include "texturedb.h"
#include <QAbstractListModel>

class TextureListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    TextureListModel(QObject *parent, std::shared_ptr<TextureDB> textureDB_) : 
        QAbstractListModel(parent), textureDB(textureDB_) {}
    
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
        return QAbstractItemModel::flags(index);
    }
    
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override
    {
        Q_UNUSED(section) Q_UNUSED(orientation) Q_UNUSED(role)
        return {};
    }
    
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override
    {
        Q_UNUSED(parent)
        return createIndex(row, column);
    }
    
    int rowCount(const QModelIndex &parent) const override
    {
        Q_UNUSED(parent)
        return textureDB->getTextureCount();
    }
    
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override
    {
        Q_UNUSED(section) Q_UNUSED(value) Q_UNUSED(role) Q_UNUSED(orientation)
        return false;
    }
    
private:
    std::shared_ptr<TextureDB> textureDB;
};

#endif // TEXTURELISTMODEL_H
