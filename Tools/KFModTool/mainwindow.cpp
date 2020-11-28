#include "mainwindow.h"
#include "gamedbeditwidget.h"
#include "map.h"
#include "mapeditwidget.h"
#include "modelviewerwidget.h"
#include "textureviewer.h"
#include <QFileDialog>

void MainWindow::on_actionLoad_files_triggered()
{
    auto directory = QFileDialog::getExistingDirectory(this, "Select the folder with your King's Field T files.", QDir::homePath());
    if (directory.isEmpty())
        return;

    QDir tfile_dir(directory);
    curSourceDirectory = directory;
    if (tfile_dir.exists("FDAT.T"))
    {
        // We don't use C++14 so no make_unique :(
        fdat.reset(new TFile(tfile_dir.filePath("FDAT.T")));
    
        loadFdat();
    }
    
    if (tfile_dir.exists("ITEM.T"))
    {
        // We don't use C++14 so no make_unique :(
        item.reset(new TFile(tfile_dir.filePath("ITEM.T")));
    
        loadItem();
    }
    
    if (tfile_dir.exists("MO.T"))
    {
        // We don't use C++14 so no make_unique :(
        mo.reset(new TFile(tfile_dir.filePath("MO.T")));
        loadMo();
    }
    
    if (tfile_dir.exists("RTMD.T"))
    {
        // We don't use C++14 so no make_unique :(
        rtmd.reset(new TFile(tfile_dir.filePath("RTMD.T")));
    
        loadRtmd();
    }
}

void MainWindow::addGameDB()
{
    std::shared_ptr<GameDB> gameDB(new GameDB(*fdat));
    auto gameDBTreeItem = new KFMTTreeWidgetItem(fdatTreeItem.get(), gameDB);
    gameDBTreeItem->setText(0, "Game Database");

    ui->filesTree->itemAt(0, 0)->addChild(gameDBTreeItem);
}

void MainWindow::addMap(unsigned int index, const QString &name)
{
    std::shared_ptr<Map> map(new Map(*fdat, index, name));
    auto mapTreeItem = new KFMTTreeWidgetItem(fdatTreeItem.get(), map);
    mapTreeItem->setText(0, "Map " + QString::number(index) + ": " + name);

    ui->filesTree->itemAt(0, 0)->addChild(mapTreeItem);
}

void MainWindow::addModel(TFile &tFile, unsigned int index, const QString &name)
{
    std::shared_ptr<Model> model(new Model(tFile, index));
    auto parentItem = ui->filesTree->findItems(tFile.getFilename(), Qt::MatchExactly).front();
    auto modelTreeItem = new KFMTTreeWidgetItem(parentItem, model);
    modelTreeItem->setText(0, name);
    parentItem->addChild(modelTreeItem);
}

void MainWindow::addTexture(TFile & tFile, unsigned int index, const QString & name)
{
    std::shared_ptr<Texture> texture(new Texture(tFile, index, name));
    auto parentItem = ui->filesTree->findItems(tFile.getFilename(), Qt::MatchExactly).front();
    auto textureTreeItem = new KFMTTreeWidgetItem(parentItem, texture);
    textureTreeItem->setText(0, name);
    parentItem->addChild(textureTreeItem);
}

void MainWindow::loadFdat()
{
    if (fdat == nullptr)
        return;
    
    if (fdatTreeItem.get() != nullptr)
    {
        ui->filesTree->removeItemWidget(fdatTreeItem.get(), 0);
        for (auto child : fdatTreeItem->takeChildren())
        {
            ui->filesTree->removeItemWidget(child, 0);
            delete child;
        }
    }
    
    fdatTreeItem.reset(new QTreeWidgetItem(ui->filesTree));
    fdatTreeItem->setIcon(0, QIcon(":/tfile_icon.png"));
    fdatTreeItem->setText(0, "FDAT.T");
    ui->filesTree->addTopLevelItem(fdatTreeItem.get());

    addMap(0, "Western Shore");
    addMap(1, "Garrison");
    addMap(2, "Central Village");
    addMap(3, "East Village");
    addMap(4, "Cathedral");
    addMap(5, "The Big Mine");
    addMap(6, "Necron's Coliseum");
    addMap(7, "Guyra's Lair");
    addMap(8, "Weird Debug Map");
    addModel(*fdat, 29, "Dagger Viewmodel");
    addModel(*fdat, 30, "Short Sword Viewmodel");
    addModel(*fdat, 31, "Knight Sword Viewmodel");
    addModel(*fdat, 32, "Morning Star Viewmodel");
    addModel(*fdat, 33, "Battle Hammer Viewmodel");
    addModel(*fdat, 34, "Bastard Sword Viewmodel");
    addModel(*fdat, 35, "Crescent Axe Viewmodel");
    addModel(*fdat, 36, "Flame Sword Viewmodel");
    addModel(*fdat, 37, "Shiden Viewmodel");
    addModel(*fdat, 38, "Spider Viewmodel");
    addModel(*fdat, 39, "Ice Blade Viewmodel");
    addModel(*fdat, 40, "Seath's Sword Viewmodel");
    addModel(*fdat, 41, "Moonlight Sword Viewmodel");
    addModel(*fdat, 42, "Dark Slayer Viewmodel");
    addModel(*fdat, 43, "Bow Viewmodel");
    addModel(*fdat, 44, "Arbalest Viewmodel");
    addGameDB();
}

void MainWindow::loadItem()
{
    if (item == nullptr)
        return;
    
    if (itemTreeItem.get() != nullptr)
    {
        ui->filesTree->removeItemWidget(itemTreeItem.get(), 0);
        for (auto child : itemTreeItem->takeChildren())
        {
            ui->filesTree->removeItemWidget(child, 0);
            delete child;
        }
    }
    
    itemTreeItem.reset(new QTreeWidgetItem(ui->filesTree));
    itemTreeItem->setIcon(0, QIcon(":/tfile_icon.png"));
    itemTreeItem->setText(0, "ITEM.T");
    ui->filesTree->addTopLevelItem(itemTreeItem.get());

    addModel(*item, 0, "Weapon: Dagger");
    addModel(*item, 1, "Weapon: Short Sword");
    addModel(*item, 2, "Weapon: Knight Sword");
    addModel(*item, 3, "Weapon: Morning Star");
    addModel(*item, 4, "Weapon: Battle Hammer");
    addModel(*item, 5, "Weapon: Bastard Sword");
    addModel(*item, 6, "Weapon: Crescent Axe");
    addModel(*item, 7, "Weapon: Flame Sword");
    addModel(*item, 8, "Weapon: Shiden");
    addModel(*item, 9, "Weapon: Spider");
    addModel(*item, 10, "Weapon: Ice Blade");
    addModel(*item, 11, "Weapon: Seaths Sword");
    addModel(*item, 12, "Weapon: Moonlight Sword");
    addModel(*item, 13, "Weapon: Dark Slayer");
    addModel(*item, 14, "Weapon: Bow");
    addModel(*item, 15, "Weapon: Arbalest");
    addModel(*item, 16, "Head: Iron Mask");
    addModel(*item, 17, "Head: Knight Helm");
    addModel(*item, 18, "Head: Great Helm");
    addModel(*item, 19, "Head: Blood Crown");
    addModel(*item, 20, "Head: Lightning Helm");
    addModel(*item, 21, "Head: Seaths Helm");
    addModel(*item, 22, "Body: Breast Plate");
    addModel(*item, 23, "Body: Knight Plate");
    addModel(*item, 24, "Body: Ice Armor");
    addModel(*item, 25, "Body: Dark Armor");
    addModel(*item, 26, "Body: Seaths Armor");
    addModel(*item, 27, "Shield: Leather Shield");
    addModel(*item, 28, "Shield: Large Shield");
    addModel(*item, 29, "Shield: Moon Guard");
    addModel(*item, 30, "Shield: Crystal Guard");
    addModel(*item, 31, "Shield: Skull Shield");
    addModel(*item, 32, "Shield: Seaths Shield");
    addModel(*item, 33, "Arms: Iron Gloves");
    addModel(*item, 34, "Arms: Stone Hands");
    addModel(*item, 35, "Arms: Silver Arms");
    addModel(*item, 36, "Arms: Demons Hands");
    addModel(*item, 37, "Arms: Ruinous Gloves");
    addModel(*item, 38, "Feet: Iron Boots");
    addModel(*item, 39, "Feet: Leg Guarders");
    addModel(*item, 40, "Feet: Silver Boots");
    addModel(*item, 41, "Feet: Death Walkers");
    addModel(*item, 42, "Feet: Ruinous Boots");
    addModel(*item, 43, "Equip. Item: Scorpions Bracelet");
    addModel(*item, 44, "Equip. Item: Seaths Tear");
    addModel(*item, 45, "Equip. Item: Seaths Bracelet");
    addModel(*item, 46, "Equip. Item: Earth Ring");
    addModel(*item, 47, "Equip. Item: Psycpros Collar");
    addModel(*item, 48, "Equip. Item: Amulet Of Mist");
    addModel(*item, 49, "Equip. Item: Lightwave Ring");
    addModel(*item, 50, "Item: Pirate's Map");
    addModel(*item, 51, "Item: Miner's Map");
    addModel(*item, 52, "Item: Necron's Map");
    addModel(*item, 53, "Item: Gold Coin");
    addModel(*item, 54, "Item: Blood Stone");
    addModel(*item, 55, "Item: Moon Stone");
    addModel(*item, 56, "Item: Verdite");
    addModel(*item, 57, "Item: Earth Herb");
    addModel(*item, 58, "Item: Antidote");
    addModel(*item, 59, "Item: Dragon Crystal");
    addModel(*item, 60, "Item: Blue Potion");
    addModel(*item, 61, "Item: Red Potion");
    addModel(*item, 62, "Item: Green Potion");
    addModel(*item, 63, "Item: Gold Potion");
    addModel(*item, 64, "Item: \"A\" Potion");
    addModel(*item, 65, "Item: Crystal Flask");
    addModel(*item, 66, "Item: Figure Of Seath");
    addModel(*item, 67, "Item: Phantom Rod");
    addModel(*item, 68, "Item: Truth Glass");
    addModel(*item, 69, "Item: Seaths Plume");
    addModel(*item, 70, "Item: Demons Pick");
    addModel(*item, 71, "Item: Harvines Flute");
    addModel(*item, 72, "Item: Ground Bell");
    addModel(*item, 73, "Item: Fire Crystal");
    addModel(*item, 74, "Item: Water Crystal");
    addModel(*item, 75, "Item: Earth Crystal");
    addModel(*item, 76, "Item: Wind Crystal");
    addModel(*item, 77, "Item: Light Crystal");
    addModel(*item, 78, "Item: Dark Crystal");
    addModel(*item, 79, "Item: Crystal");
    addModel(*item, 80, "Item: Crystal Shard");
    addModel(*item, 81, "Item: \"A\" Ring");
    addModel(*item, 82, "Item: Elf's Key");
    addModel(*item, 83, "Item: Pirate's Key");
    addModel(*item, 84, "Item: Skull Key");
    addModel(*item, 85, "Item: Jail Key");
    addModel(*item, 86, "Item: Rhombus Key");
    addModel(*item, 87, "Item: Harvines Key");
    addModel(*item, 88, "Item: Dragon Stone");
    addModel(*item, 89, "Item: Magicians Key");
    addModel(*item, 90, "Item: Silver Key");
    addModel(*item, 91, "Item: Gold Key");
    addModel(*item, 92, "Item: Shrine Key");
    addModel(*item, 93, "Item: \"A\" Herb");
    addModel(*item, 94, "Item: Moon Gate");
    addModel(*item, 95, "Item: Star Gate");
    addModel(*item, 96, "Item: Sun Gate");
    addModel(*item, 97, "Item: Moon Key");
    addModel(*item, 98, "Item: Star Key");
    addModel(*item, 99, "Item: Sun Key");
    addModel(*item, 100, "Item: Arrow For The Bow");
    addModel(*item, 101, "Item: Elf's Bolt");
    addModel(*item, 102, "Item: \"A\" Herb 2");
    addTexture(*item, 103, "Test");
}

void MainWindow::loadMo()
{
    if (mo == nullptr)
        return;
    
    if (moTreeItem.get() != nullptr)
    {
        ui->filesTree->removeItemWidget(moTreeItem.get(), 0);
        for (auto child : moTreeItem->takeChildren())
        {
            ui->filesTree->removeItemWidget(child, 0);
            delete child;
        }
    }
    
    moTreeItem.reset(new QTreeWidgetItem(ui->filesTree));
    moTreeItem->setIcon(0, QIcon(":/tfile_icon.png"));
    moTreeItem->setText(0, "MO.T");
    ui->filesTree->addTopLevelItem(moTreeItem.get());
    
    for (size_t moFile = 0; moFile < mo->getTrueNumFiles() - 1; moFile++)
        addModel(*mo, moFile, QString::asprintf("Model %zu", moFile));
}

void MainWindow::loadRtmd()
{
    if (rtmd == nullptr)
        return;
    
    if (rtmdTreeItem.get() != nullptr)
    {
        ui->filesTree->removeItemWidget(rtmdTreeItem.get(), 0);
        for (auto child : rtmdTreeItem->takeChildren())
        {
            ui->filesTree->removeItemWidget(child, 0);
            delete child;
        }
    }
    
    rtmdTreeItem.reset(new QTreeWidgetItem(ui->filesTree));
    rtmdTreeItem->setIcon(0, QIcon(":/tfile_icon.png"));
    rtmdTreeItem->setText(0, "RTMD.T");
    ui->filesTree->addTopLevelItem(rtmdTreeItem.get());
    
    for (size_t tileset = 0; tileset < rtmd->getTrueNumFiles() - 1; tileset++)
        addModel(*rtmd, tileset, QString::asprintf("Tileset %zu", tileset));
}

void MainWindow::on_filesTree_itemDoubleClicked(QTreeWidgetItem *item, int)
{
    if (item->type() == QTreeWidgetItem::UserType)
    {
        auto kfmtItem = dynamic_cast<KFMTTreeWidgetItem *>(item);
        switch (kfmtItem->getType())
        {
            case KFMTDataType::KFMT_GAMEDB:
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
                break;
            }
            case KFMTDataType::KFMT_MAP:
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
                break;
            }
            case KFMTDataType::KFMT_MODEL:
            {
                auto* modelViewer = new ModelViewerWidget(ui->editorTabs);
                modelViewer->setModel(kfmtItem->getModel());
                ui->editorTabs->addTab(modelViewer, kfmtItem->text(0));
                ui->editorTabs->setCurrentWidget(modelViewer);
                ui->editorTabs->setTabIcon(ui->editorTabs->currentIndex(), QIcon(":/3d_icon.png"));
                break;
            }
            case KFMTDataType::KFMT_TEXTURE:
            {
                auto* textureViewer = new TextureViewer(ui->editorTabs);
                textureViewer->setTexture(kfmtItem->getTexture());
                ui->editorTabs->addTab(textureViewer, kfmtItem->text(0));
                ui->editorTabs->setCurrentWidget(textureViewer);
                ui->editorTabs->setTabIcon(ui->editorTabs->currentIndex(), QIcon(":/tex_icon.png"));
                break;
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
