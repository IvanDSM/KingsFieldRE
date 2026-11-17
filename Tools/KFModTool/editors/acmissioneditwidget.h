#ifndef ACMISSIONEDITWIDGET_H
#define ACMISSIONEDITWIDGET_H

#include "kfmteditor.h"
#include "../datahandlers/acmission.h"
#include "../models/acblockvertextablemodel.h"
#include "../models/acsectiontablemodel.h"
#include "../models/acspawntablemodel.h"
#include <QStringListModel>

namespace Ui
{
class ACMissionEditWidget;
}

class ACMissionEditWidget : public KFMTEditor
{
    Q_OBJECT

public:
    explicit ACMissionEditWidget(KFMTFile& file_, QWidget* parent = nullptr);
    ~ACMissionEditWidget() override;

private slots:
    void on_editorTabs_currentChanged(int index);
    void on_sectionList_clicked(const QModelIndex& index);
    void on_spawnList_clicked(const QModelIndex& index);
    void on_showCeilingsCheck_toggled(bool checked);
    void on_blockCombo_currentIndexChanged(int index);
    void on_subObjectCombo_currentIndexChanged(int index);
    void on_applyTranslateBtn_clicked();
    void onSectionOrVertexEdited();
    void onSpawnEdited();

private:
    void refreshSectionList();
    void refreshSpawnList();
    void refreshBlockCombos();
    void syncGizmoToSelectedSection(bool focusCamera);
    void syncGizmoToSelectedSpawn(bool focusCamera);
    void syncSpawnMarkers();

    Ui::ACMissionEditWidget* ui;
    QStringListModel sectionListModel;
    QStringListModel spawnListModel;
    ACSectionTableModel sectionTableModel;
    ACSpawnTableModel spawnTableModel;
    ACBlockVertexTableModel blockVertexTableModel;
};

#endif // ACMISSIONEDITWIDGET_H
