#include "mainwindow.h"
#include "gamedbeditwidget.h"
#include "map.h"
#include "mapeditwidget.h"
#include <QFileDialog>

void MainWindow::on_actionLoad_files_triggered()
{
#ifndef EMSCRIPTEN
    auto directory = QFileDialog::getExistingDirectory(this, "Select the folder with your King's Field T files.", QDir::homePath());
    if (directory.isEmpty())
        return;

    QDir tfile_dir(directory);
    if (!tfile_dir.exists("FDAT.T"))
    {
        QMessageBox::critical(this, "Error loading files!", "FDAT.T not found in the provided directory");
        return;
    }

    curSourceDirectory = directory;

    // We don't use C++14 so no make_unique :(
    fdat.reset(new TFile(tfile_dir.filePath("FDAT.T")));

    loadFdat();
#else
    auto loadedFdat = [this](const QString &fileName, const QByteArray &fileContent)
    {
        fdat.reset(new TFile(fileName, fileContent));
    };

    QFileDialog::getOpenFileContent("FDAT.T (FDAT.T)",  loadedFdat);

    //loadFdat();
#endif
}

void MainWindow::addMap(const unsigned int &index, const QString &name)
{
    std::shared_ptr<Map> map(new Map(*fdat, index, name));
    auto mapTreeItem = new KFMTTreeWidgetItem(ui->filesTree->itemAt(0,0), map);
    mapTreeItem->setText(0, "Map " + QString::number(index) + ": " + name);

    ui->filesTree->itemAt(0, 0)->addChild(mapTreeItem);
}

void MainWindow::loadFdat()
{
    if (fdat == nullptr)
        return;

    addMap(0, "Western Shore");
    addMap(1, "Garrison");
    addMap(2, "Central Village");
    addMap(3, "East Village");
    addMap(4, "Cathedral");
    addMap(5, "The Big Mine");
    addMap(6, "Necron's Coliseum");
    addMap(7, "Guyra's Lair");
    addMap(8, "Weird Debug Map");

    gameDB.reset(new GameDB(*fdat));
    addGameDB();
}

void MainWindow::on_filesTree_itemDoubleClicked(QTreeWidgetItem *item, int)
{
    if (item->type() == QTreeWidgetItem::UserType)
    {
        auto kfmtItem = dynamic_cast<KFMTTreeWidgetItem *>(item);
        if (kfmtItem->getType() == KFMTDataType::KFMT_MAP)
        {
            auto mapIndex = kfmtItem->getMap()->getIndex();
            if (openMaps.at(mapIndex) != -1)
                ui->editorTabs->setCurrentIndex(openMaps.at(mapIndex));
            else
            {
                auto map = kfmtItem->getMap();
                auto* mapEditor = new MapEditWidget(ui->editorTabs);
                mapEditor->setMap(map);
                ui->editorTabs->addTab(mapEditor, map->getName());
                ui->editorTabs->setCurrentWidget(mapEditor);
                ui->editorTabs->setTabIcon(ui->editorTabs->currentIndex(), QIcon(":/map_icon.png"));
                openMaps.at(mapIndex) = ui->editorTabs->currentIndex();
            }
        }
        else if (kfmtItem->getType() == KFMTDataType::KFMT_GAMEDB)
        {
            if (openGameDB != -1)
                ui->editorTabs->setCurrentIndex(openGameDB);
            else
            {
                auto gameDBEditor = new GameDBEditWidget(ui->editorTabs, kfmtItem->getDB());
                ui->editorTabs->addTab(gameDBEditor, "Game Database");
                ui->editorTabs->setCurrentWidget(gameDBEditor);
                ui->editorTabs->setTabIcon(ui->editorTabs->currentIndex(), QIcon(":/db_icon.png"));
            }
        }
    }
}

void MainWindow::on_actionSave_changes_triggered()
{
    for (auto curChild = 0; curChild < ui->filesTree->itemAt(0, 0)->childCount(); curChild++)
    {
        auto *child = dynamic_cast<KFMTTreeWidgetItem *>(ui->filesTree->itemAt(0,0)->child(curChild));

        if (child->getType() == KFMTDataType::KFMT_MAP)
            child->getMap()->writeChanges();
        else if (child->getType() == KFMTDataType::KFMT_GAMEDB)
            child->getDB()->writeChanges();
    }

    auto dirPath = QFileDialog::getExistingDirectory(this, "Select where to save the changed files",
                                               QDir::homePath());

    if (dirPath.isEmpty())
        return;

    if (dirPath == curSourceDirectory)
    {
        auto answer = QMessageBox::question(this, "You're about to overwrite your files!",
                                            "You just chose the same directory as your source files. Are you sure you want to overwrite them?");

        if (answer != QMessageBox::Yes)
            return;
    }

    QDir dir(dirPath);


    QFile fdatOut(dir.filePath("FDAT.T"));
    fdatOut.open(QIODevice::WriteOnly);
    fdatOut.write(fdat->getTFile());
    fdatOut.close();

    QMessageBox::information(this, "Changes saved successfully!", "Your changes have been saved!");
}

void MainWindow::addGameDB()
{
    auto gameDBTreeItem = new KFMTTreeWidgetItem(ui->filesTree->itemAt(0,0), gameDB);
    gameDBTreeItem->setText(0, "Game Database");

    ui->filesTree->itemAt(0, 0)->addChild(gameDBTreeItem);
}
