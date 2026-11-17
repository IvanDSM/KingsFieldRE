#ifndef ACSECTIONTABLEMODEL_H
#define ACSECTIONTABLEMODEL_H

#include "ac1/mission.h"
#include "datahandlers/acmission.h"
#include <QAbstractTableModel>

class ACSectionTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ACSectionTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    void setSection(ACMission* missionPtr, size_t index);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override { Q_UNUSED(parent); return 2; }
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    ACMission* mission = nullptr;
    size_t sectionIndex = 0;
};

#endif // ACSECTIONTABLEMODEL_H
