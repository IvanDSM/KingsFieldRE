#ifndef ACSPAWNTABLEMODEL_H
#define ACSPAWNTABLEMODEL_H

#include "ac1/mission.h"
#include <QAbstractTableModel>

class ACSpawnTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ACSpawnTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    void setSpawn(AC1::SpawnRecord* record);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override { Q_UNUSED(parent); return 2; }
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    AC1::SpawnRecord* spawn = nullptr;
};

#endif // ACSPAWNTABLEMODEL_H
