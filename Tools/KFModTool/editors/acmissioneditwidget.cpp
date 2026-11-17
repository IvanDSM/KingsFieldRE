#include "acmissioneditwidget.h"
#include "ui_acmissioneditwidget.h"
#include <cmath>
#include <memory>

ACMissionEditWidget::ACMissionEditWidget(KFMTFile& file_, QWidget* parent)
    : KFMTEditor(file_, parent), ui(new Ui::ACMissionEditWidget)
{
    ui->setupUi(this);

    if (!handler)
    handler = std::make_unique<ACMission>(file_);

    auto& mission = *reinterpret_cast<ACMission*>(handler.get());

    ui->sectionList->setModel(&sectionListModel);
    ui->spawnList->setModel(&spawnListModel);

    ui->sectionTable->setModel(&sectionTableModel);
    ui->spawnTable->setModel(&spawnTableModel);
    ui->vertexTable->setModel(&blockVertexTableModel);

    connect(&sectionTableModel, &QAbstractItemModel::dataChanged,
            this, &ACMissionEditWidget::onSectionOrVertexEdited);
    connect(&blockVertexTableModel, &QAbstractItemModel::dataChanged,
            this, &ACMissionEditWidget::onSectionOrVertexEdited);
    connect(&spawnTableModel, &QAbstractItemModel::dataChanged,
            this, &ACMissionEditWidget::onSpawnEdited);

    ui->modelGLView->setModel(mission.getAssembledModel());
    ui->modelGLView->showAllObjects();

    refreshSectionList();
    refreshSpawnList();
    refreshBlockCombos();
    syncSpawnMarkers();

    if (mission.sectionCount() > 0)
    {
        ui->sectionList->setCurrentIndex(sectionListModel.index(0, 0));
        sectionTableModel.setSection(&mission, 0);
        syncGizmoToSelectedSection(true);
    }

    ui->spawnList->setCurrentIndex(spawnListModel.index(0, 0));
    spawnTableModel.setSpawn(&mission.getSpawn(0));
}

ACMissionEditWidget::~ACMissionEditWidget()
{
    delete ui;
}

void ACMissionEditWidget::refreshSectionList()
{
    auto& mission = *reinterpret_cast<ACMission*>(handler.get());
    QStringList items;
    items.reserve(static_cast<int>(mission.sectionCount()));

    for (size_t i = 0; i < mission.sectionCount(); ++i)
    {
        const auto& sec = mission.getSection(i);
        items << QStringLiteral("Section %1 (Block %2 @ %3, %4, %5)")
                     .arg(i)
                     .arg(sec.blockIndex)
                     .arg(sec.translation.at(0))
                     .arg(sec.translation.at(1))
                     .arg(sec.translation.at(2));
    }
    sectionListModel.setStringList(items);
}

void ACMissionEditWidget::refreshSpawnList()
{
    auto& mission = *reinterpret_cast<ACMission*>(handler.get());
    QStringList items;
    items.reserve(static_cast<int>(ACMission::spawnTableSize));

    for (size_t i = 0; i < ACMission::spawnTableSize; ++i)
    {
        const auto& sp = mission.getSpawn(i);
        if (sp.isEmpty())
        {
            items << QStringLiteral("Spawn %1 (Empty)").arg(i);
        }
        else
        {
            items << QStringLiteral("Spawn %1 (Res %2 @ %3, %4, %5)")
            .arg(i)
                .arg(sp.resourceId)
                .arg(sp.posX)
                .arg(sp.posY)
                .arg(sp.posZ);
        }
    }
    spawnListModel.setStringList(items);
}

void ACMissionEditWidget::refreshBlockCombos()
{
    auto& mission = *reinterpret_cast<ACMission*>(handler.get());
    ui->blockCombo->blockSignals(true);
    ui->blockCombo->clear();

    for (size_t i = 0; i < mission.blockCount(); ++i)
    {
        const auto& info = mission.getBlockInfo(i);
        ui->blockCombo->addItem(
            QStringLiteral("Block %1 (%2 sub-objects)").arg(i).arg(info.subObjects.size()));
    }
    ui->blockCombo->blockSignals(false);

    if (mission.blockCount() > 0)
    {
        ui->blockCombo->setCurrentIndex(0);
        on_blockCombo_currentIndexChanged(0);
    }
}

void ACMissionEditWidget::on_editorTabs_currentChanged(int index)
{
    if (index == 0) // Sections (Chunk 7)
        syncGizmoToSelectedSection(false);
    else if (index == 1) // Spawns (Chunk 12)
        syncGizmoToSelectedSpawn(false);
    else
        ui->modelGLView->setGizmo(false, {});
}

void ACMissionEditWidget::syncGizmoToSelectedSpawn(bool focusCamera)
{
    auto& mission = *reinterpret_cast<ACMission*>(handler.get());
    const int spIdx = ui->spawnList->currentIndex().row();
    if (spIdx < 0 || static_cast<size_t>(spIdx) >= mission.spawnCount())
    {
        ui->modelGLView->setGizmo(false, {});
        return;
    }

    const auto& sp = mission.getSpawn(static_cast<size_t>(spIdx));
    constexpr float kWorldToGL = 256.f / 4096.f;
    const QVector3D center(sp.posX * kWorldToGL,
                           sp.posY * kWorldToGL,
                           sp.posZ * kWorldToGL);

    if (focusCamera)
        ui->modelGLView->focusOn(center);

    ui->modelGLView->setGizmo(
        true,
        center,
        [this, spIdx](const QVector3D& glDelta) {
            auto& m = *reinterpret_cast<ACMission*>(handler.get());
            if (spIdx < 0 || static_cast<size_t>(spIdx) >= m.spawnCount()) return;

            constexpr float kGLToWorld = 4096.f / 256.f;
            auto& s = m.getSpawn(static_cast<size_t>(spIdx));
            s.posX = static_cast<int16_t>(s.posX + std::round(glDelta.x() * kGLToWorld));
            s.posY = static_cast<int16_t>(s.posY + std::round(glDelta.y() * kGLToWorld));
            s.posZ = static_cast<int16_t>(s.posZ + std::round(glDelta.z() * kGLToWorld));

            syncSpawnMarkers();
            spawnTableModel.setSpawn(&s);
            spawnListModel.setData(
                spawnListModel.index(spIdx, 0),
                QStringLiteral("Spawn %1 (Res %2 @ %3, %4, %5)")
                    .arg(spIdx)
                    .arg(s.resourceId)
                    .arg(s.posX)
                    .arg(s.posY)
                    .arg(s.posZ));
        },
        [](int axis, const QVector3D& candidateGLPos, Qt::KeyboardModifiers mods) -> QVector3D {
            QVector3D result = candidateGLPos;
            if (mods & Qt::ShiftModifier)
            {
                constexpr float kGridStep = 32.f;
                result[axis] = std::round(candidateGLPos[axis] / kGridStep) * kGridStep;
            }
            return result;
        });
}

void ACMissionEditWidget::syncGizmoToSelectedSection(bool focusCamera)
{
    auto& mission = *reinterpret_cast<ACMission*>(handler.get());
    const int secIdx = ui->sectionList->currentIndex().row();
    if (secIdx < 0 || static_cast<size_t>(secIdx) >= mission.sectionCount())
    {
        ui->modelGLView->setGizmo(false, {});
        return;
    }

    const auto& sec = mission.getSection(static_cast<size_t>(secIdx));
    // AC1 world units are divided by 4096 in ACMission and scaled by glModelScale (256) in ModelGLView
    constexpr float kWorldToGL = 256.f / 4096.f;
    const QVector3D center(sec.translation.at(0) * kWorldToGL,
                           sec.translation.at(1) * kWorldToGL,
                           sec.translation.at(2) * kWorldToGL);

    if (focusCamera)
        ui->modelGLView->focusOn(center);

    ui->modelGLView->setGizmo(
        true,
        center,
        [this, secIdx](const QVector3D& glDelta) {
            auto& m = *reinterpret_cast<ACMission*>(handler.get());
            if (secIdx < 0 || static_cast<size_t>(secIdx) >= m.sectionCount()) return;

            constexpr float kGLToWorld = 4096.f / 256.f;
            auto& s = m.getSection(static_cast<size_t>(secIdx));
            s.translation.at(0) = static_cast<int16_t>(s.translation.at(0) + std::round(glDelta.x() * kGLToWorld));
            s.translation.at(1) = static_cast<int16_t>(s.translation.at(1) + std::round(glDelta.y() * kGLToWorld));
            s.translation.at(2) = static_cast<int16_t>(s.translation.at(2) + std::round(glDelta.z() * kGLToWorld));

            m.rebuildAssembledLevel();
            ui->modelGLView->setModel(m.getAssembledModel());

            sectionTableModel.setSection(&m, static_cast<size_t>(secIdx));
            sectionListModel.setData(
                sectionListModel.index(secIdx, 0),
                QStringLiteral("Section %1 (Block %2 @ %3, %4, %5)")
                    .arg(secIdx)
                    .arg(s.blockIndex)
                    .arg(s.translation.at(0))
                    .arg(s.translation.at(1))
                    .arg(s.translation.at(2)));
        },
        [this, secIdx](int axis, const QVector3D& candidateGLPos, Qt::KeyboardModifiers mods) -> QVector3D {
            QVector3D result = candidateGLPos;
            if (mods & Qt::ControlModifier)
            {
                auto& m = *reinterpret_cast<ACMission*>(handler.get());
                constexpr float kGLToWorld = 4096.f / 256.f;
                constexpr float kWorldToGL = 256.f / 4096.f;
                const int16_t candWorld = static_cast<int16_t>(std::round(candidateGLPos[axis] * kGLToWorld));
                const int16_t snappedWorld = m.snapSectionAxisToNeighbors(static_cast<size_t>(secIdx), axis, candWorld, 512);
                result[axis] = snappedWorld * kWorldToGL;
            }
            else if (mods & Qt::ShiftModifier)
            {
                constexpr float kGridStep = 32.f;
                result[axis] = std::round(candidateGLPos[axis] / kGridStep) * kGridStep;
            }
            return result;
        });
}

void ACMissionEditWidget::syncSpawnMarkers()
{
    auto& mission = *reinterpret_cast<ACMission*>(handler.get());
    const int selectedIdx = ui->spawnList->currentIndex().row();
    constexpr float kWorldToGL = 256.f / 4096.f;

    std::vector<ModelGLView::SpawnMarker> markers;
    for (size_t i = 0; i < mission.spawnCount(); ++i)
    {
        const auto& sp = mission.getSpawn(i);
        if (sp.isEmpty()) continue;

        ModelGLView::SpawnMarker m;
        m.pos = QVector3D(sp.posX * kWorldToGL, sp.posY * kWorldToGL, sp.posZ * kWorldToGL);
        m.selected = (static_cast<int>(i) == selectedIdx);
        markers.push_back(m);
    }

    ui->modelGLView->setSpawns(std::move(markers));
}

void ACMissionEditWidget::on_sectionList_clicked(const QModelIndex& index)
{
    auto& mission = *reinterpret_cast<ACMission*>(handler.get());
    if (!index.isValid() || static_cast<size_t>(index.row()) >= mission.sectionCount()) return;

    const int secIdx = index.row();
    mission.setSelectedSection(secIdx);
    mission.setSelectedBlock(-1);
    sectionTableModel.setSection(&mission, static_cast<size_t>(secIdx));

    ui->modelGLView->setModel(mission.getAssembledModel());
    ui->modelGLView->showAllObjects();
    syncGizmoToSelectedSection(true);
}

void ACMissionEditWidget::on_spawnList_clicked(const QModelIndex& index)
{
    auto& mission = *reinterpret_cast<ACMission*>(handler.get());
    if (!index.isValid() || static_cast<size_t>(index.row()) >= mission.spawnCount()) return;

    const size_t spIdx = static_cast<size_t>(index.row());
    spawnTableModel.setSpawn(&mission.getSpawn(spIdx));
    syncSpawnMarkers();
    syncGizmoToSelectedSpawn(true);
}

void ACMissionEditWidget::on_showCeilingsCheck_toggled(bool checked)
{
    auto& mission = *reinterpret_cast<ACMission*>(handler.get());
    mission.setShowCeilings(checked);
    ui->modelGLView->setModel(mission.getAssembledModel());
    ui->modelGLView->showAllObjects();
}

void ACMissionEditWidget::on_blockCombo_currentIndexChanged(int index)
{
    auto& mission = *reinterpret_cast<ACMission*>(handler.get());
    ui->subObjectCombo->blockSignals(true);
    ui->subObjectCombo->clear();

    if (index >= 0 && static_cast<size_t>(index) < mission.blockCount())
    {
        mission.setSelectedBlock(index);
        const auto& subs = mission.getBlockInfo(static_cast<size_t>(index)).subObjects;
        for (size_t s = 0; s < subs.size(); ++s)
        {
            ui->subObjectCombo->addItem(
                QStringLiteral("Sub-Object %1 (%2 vertices)").arg(s).arg(subs.at(s).vtxCount));
        }

        ui->modelGLView->setModel(mission.getAssembledModel());
        ui->modelGLView->showAllObjects();

        if (!subs.empty())
        {
            ui->subObjectCombo->setCurrentIndex(0);
            blockVertexTableModel.setTarget(&mission, static_cast<size_t>(index), 0);
        }
        else
        {
            blockVertexTableModel.setTarget(nullptr, 0, 0);
        }
    }
    ui->subObjectCombo->blockSignals(false);
}

void ACMissionEditWidget::on_subObjectCombo_currentIndexChanged(int index)
{
    auto& mission = *reinterpret_cast<ACMission*>(handler.get());
    const int blkIdx = ui->blockCombo->currentIndex();
    if (blkIdx < 0 || index < 0) return;

    blockVertexTableModel.setTarget(&mission, static_cast<size_t>(blkIdx), static_cast<size_t>(index));
}

void ACMissionEditWidget::on_applyTranslateBtn_clicked()
{
    auto& mission = *reinterpret_cast<ACMission*>(handler.get());
    const int blkIdx = ui->blockCombo->currentIndex();
    const int subIdx = ui->subObjectCombo->currentIndex();
    if (blkIdx < 0 || subIdx < 0) return;

    mission.translateSubObject(static_cast<size_t>(blkIdx),
                               static_cast<size_t>(subIdx),
                               ui->dxSpin->value(),
                               ui->dySpin->value(),
                               ui->dzSpin->value());

    blockVertexTableModel.refresh();
    ui->modelGLView->setModel(mission.getAssembledModel());
    ui->modelGLView->showAllObjects();
}

void ACMissionEditWidget::onSectionOrVertexEdited()
{
    auto& mission = *reinterpret_cast<ACMission*>(handler.get());
    const int secRow = ui->sectionList->currentIndex().row();

    ui->modelGLView->setModel(mission.getAssembledModel());
    ui->modelGLView->showAllObjects();
    refreshSectionList();

    if (secRow >= 0)
        ui->sectionList->setCurrentIndex(sectionListModel.index(secRow, 0));

    if (ui->editorTabs->currentIndex() == 1)
        syncGizmoToSelectedSpawn(false);
    else
        syncGizmoToSelectedSection(false);

    syncSpawnMarkers();
}

void ACMissionEditWidget::onSpawnEdited()
{
    auto& mission = *reinterpret_cast<ACMission*>(handler.get());
    const int spRow = ui->spawnList->currentIndex().row();

    mission.rebuildAssembledLevel();
    ui->modelGLView->setModel(mission.getAssembledModel());
    ui->modelGLView->showAllObjects();
    refreshSpawnList();

    if (spRow >= 0)
        ui->spawnList->setCurrentIndex(spawnListModel.index(spRow, 0));
}
