#include "mainwindow.h"
#include "gamedbeditwidget.h"
#include "map.h"
#include "mapeditwidget.h"
#include "modelviewerwidget.h"
#include "texturedbviewer.h"
#include <QFileDialog>
#include <memory>

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
        
        loadTFile(*fdat, fdatTreeItem);
    }
    
    if (tfile_dir.exists("ITEM.T"))
    {
        item = std::make_unique<TFile>(tfile_dir.filePath("ITEM.T"));
    
        loadTFile(*item, itemTreeItem);
    }
    
    if (tfile_dir.exists("MO.T"))
    {
        mo = std::make_unique<TFile>(tfile_dir.filePath("MO.T"));
        
        loadTFile(*mo, moTreeItem);
    }
    
    if (tfile_dir.exists("RTIM.T"))
    {
        rtim = std::make_unique<TFile>(tfile_dir.filePath("RTIM.T"));
    
        loadTFile(*rtim, rtimTreeItem);
    }
    
    if (tfile_dir.exists("RTMD.T"))
    {
        rtmd = std::make_unique<TFile>(tfile_dir.filePath("RTMD.T"));
        
        loadTFile(*rtmd, rtmdTreeItem);
    }
    
    if (tfile_dir.exists("TALK.T"))
    {
        // We don't use C++14 so no make_unique :(
        talk = std::make_unique<TFile>(tfile_dir.filePath("TALK.T"));
    
        loadTFile(*talk, talkTreeItem);
    }
    
    for (int tab = ui->editorTabs->count() - 1; tab >= 0; tab++)
        ui->editorTabs->removeTab(tab);
}

void MainWindow::on_filesTree_itemDoubleClicked(QTreeWidgetItem *item_, int)
{
    if (item_->type() == QTreeWidgetItem::UserType)
    {
        auto kfmtItem = dynamic_cast<KFMTTreeWidgetItem *>(item_);
        
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
        case KFMTDataType::KFMT_TEXTUREDB:
        {
            auto* textureViewer = new TextureDBViewer(ui->editorTabs);
            textureViewer->setTextureDB(kfmtItem->getTextureDB());
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
    auto tFileItemCount = ui->filesTree->topLevelItemCount();
    
    // Bail out if files weren't loaded
    if (tFileItemCount == 0)
            return;
    
    for (auto tFileItemIndex = 0; tFileItemIndex < tFileItemCount; tFileItemIndex++)
    {
        auto tFileItem = ui->filesTree->topLevelItem(tFileItemIndex);
        for (auto childIndex = 0; childIndex < tFileItem->childCount(); childIndex++)
            dynamic_cast<KFMTTreeWidgetItem *>(tFileItem->child(childIndex))->writeChanges();
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
    
    writeTFile(*fdat, dir);
    writeTFile(*item, dir);
    writeTFile(*rtim, dir);
    writeTFile(*talk, dir);
    
    QMessageBox::information(this, "Changes saved successfully!", "Your changes have been saved!");
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
    
    std::shared_ptr<TextureDB> texture(new TextureDB(tFile, index));
    auto parentItem = ui->filesTree->findItems(tFile.getFilename(), Qt::MatchExactly).front();
    auto textureTreeItem = new KFMTTreeWidgetItem(parentItem, texture);
    textureTreeItem->setText(0, prettyName);
    parentItem->addChild(textureTreeItem);
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

void MainWindow::writeTFile(TFile &tFile, QDir directory)
{
    QFile tFileOut(directory.filePath(tFile.getFilename()));
    tFileOut.open(QIODevice::WriteOnly);
    tFileOut.write(tFile.getTFile());
    tFileOut.close();
}
