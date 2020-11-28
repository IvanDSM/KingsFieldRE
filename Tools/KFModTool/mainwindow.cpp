#include "mainwindow.h"
#include "gamedbeditwidget.h"
#include "map.h"
#include "mapeditwidget.h"
#include "modelviewerwidget.h"
#include "textureviewer.h"
#include <QFileDialog>
#include <memory>

#define TEST_GENERIC 1

void MainWindow::on_actionLoad_files_triggered()
{
    auto directory = QFileDialog::getExistingDirectory(this, "Select the folder with your King's Field T files.", QDir::homePath());
    if (directory.isEmpty())
        return;

    QDir tfile_dir(directory);
    curSourceDirectory = directory;
    if (tfile_dir.exists("FDAT.T"))
    {
        fdat = std::make_unique<TFile>(tfile_dir.filePath("FDAT.T"));
        
#if TEST_GENERIC
        loadTFile(*fdat, fdatTreeItem);
#else
        loadFdat();
#endif
    }
    
    if (tfile_dir.exists("ITEM.T"))
    {
        item = std::make_unique<TFile>(tfile_dir.filePath("ITEM.T"));
    
        loadTFile(*item, itemTreeItem);
    }
    
    if (tfile_dir.exists("MO.T"))
    {
        mo = std::make_unique<TFile>(tfile_dir.filePath("MO.T"));
        
#if TEST_GENERIC
        loadTFile(*mo, moTreeItem);
#else
        loadMo();
#endif
    }
    
    if (tfile_dir.exists("RTIM.T"))
    {
        rtim = std::make_unique<TFile>(tfile_dir.filePath("RTIM.T"));
    
        loadTFile(*rtim, rtimTreeItem);
    }
    
    if (tfile_dir.exists("RTMD.T"))
    {
        rtmd = std::make_unique<TFile>(tfile_dir.filePath("RTMD.T"));
        
#if TEST_GENERIC
        loadTFile(*rtmd, rtmdTreeItem);
#else
        loadRtmd();
#endif
    }
    
    if (tfile_dir.exists("TALK.T"))
    {
        // We don't use C++14 so no make_unique :(
        talk = std::make_unique<TFile>(tfile_dir.filePath("TALK.T"));
    
        loadTFile(*talk, talkTreeItem);
    }
    
    for (int tab = 0; tab < ui->editorTabs->count(); tab++)
        ui->editorTabs->removeTab(tab);
}

void MainWindow::addGameDB(TFile &tFile, unsigned int index)
{
    std::shared_ptr<GameDB> gameDB(new GameDB(tFile, index));
    auto parentItem = ui->filesTree->findItems(tFile.getFilename(), Qt::MatchExactly).front();
    auto gameDBTreeItem = new KFMTTreeWidgetItem(parentItem, gameDB);
    gameDBTreeItem->setText(0, "Game Database");

    parentItem->addChild(gameDBTreeItem);
}

void MainWindow::addMap(TFile &tFile, unsigned int index)
{
    auto prettyName = tFile.getPrettyName(index);
    if (prettyName.isEmpty())
        prettyName = tFile.getFilename() + ' ' + QString::number(index);
    
    std::shared_ptr<Map> map(new Map(tFile, index));
    auto parentItem = ui->filesTree->findItems(tFile.getFilename(), Qt::MatchExactly).front();
    auto mapTreeItem = new KFMTTreeWidgetItem(parentItem, map);
    mapTreeItem->setText(0, prettyName);

    parentItem->addChild(mapTreeItem);
}

void MainWindow::addModel(TFile &tFile, unsigned int index)
{
    auto prettyName = tFile.getPrettyName(index);
    if (prettyName.isEmpty())
        prettyName = tFile.getFilename() + ' ' + QString::number(index);
    
    std::shared_ptr<Model> model(new Model(tFile, index));
    auto parentItem = ui->filesTree->findItems(tFile.getFilename(), Qt::MatchExactly).front();
    auto modelTreeItem = new KFMTTreeWidgetItem(parentItem, model);
    modelTreeItem->setText(0, prettyName);
    parentItem->addChild(modelTreeItem);
}

void MainWindow::addTexture(TFile & tFile, unsigned int index)
{
    auto prettyName = tFile.getPrettyName(index);
    if (prettyName.isEmpty())
        prettyName = tFile.getFilename() + ' ' + QString::number(index);
    
    std::shared_ptr<Texture> texture(new Texture(tFile, index));
    auto parentItem = ui->filesTree->findItems(tFile.getFilename(), Qt::MatchExactly).front();
    auto textureTreeItem = new KFMTTreeWidgetItem(parentItem, texture);
    textureTreeItem->setText(0, prettyName);
    parentItem->addChild(textureTreeItem);
}

void MainWindow::loadFdat()
{
    if (fdat == nullptr)
        return;
    
    if (fdatTreeItem != nullptr)
    {
        ui->filesTree->removeItemWidget(fdatTreeItem.get(), 0);
        for (auto child : fdatTreeItem->takeChildren())
        {
            ui->filesTree->removeItemWidget(child, 0);
            delete child;
        }
    }
    
    fdatTreeItem = std::make_unique<QTreeWidgetItem>(ui->filesTree);
    fdatTreeItem->setIcon(0, QIcon(":/tfile_icon.png"));
    fdatTreeItem->setText(0, "FDAT.T");
    ui->filesTree->addTopLevelItem(fdatTreeItem.get());

    addMap(*fdat, 0);
    addMap(*fdat, 3);
    addMap(*fdat, 6);
    addMap(*fdat, 9);
    addMap(*fdat, 12);
    addMap(*fdat, 15);
    addMap(*fdat, 18);
    addMap(*fdat, 21);
    addMap(*fdat, 24);
    addGameDB(*fdat, 28);
    addModel(*fdat, 29);
    addModel(*fdat, 30);
    addModel(*fdat, 31);
    addModel(*fdat, 32);
    addModel(*fdat, 33);
    addModel(*fdat, 34);
    addModel(*fdat, 35);
    addModel(*fdat, 36);
    addModel(*fdat, 37);
    addModel(*fdat, 38);
    addModel(*fdat, 39);
    addModel(*fdat, 40);
    addModel(*fdat, 41);
    addModel(*fdat, 42);
    addModel(*fdat, 43);
    addModel(*fdat, 44);
}

void MainWindow::loadMo()
{
    if (mo == nullptr)
        return;
    
    if (moTreeItem != nullptr)
    {
        ui->filesTree->removeItemWidget(moTreeItem.get(), 0);
        for (auto child : moTreeItem->takeChildren())
        {
            ui->filesTree->removeItemWidget(child, 0);
            delete child;
        }
    }
    
    moTreeItem = std::make_unique<QTreeWidgetItem>(ui->filesTree);
    moTreeItem->setIcon(0, QIcon(":/tfile_icon.png"));
    moTreeItem->setText(0, "MO.T");
    ui->filesTree->addTopLevelItem(moTreeItem.get());
    
    for (size_t moFile = 0; moFile < mo->getTrueNumFiles() - 1; moFile++)
        addModel(*mo, moFile);
}

void MainWindow::loadRtmd()
{
    if (rtmd == nullptr)
        return;
    
    if (rtmdTreeItem != nullptr)
    {
        ui->filesTree->removeItemWidget(rtmdTreeItem.get(), 0);
        for (auto child : rtmdTreeItem->takeChildren())
        {
            ui->filesTree->removeItemWidget(child, 0);
            delete child;
        }
    }
    
    rtmdTreeItem = std::make_unique<QTreeWidgetItem>(ui->filesTree);
    rtmdTreeItem->setIcon(0, QIcon(":/tfile_icon.png"));
    rtmdTreeItem->setText(0, "RTMD.T");
    ui->filesTree->addTopLevelItem(rtmdTreeItem.get());
    
    for (size_t tileset = 0; tileset < rtmd->getTrueNumFiles() - 1; tileset++)
        addModel(*rtmd, tileset);
}

void MainWindow::loadTFile(TFile &tFile, std::unique_ptr<QTreeWidgetItem> &tFileTreeItem)
{
    if (tFileTreeItem.get() != nullptr)
    {
        ui->filesTree->removeItemWidget(tFileTreeItem.get(), 0);
        for (auto child : tFileTreeItem->takeChildren())
        {
            ui->filesTree->removeItemWidget(child, 0);
            delete child;
        }
    }
    
    tFileTreeItem = std::make_unique<QTreeWidgetItem>(ui->filesTree);
    tFileTreeItem->setIcon(0, QIcon(":/tfile_icon.png"));
    tFileTreeItem->setText(0, tFile.getFilename());
    ui->filesTree->addTopLevelItem(tFileTreeItem.get());
    
    for (size_t fileIndex = 0; fileIndex < tFile.getTrueNumFiles() - 1; fileIndex++)
    {
        auto file = tFile.getFile(fileIndex);
        if (TFile::isTMD(file))
            addModel(tFile, fileIndex);
        else if (TFile::isTIM(file) || TFile::isRTIM(file))
            addTexture(tFile, fileIndex);
        else if (TFile::isRTMD(file))
            addModel(tFile, fileIndex);
        else if (TFile::isMO(file))
            addModel(tFile, fileIndex);
        else if (TFile::isMAP1(file))
            addMap(tFile, fileIndex);
    }
}

void MainWindow::on_filesTree_itemDoubleClicked(QTreeWidgetItem *item, int)
{
    if (item->type() == QTreeWidgetItem::UserType)
    {
        auto kfmtItem = dynamic_cast<KFMTTreeWidgetItem *>(item);
        
        // Check to see if there is already a tab for this item
        auto tabForItem = openTabs.find(kfmtItem->text(0));
        if (tabForItem != openTabs.end())
        {
            // If there is one, switch to it and leave the function
            ui->editorTabs->setCurrentWidget(tabForItem->second);
            return;
        }
        
        // Otherwise, create tab for the item
        switch (kfmtItem->getType())
        {
            case KFMTDataType::KFMT_GAMEDB:
            {
                auto gameDBEditor = new GameDBEditWidget(ui->editorTabs, kfmtItem->getDB());
                ui->editorTabs->addTab(gameDBEditor, "Game Database");
                ui->editorTabs->setCurrentWidget(gameDBEditor);
                ui->editorTabs->setTabIcon(ui->editorTabs->currentIndex(), QIcon(":/db_icon.png"));
                break;
            }
            case KFMTDataType::KFMT_MAP:
            {
                auto map = kfmtItem->getMap();
                auto* mapEditor = new MapEditWidget(ui->editorTabs);
                mapEditor->setMap(map);
                ui->editorTabs->addTab(mapEditor, kfmtItem->text(0));
                ui->editorTabs->setCurrentWidget(mapEditor);
                ui->editorTabs->setTabIcon(ui->editorTabs->currentIndex(), QIcon(":/map_icon.png"));
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
        
        // Add tab to the tab list
        openTabs.emplace(kfmtItem->text(0), ui->editorTabs->currentWidget());
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
