#ifndef ENTITYSTATETABLEMODEL_H
#define ENTITYSTATETABLEMODEL_H

#include <QAbstractTableModel>

class EntityStateTableModel : public QAbstractTableModel
{
    Q_OBJECT
    
public:
    explicit EntityStateTableModel(QObject *parent = nullptr, uint8_t *statePointer_ = nullptr)
        : QAbstractTableModel(parent), statePointer(statePointer_) {}
    
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override
    {
        Q_UNUSED(parent)
        return 1;
    }
    
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    
    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    
    Qt::ItemFlags flags(const QModelIndex& index) const override
    {
        if (!index.isValid())
            return Qt::NoItemFlags;
        
        return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
    }
    
private:
    uint8_t *statePointer = nullptr;
};

#endif // ENTITYSTATETABLEMODEL_H
