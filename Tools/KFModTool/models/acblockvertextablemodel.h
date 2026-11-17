#ifndef ACBLOCKVERTEXTABLEMODEL_H
#define ACBLOCKVERTEXTABLEMODEL_H

#include "datahandlers/acmission.h"
#include <QAbstractTableModel>

class ACBlockVertexTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ACBlockVertexTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    void setTarget(ACMission* missionPtr, size_t blockIdx, size_t subIdx);
    void refresh();

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override { Q_UNUSED(parent); return 4; }
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    ACMission* mission = nullptr;
    size_t blockIndex = 0;
    size_t subIndex = 0;
};

#endif // ACBLOCKVERTEXTABLEMODEL_H