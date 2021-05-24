#include "mainwindow.h"
#include "gamedbeditwidget.h"
#include "map.h"
#include "mapeditwidget.h"
#include "modelviewerwidget.h"
#include "texturedbviewer.h"
#include "utilities.h"
#include <QFileDialog>
#include <memory>

void MainWindow::on_actionLoad_files_triggered()
{
    auto directory = QFileDialog::getExistingDirectory(this, "Select the root folder of your King's Field CD.", QDir::homePath());
    if (directory.isEmpty())
        return;

    QDir srcDir(directory);
    curSourceDirectory = directory;
    
    files.clear();
    
    if (srcDir.exists("KFIELD.EXE") && srcDir.exists("MAP.001"))
        loadJDemo();
    else if (srcDir.exists("PSX.EXE") && srcDir.exists("E0") && srcDir.exists("E1") 
             && srcDir.exists("E2") && srcDir.exists("E3"))
        loadJ();
    else if ((srcDir.exists("SLUS_001.58") || srcDir.exists("SLPS_910.03") || srcDir.exists("PSX.EXE"))
        && srcDir.exists("END.EXE"))
        load2J();
    else if (srcDir.exists("SCES_005.10") && srcDir.exists("END.EXE") && srcDir.exists("LICENSEE.DAT"))
        loadEU();
    else if ((srcDir.exists("SLUS_002.55") || srcDir.exists("SLPS_003.77") || srcDir.exists("SLPM_800.29")) 
             && srcDir.exists("LOAD.MSG"))
        load3JorPS();
    else if (srcDir.exists("SLPS_009.00"))
        loadACProto();
    else if (srcDir.exists("USA10.EXE"))
        loadACSampler4Demo();

    for (int tab = ui->editorTabs->count() - 1; tab >= 0; tab++) ui->editorTabs->removeTab(tab);
}

void MainWindow::on_filesTree_itemDoubleClicked(QTreeWidgetItem *item_, int)
{
    if (item_->type() == QTreeWidgetItem::UserType)
    {
        auto *kfmtItem = dynamic_cast<KFMTTreeWidgetItem *>(item_);
        
        // Check to see if there is already a tab for this item
        auto tabForItem = openTabs.find(kfmtItem->text(0));
        if (tabForItem != openTabs.end())
        {
            // If there is one, switch to it and leave the function
            ui->editorTabs->setCurrentWidget(tabForItem->second);
            return;
        }
        
        // Builds the item's contents if necessary
        kfmtItem->build();
        
        // Otherwise, create tab for the item
        switch (kfmtItem->getType())
        {
            case KFMTDataType::KFMT_GAMEDB:
            {
                auto *gameDBEditor = new GameDBEditWidget(ui->editorTabs, kfmtItem->getDB());
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
    
    writeFiles(dir);
    
    QMessageBox::information(this, "Changes saved successfully!", "Your changes have been saved!");
}

KFMTTreeWidgetItem *MainWindow::addGameDB(QTreeWidgetItem * parent, QByteArray &file)
{
    auto *gameDBTreeItem = new KFMTTreeWidgetItem(parent, file, KFMTDataType::KFMT_GAMEDB);
    gameDBTreeItem->setText(0, "Game Database");

    if (parent != nullptr)
        parent->addChild(gameDBTreeItem);
    else
        ui->filesTree->addTopLevelItem(gameDBTreeItem);
    
    return gameDBTreeItem;
}

KFMTTreeWidgetItem *MainWindow::addMap(QTreeWidgetItem *parent, QByteArray &file1, QByteArray &file2, 
                                       QByteArray &file3, const QString &filename)
{
    auto *mapTreeItem = new KFMTTreeWidgetItem(parent, file1, file2, file3, KFMTDataType::KFMT_MAP);
    mapTreeItem->setText(0, filename);

    if (parent != nullptr)
        parent->addChild(mapTreeItem);
    else
        ui->filesTree->addTopLevelItem(mapTreeItem);
    
    return mapTreeItem;
}

KFMTTreeWidgetItem *MainWindow::addModel(QTreeWidgetItem *parent, QByteArray &file, const QString &filename)
{
    auto *modelTreeItem = new KFMTTreeWidgetItem(parent, file, KFMTDataType::KFMT_MODEL);
    modelTreeItem->setText(0, filename);
    
    if (parent != nullptr)
        parent->addChild(modelTreeItem);
    else
        ui->filesTree->addTopLevelItem(modelTreeItem);
    
    return modelTreeItem;
}

KFMTTreeWidgetItem *MainWindow::addTexture(QTreeWidgetItem *parent, QByteArray &file, const QString &filename)
{
    auto *textureTreeItem = new KFMTTreeWidgetItem(parent, file, KFMTDataType::KFMT_TEXTUREDB);
    textureTreeItem->setText(0, filename);
    
    if (parent != nullptr)
        parent->addChild(textureTreeItem);
    else
        ui->filesTree->addTopLevelItem(textureTreeItem);
    
    return textureTreeItem;
}

void MainWindow::loadJDemo()
{
    loadRawFile("MAP/M561.TIM");
    loadRawFile("TIM/10301.TIM");
    loadRawFile("TIM/10302.TIM");
    loadRawFile("TIM/10303.TIM");
    loadRawFile("TIM/10401.TIM");
    loadRawFile("TIM/10402.TIM");
    loadRawFile("TIM/10403.TIM");
    loadRawFile("TIM/10901.TIM");
    loadRawFile("TIM/10902.TIM");
    loadRawFile("TIM/10903.TIM");
    loadRawFile("TIM/11301.TIM");
    loadRawFile("TIM/11302.TIM");
    loadRawFile("TIM/11303.TIM");
    loadRawFile("TIM/M001.TIM");
    loadRawFile("TIM/M002.TIM");
    loadRawFile("TIM/M003.TIM");
    loadRawFile("TIM/M004.TIM");
    loadRawFile("TIM/M005.TIM");
    loadRawFile("TIM/M006.TIM");
    loadRawFile("TIM/M007.TIM");
    loadRawFile("TIM/M008.TIM");
    loadRawFile("TIM/M009.TIM");
    loadRawFile("TIM/M010.TIM");
    loadRawFile("TIM/M011.TIM");
    loadRawFile("TIM/M012.TIM");
    loadRawFile("TMD/I001.TMD");
    loadRawFile("TMD/I002.TMD");
    loadRawFile("TMD/I003.TMD");
    loadRawFile("TMD/I004.TMD");
    loadRawFile("TMD/I005.TMD");
    loadRawFile("TMD/I006.TMD");
    loadRawFile("TMD/I007.TMD");
    loadRawFile("TMD/I008.TMD");
    loadRawFile("TMD/I009.TMD");
    loadRawFile("TMD/I012.TMD");
    loadRawFile("TMD/I040.TMD");
    loadRawFile("TMD/I041.TMD");
    loadRawFile("TMD/I044.TMD");
    loadRawFile("TMD/I045.TMD");
    loadRawFile("TMD/I053.TMD");
    loadRawFile("TMD/I055.TMD");
    loadRawFile("TMD/I056.TMD");
    loadRawFile("TMD/I057.TMD");
    loadRawFile("TMD/MIX.TMD");
    loadMIXFile("MIX.TIM");
    loadRawFile("FANM.TMD");
    loadRawFile("ITMTMD.001");
    loadRawFile("MIX.TMD");
}

void MainWindow::loadJ()
{
    loadMIXFile("KF/B0/L0");
    loadMIXFile("KF/B0/MIX0");
    loadMIXFile("KF/B0/MIX3");
    loadMIXFile("KF/B0/MIX9");
    loadMIXFile("KF/B0/MIXB0");
    loadMIXFile("KF/B0/MIXB3");
    loadMIXFile("KF/B0/MIXBE");
    loadMIXFile("KF/B1/MIX.TIM");
    loadMIXFile("KF/B1/MIXB.DAT");
    loadMIXFile("KF/B2/MIX.TIM");
    loadMIXFile("KF/B2/MIXB.DAT");
    loadMIXFile("KF/B3/MIX.TIM");
    loadMIXFile("KF/B3/MIXB.DAT");
    loadMIXFile("KF/B4/MIX.TIM");
    loadMIXFile("KF/B4/MIXB.DAT");
    loadMIXFile("KF/B5/MIX.TIM");
    loadMIXFile("KF/B5/MIXB.DAT");
    loadMIXFile("KF/COM/MIX.TIM");
    loadRawFile("KF/ENE1/EI00.TIM");
    loadRawFile("KF/ENE1/EI01.TIM");
    loadRawFile("KF/ENE1/EI02.TIM");
    loadRawFile("KF/ENE1/EI03.TIM");
    loadRawFile("KF/ENE1/EI04.TIM");
    loadRawFile("KF/ENE1/EI05.TIM");
    loadRawFile("KF/ENE1/EI06.TIM");
    loadRawFile("KF/ENE1/EI07.TIM");
    loadRawFile("KF/ENE1/EI08.TIM");
    loadRawFile("KF/ENE1/EI09.TIM");
    loadRawFile("KF/ENE2/EI00.TIM");
    loadRawFile("KF/ENE2/EI01.TIM");
    loadRawFile("KF/ENE2/EI02.TIM");
    loadRawFile("KF/ENE2/EI03.TIM");
    loadRawFile("KF/ENE2/EI04.TIM");
    loadRawFile("KF/ENE2/EI05.TIM");
    loadRawFile("KF/ENE2/EI06.TIM");
    loadRawFile("KF/ENE2/EI07.TIM");
    loadRawFile("KF/ENE2/EI08.TIM");
    loadRawFile("KF/ENE2/EI09.TIM");
    loadRawFile("KF/ENE3/EI00.TIM");
    loadRawFile("KF/ENE3/EI01.TIM");
    loadRawFile("KF/ENE3/EI02.TIM");
    loadRawFile("KF/ENE3/EI03.TIM");
    loadRawFile("KF/ENE3/EI04.TIM");
    loadRawFile("KF/ENE3/EI05.TIM");
    loadRawFile("KF/ENE3/EI06.TIM");
    loadRawFile("KF/ENE4/EI00.TIM");
    loadRawFile("KF/ENE4/EI01.TIM");
    loadRawFile("KF/ENE4/EI02.TIM");
    loadRawFile("KF/ENE4/EI03.TIM");
    loadRawFile("KF/ENE4/EI04.TIM");
    loadRawFile("KF/ENE4/EI05.TIM");
    loadRawFile("KF/ENE4/EI06.TIM");
    loadRawFile("KF/ENE4/EI07.TIM");
    loadRawFile("KF/ENE5/EI00.TIM");
    loadRawFile("KF/ENE5/EI01.TIM");
    loadRawFile("KF/ENE5/EI02.TIM");
    loadRawFile("KF/ENE5/EI03.TIM");
    loadRawFile("KF/ENE5/EI04.TIM");
    loadRawFile("KF/ENE5/EI05.TIM");
    loadRawFile("KF/ENE5/EI06.TIM");
    loadRawFile("KF/ENE5/EI07.TIM");
    loadRawFile("KF/ENE5/EI08.TIM");
    loadRawFile("KF/ITEM1/I001.TMD");
    loadRawFile("KF/ITEM1/I002.TMD");
    loadRawFile("KF/ITEM1/I003.TMD");
    loadRawFile("KF/ITEM1/I004.TMD");
    loadRawFile("KF/ITEM1/I005.TMD");
    loadRawFile("KF/ITEM1/I006.TMD");
    loadRawFile("KF/ITEM1/I007.TMD");
    loadRawFile("KF/ITEM1/I008.TMD");
    loadRawFile("KF/ITEM1/I009.TMD");
    loadRawFile("KF/ITEM1/I010.TMD");
    loadRawFile("KF/ITEM1/I011.TMD");
    loadRawFile("KF/ITEM1/I012.TMD");
    loadRawFile("KF/ITEM1/I014.TMD");
    loadRawFile("KF/ITEM1/I015.TMD");
    loadRawFile("KF/ITEM1/I016.TMD");
    loadRawFile("KF/ITEM1/I017.TMD");
    loadRawFile("KF/ITEM1/I018.TMD");
    loadRawFile("KF/ITEM1/I020.TMD");
    loadRawFile("KF/ITEM1/I021.TMD");
    loadRawFile("KF/ITEM1/I022.TMD");
    loadRawFile("KF/ITEM1/I023.TMD");
    loadRawFile("KF/ITEM1/I024.TMD");
    loadRawFile("KF/ITEM1/I025.TMD");
    loadRawFile("KF/ITEM1/I027.TMD");
    loadRawFile("KF/ITEM1/I028.TMD");
    loadRawFile("KF/ITEM1/I029.TMD");
    loadRawFile("KF/ITEM1/I030.TMD");
    loadRawFile("KF/ITEM2/I031.TMD");
    loadRawFile("KF/ITEM2/I033.TMD");
    loadRawFile("KF/ITEM2/I034.TMD");
    loadRawFile("KF/ITEM2/I035.TMD");
    loadRawFile("KF/ITEM2/I036.TMD");
    loadRawFile("KF/ITEM2/I037.TMD");
    loadRawFile("KF/ITEM2/I038.TMD");
    loadRawFile("KF/ITEM2/I039.TMD");
    loadRawFile("KF/ITEM2/I040.TMD");
    loadRawFile("KF/ITEM2/I041.TMD");
    loadRawFile("KF/ITEM2/I042.TMD");
    loadRawFile("KF/ITEM2/I043.TMD");
    loadRawFile("KF/ITEM2/I044.TMD");
    loadRawFile("KF/ITEM2/I045.TMD");
    loadRawFile("KF/ITEM2/I046.TMD");
    loadRawFile("KF/ITEM2/I047.TMD");
    loadRawFile("KF/ITEM2/I048.TMD");
    loadRawFile("KF/ITEM2/I049.TMD");
    loadRawFile("KF/ITEM2/I050.TMD");
    loadRawFile("KF/ITEM2/I051.TMD");
    loadRawFile("KF/ITEM2/I052.TMD");
    loadRawFile("KF/ITEM2/I053.TMD");
    loadRawFile("KF/ITEM2/I054.TMD");
    loadRawFile("KF/ITEM2/I055.TMD");
    loadRawFile("KF/ITEM2/I056.TMD");
    loadRawFile("KF/ITEM2/I057.TMD");
    loadRawFile("KF/ITEM2/I058.TMD");
    loadRawFile("KF/ITEM2/I059.TMD");
    loadRawFile("KF/ITEM2/I060.TMD");
    loadRawFile("KF/ITEM3/I061.TMD");
    loadRawFile("KF/ITEM3/I062.TMD");
    loadRawFile("KF/ITEM3/I063.TMD");
    loadRawFile("KF/ITEM3/I064.TMD");
    loadRawFile("KF/ITEM3/I065.TMD");
    loadRawFile("KF/ITEM3/I069.TMD");
    loadRawFile("KF/ITEM3/I070.TMD");
    loadRawFile("KF/ITEM3/I074.TMD");
    loadRawFile("KF/ITEM3/I075.TMD");
    loadRawFile("KF/ITEM4/I106.TMD");
    loadRawFile("KF/ITEM4/I110.TMD");
    loadRawFile("KF/KAN/B1/K000.TIM");
    loadRawFile("KF/KAN/B1/K001.TIM");
    loadRawFile("KF/KAN/B1/K002.TIM");
    loadRawFile("KF/KAN/B1/K003.TIM");
    loadRawFile("KF/KAN/B1/K004.TIM");
    loadRawFile("KF/KAN/B1/K005.TIM");
    loadRawFile("KF/KAN/B1/K006.TIM");
    loadRawFile("KF/KAN/B1/K007.TIM");
    loadRawFile("KF/KAN/B1/K008.TIM");
    loadRawFile("KF/KAN/B1/K100.TIM");
    loadRawFile("KF/KAN/B1/K101.TIM");
    loadRawFile("KF/KAN/B1/K102.TIM");
    loadRawFile("KF/KAN/B1/K103.TIM");
    loadRawFile("KF/KAN/B2/K000.TIM");
    loadRawFile("KF/KAN/B2/K001.TIM");
    loadRawFile("KF/KAN/B2/K002.TIM");
    loadRawFile("KF/KAN/B2/K003.TIM");
    loadRawFile("KF/KAN/B2/K004.TIM");
    loadRawFile("KF/KAN/B2/K005.TIM");
    loadRawFile("KF/KAN/B2/K006.TIM");
    loadRawFile("KF/KAN/B2/K100.TIM");
    loadRawFile("KF/KAN/B2/K101.TIM");
    loadRawFile("KF/KAN/B2/K102.TIM");
    loadRawFile("KF/KAN/B3/K000.TIM");
    loadRawFile("KF/KAN/B3/K001.TIM");
    loadRawFile("KF/KAN/B3/K002.TIM");
    loadRawFile("KF/KAN/B3/K003.TIM");
    loadRawFile("KF/KAN/B3/K004.TIM");
    loadRawFile("KF/KAN/B3/K101.TIM");
    loadRawFile("KF/KAN/B3/K102.TIM");
    loadRawFile("KF/KAN/B3/K103.TIM");
    loadRawFile("KF/KAN/B3/K104.TIM");
    loadRawFile("KF/KAN/B4/K000.TIM");
    loadRawFile("KF/KAN/B4/K001.TIM");
    loadRawFile("KF/KAN/B4/K002.TIM");
    loadRawFile("KF/KAN/B4/K004.TIM");
    loadRawFile("KF/KAN/B4/K101.TIM");
    loadRawFile("KF/KAN/B4/K102.TIM");
    loadRawFile("KF/KAN/B4/K103.TIM");
    loadRawFile("KF/MAP/M11");
    loadRawFile("KF/MAP/M12");
    loadRawFile("KF/MAP/M13");
    loadRawFile("KF/MAP/M14");
    loadRawFile("KF/MAP/M15");
    loadRawFile("KF/MAP/M21");
    loadRawFile("KF/MAP/M22");
    loadRawFile("KF/MAP/M23");
    loadRawFile("KF/MAP/M24");
    loadRawFile("KF/MAP/M25");
    loadRawFile("KF/PRSN/PER01.TIM");
    loadRawFile("KF/PRSN/PER02.TIM");
    loadRawFile("KF/PRSN/PER03.TIM");
    loadRawFile("KF/PRSN/PER04.TIM");
    loadRawFile("KF/PRSN/PER05.TIM");
    loadRawFile("KF/PRSN/PER06.TIM");
    loadRawFile("KF/PRSN/PER07.TIM");
    loadRawFile("KF/PRSN/PER08.TIM");
    loadRawFile("KF/PRSN/PER09.TIM");
    loadRawFile("KF/PRSN/PER10.TIM");
    loadRawFile("KF/PRSN/PER11.TIM");
    loadRawFile("KF/PRSN/PER12.TIM");
    loadRawFile("KF/PRSN/PER13.TIM");
    loadRawFile("KF/PRSN/PER14.TIM");
    loadRawFile("KF/PRSN/PER15.TIM");
    loadRawFile("KF/PRSN/PER16.TIM");
    loadRawFile("KF/PRSN/PER17.TIM");
    loadRawFile("KF/TALK/C01/T11011.TIM");
    loadRawFile("KF/TALK/C01/T11012.TIM");
    loadRawFile("KF/TALK/C01/T11013.TIM");
    loadRawFile("KF/TALK/C01/T11014.TIM");
    loadRawFile("KF/TALK/C01/T11015.TIM");
    loadRawFile("KF/TALK/C01/T11016.TIM");
    loadRawFile("KF/TALK/C01/T11017.TIM");
    loadRawFile("KF/TALK/C01/T11018.TIM");
    loadRawFile("KF/TALK/C01/T11019.TIM");
    loadRawFile("KF/TALK/C01/T12011.TIM");
    loadRawFile("KF/TALK/C01/T12012.TIM");
    loadRawFile("KF/TALK/C01/T12013.TIM");
    loadRawFile("KF/TALK/C01/T13011.TIM");
    loadRawFile("KF/TALK/C01/T14011.TIM");
    loadRawFile("KF/TALK/C01/T15011.TIM");
    loadRawFile("KF/TALK/C02/T11021.TIM");
    loadRawFile("KF/TALK/C02/T11022.TIM");
    loadRawFile("KF/TALK/C02/T11023.TIM");
    loadRawFile("KF/TALK/C02/T11024.TIM");
    loadRawFile("KF/TALK/C02/T11025.TIM");
    loadRawFile("KF/TALK/C02/T11026.TIM");
    loadRawFile("KF/TALK/C02/T11027.TIM");
    loadRawFile("KF/TALK/C02/T11028.TIM");
    loadRawFile("KF/TALK/C02/T11029.TIM");
    loadRawFile("KF/TALK/C02/T12021.TIM");
    loadRawFile("KF/TALK/C02/T12022.TIM");
    loadRawFile("KF/TALK/C02/T12023.TIM");
    loadRawFile("KF/TALK/C02/T12045.TIM");
    loadRawFile("KF/TALK/C02/T13021.TIM");
    loadRawFile("KF/TALK/C02/T14021.TIM");
    loadRawFile("KF/TALK/C02/T15021.TIM");
    loadRawFile("KF/TALK/C03/T11031.TIM");
    loadRawFile("KF/TALK/C03/T11032.TIM");
    loadRawFile("KF/TALK/C03/T11033.TIM");
    loadRawFile("KF/TALK/C03/T11034.TIM");
    loadRawFile("KF/TALK/C03/T11035.TIM");
    loadRawFile("KF/TALK/C03/T11036.TIM");
    loadRawFile("KF/TALK/C03/T11037.TIM");
    loadRawFile("KF/TALK/C03/T11038.TIM");
    loadRawFile("KF/TALK/C03/T12031.TIM");
    loadRawFile("KF/TALK/C03/T12032.TIM");
    loadRawFile("KF/TALK/C03/T12035.TIM");
    loadRawFile("KF/TALK/C03/T13031.TIM");
    loadRawFile("KF/TALK/C03/T13032.TIM");
    loadRawFile("KF/TALK/C03/T14031.TIM");
    loadRawFile("KF/TALK/C03/T15031.TIM");
    loadRawFile("KF/TALK/C04/T11041.TIM");
    loadRawFile("KF/TALK/C04/T11042.TIM");
    loadRawFile("KF/TALK/C04/T11043.TIM");
    loadRawFile("KF/TALK/C04/T11044.TIM");
    loadRawFile("KF/TALK/C04/T11045.TIM");
    loadRawFile("KF/TALK/C04/T11046.TIM");
    loadRawFile("KF/TALK/C04/T11047.TIM");
    loadRawFile("KF/TALK/C04/T11048.TIM");
    loadRawFile("KF/TALK/C04/T12041.TIM");
    loadRawFile("KF/TALK/C04/T12042.TIM");
    loadRawFile("KF/TALK/C04/T12043.TIM");
    loadRawFile("KF/TALK/C04/T12044.TIM");
    loadRawFile("KF/TALK/C04/T12045.TIM");
    loadRawFile("KF/TALK/C04/T13041.TIM");
    loadRawFile("KF/TALK/C04/T13042.TIM");
    loadRawFile("KF/TALK/C04/T14041.TIM");
    loadRawFile("KF/TALK/C04/T14042.TIM");
    loadRawFile("KF/TALK/C04/T15041.TIM");
    loadRawFile("KF/TALK/C05/T44051.TIM");
    loadRawFile("KF/TALK/C05/T44052.TIM");
    loadRawFile("KF/TALK/C05/T44053.TIM");
    loadRawFile("KF/TALK/C06/T22061.TIM");
    loadRawFile("KF/TALK/C06/T22062.TIM");
    loadRawFile("KF/TALK/C06/T22063.TIM");
    loadRawFile("KF/TALK/C06/T22064.TIM");
    loadRawFile("KF/TALK/C06/T22065.TIM");
    loadRawFile("KF/TALK/C06/T22066.TIM");
    loadRawFile("KF/TALK/C06/T22067.TIM");
    loadRawFile("KF/TALK/C06/T22068.TIM");
    loadRawFile("KF/TALK/C06/T22069.TIM");
    loadRawFile("KF/TALK/C06/T33061.TIM");
    loadRawFile("KF/TALK/C06/T33062.TIM");
    loadRawFile("KF/TALK/C06/T33063.TIM");
    loadRawFile("KF/TALK/C06/T33064.TIM");
    loadRawFile("KF/TALK/C06/T33065.TIM");
    loadRawFile("KF/TALK/C06/T33066.TIM");
    loadRawFile("KF/TALK/C06/T33067.TIM");
    loadRawFile("KF/TALK/C06/T33068.TIM");
    loadRawFile("KF/TALK/C06/T33069.TIM");
    loadRawFile("KF/TALK/C06/T34061.TIM");
    loadRawFile("KF/TALK/C06/T34062.TIM");
    loadRawFile("KF/TALK/C06/T35061.TIM");
    loadRawFile("KF/TALK/C06/T35062.TIM");
    loadRawFile("KF/TALK/C06/T35063.TIM");
    loadRawFile("KF/TALK/C06/T35064.TIM");
    loadRawFile("KF/TALK/C07/T22071.TIM");
    loadRawFile("KF/TALK/C07/T22072.TIM");
    loadRawFile("KF/TALK/C07/T22073.TIM");
    loadRawFile("KF/TALK/C07/T22074.TIM");
    loadRawFile("KF/TALK/C07/T22075.TIM");
    loadRawFile("KF/TALK/C07/T23071.TIM");
    loadRawFile("KF/TALK/C07/T23072.TIM");
    loadRawFile("KF/TALK/C08/T22081.TIM");
    loadRawFile("KF/TALK/C08/T22082.TIM");
    loadRawFile("KF/TALK/C08/T22083.TIM");
    loadRawFile("KF/TALK/C08/T22084.TIM");
    loadRawFile("KF/TALK/C08/T22085.TIM");
    loadRawFile("KF/TALK/C08/T22086.TIM");
    loadRawFile("KF/TALK/C08/T22087.TIM");
    loadRawFile("KF/TALK/C08/T23081.TIM");
    loadRawFile("KF/TALK/C08/T23082.TIM");
    loadRawFile("KF/TALK/C08/T23083.TIM");
    loadRawFile("KF/TALK/C08/T24081.TIM");
    loadRawFile("KF/TALK/C08/T24082.TIM");
    loadRawFile("KF/TALK/C08/T25081.TIM");
    loadRawFile("KF/TALK/C08/T25082.TIM");
    loadRawFile("KF/TALK/C08/T25083.TIM");
    loadRawFile("KF/TALK/C09/T11091.TIM");
    loadRawFile("KF/TALK/C09/T11092.TIM");
    loadRawFile("KF/TALK/C09/T11093.TIM");
    loadRawFile("KF/TALK/C09/T11094.TIM");
    loadRawFile("KF/TALK/C09/T11095.TIM");
    loadRawFile("KF/TALK/C09/T11096.TIM");
    loadRawFile("KF/TALK/C09/T12091.TIM");
    loadRawFile("KF/TALK/C09/T12092.TIM");
    loadRawFile("KF/TALK/C09/T13091.TIM");
    loadRawFile("KF/TALK/C09/T13092.TIM");
    loadRawFile("KF/TALK/C11/T22111.TIM");
    loadRawFile("KF/TALK/C11/T55111.TIM");
    loadRawFile("KF/TALK/C11/T55112.TIM");
    loadRawFile("KF/TALK/C11/T55113.TIM");
    loadRawFile("KF/TALK/C12/T33121.TIM");
    loadRawFile("KF/TALK/C12/T33122.TIM");
    loadRawFile("KF/TALK/C12/T33123.TIM");
    loadRawFile("KF/TALK/C12/T34121.TIM");
    loadRawFile("KF/TALK/C13/T11131.TIM");
    loadRawFile("KF/TALK/C13/T11132.TIM");
    loadRawFile("KF/TALK/C13/T11133.TIM");
    loadRawFile("KF/TALK/C13/T11134.TIM");
    loadRawFile("KF/TALK/C13/T11135.TIM");
    loadRawFile("KF/TALK/C13/T11136.TIM");
    loadRawFile("KF/TALK/C13/T11137.TIM");
    loadRawFile("KF/TALK/C13/T11138.TIM");
    loadRawFile("KF/TALK/C13/T12131.TIM");
    loadRawFile("KF/TALK/C13/T12132.TIM");
    loadRawFile("KF/TALK/C13/T12133.TIM");
    loadRawFile("KF/TALK/C13/T12134.TIM");
    loadRawFile("KF/TALK/C13/T12135.TIM");
    loadRawFile("KF/TALK/C13/T12136.TIM");
    loadRawFile("KF/TALK/C14/T44141.TIM");
    loadRawFile("KF/TALK/C15/T44151.TIM");
    loadRawFile("KF/TALK/C17/T55171.TIM");
    loadRawFile("KF/TALK/C17/T55172.TIM");
    loadRawFile("KF/TIM/ICO1.TIM");
    loadRawFile("KF/TIM/ICO2.TIM");
    loadRawFile("KF/TIM/ICO3.TIM");
    loadRawFile("KF/TIM/M001");
    loadRawFile("KF/TIM/M002");
    loadRawFile("KF/TIM/M003");
    loadRawFile("KF/TIM/M004");
    loadRawFile("KF/TIM/M005");
    loadRawFile("KF/TIM/M006");
    loadRawFile("KF/TIM/M007");
    loadRawFile("KF/TIM/M008");
    loadRawFile("KF/TIM/M009");
    loadRawFile("KF/TIM/M101");
    loadRawFile("KF/TIM/M102");
    loadRawFile("KF/TIM/M103");
    loadRawFile("KF/TIM/M104");
    loadRawFile("KF/TIM/M105");
    loadRawFile("KF/TIM/M106");
    loadRawFile("KF/TIM/M107");
    loadRawFile("KF/TIM/M108");
    loadRawFile("KF/TIM/M109");
    loadRawFile("KF/TIM/M110");
    loadRawFile("KF/TIM/M111");
    loadRawFile("KF/TIM/M112");
    loadRawFile("KF/TIM/M113");
    loadRawFile("KF/TIM/M114");
    loadRawFile("KF/TIM/M115");
    loadRawFile("KF/TIM/M999");
    loadRawFile("E0");
    loadRawFile("E1");
    loadRawFile("E2");
    loadRawFile("E3");
}

void MainWindow::load2J()
{
    loadTFile("CD/COM/FDAT.T");
    loadTFile("CD/COM/ITEM.T");
    loadTFile("CD/COM/MO.T");
    loadTFile("CD/COM/RTIM.T");
    loadTFile("CD/COM/RTMD.T");
    loadTFile("CD/COM/TALK.T");
    loadTFile("CD/COM/VAB.T");
    // TODO: ED.D is weird and thus unsupported.
    //loadMIXFile("OP/ED.D");
    loadMIXFile("OP/OP.D");
    loadMIXFile("OP/OPU.D"); // This is only for the US version
}

void MainWindow::loadEU()
{
    loadTFile("CD/COM/FDAT.T");
    loadTFile("CD/COM/ITEM0.T");
    loadTFile("CD/COM/ITEM1.T");
    loadTFile("CD/COM/ITEM2.T");
    loadTFile("CD/COM/MO.T");
    loadTFile("CD/COM/RTIM.T");
    loadTFile("CD/COM/RTMD.T");
    loadTFile("CD/COM/TALK0.T");
    loadTFile("CD/COM/TALK1.T");
    loadTFile("CD/COM/TALK2.T");
    loadTFile("CD/COM/VAB.T");
    loadRawFile("CD/MSG0.TIM");
    loadRawFile("CD/MSG1.TIM");
    loadRawFile("CD/MSG2.TIM");
    loadMIXFile("OP/EUR.D");
    loadMIXFile("OP/OP.D");
}

void MainWindow::load3JorPS()
{
    loadTFile("CD/COM/FDAT.T");
    loadTFile("CD/COM/ITEM.T");
    loadTFile("CD/COM/MO.T");
    loadTFile("CD/COM/MOF.T");
    loadTFile("CD/COM/RTIM.T");
    loadTFile("CD/COM/RTMD.T");
    loadTFile("CD/COM/STALK.T");
    loadTFile("CD/COM/TALK.T");
    loadTFile("CD/COM/VAB.T");
    loadMIXFile("OP/OP.D");
    loadRawFile("LOAD.MSG");
}

void MainWindow::loadACProto()
{
    loadTFile("GG/COM/FDAT.T");
    loadTFile("GG/COM/RTIM.T");
    loadTFile("GG/MS/ARMS_T.T");
    loadTFile("GG/MS/BST_T.T");
    loadTFile("GG/MS/BWL_T.T");
    loadTFile("GG/MS/BWR_T.T");
    loadTFile("GG/MS/COMP_T.T");
    loadTFile("GG/MS/CORE_T.T");
    loadTFile("GG/MS/GENE_T.T");
    loadTFile("GG/MS/HEAD_T.T");
    loadTFile("GG/MS/LEG_T.T");
    loadTFile("GG/MS/MENU_TIM.T");
    loadTFile("GG/MS/MENU_TMD.T");
    loadTFile("GG/MS/MENU_VAB.T");
    loadTFile("GG/MS/MIS.T");
    loadTFile("GG/MS/SPEC_T.T");
    loadTFile("GG/MS/WEL_T.T");
    loadTFile("GG/MS/WER_T.T");
}

void MainWindow::loadACSampler4Demo()
{
    loadTFile("COM/FDAT.T");
    loadTFile("COM/RTIM.T");
    loadTFile("MS/ARMS_T.T");
    loadTFile("MS/BST_T.T");
    loadTFile("MS/BWL_T.T");
    loadTFile("MS/BWR_T.T");
    loadTFile("MS/COMP_T.T");
    loadTFile("MS/CORE_T.T");
    loadTFile("MS/GENE_T.T");
    loadTFile("MS/HEAD_T.T");
    loadTFile("MS/LEG_T.T");
    loadTFile("MS/MENU_TIM.T");
    loadTFile("MS/MENU_TMD.T");
    loadTFile("MS/MENU_VAB.T");
    loadTFile("MS/MIS.T");
    loadTFile("MS/SPEC_T.T");
    loadTFile("MS/WEL_T.T");
    loadTFile("MS/WER_T.T");
}

void MainWindow::loadMIXFile(QString path)
{
    // Prepend the path with a forward slash
    path.prepend(QChar('/'));
    // Replace the unix-style forward slashes in the path with the current system's separator.
    path.replace(QChar('/'), QDir::separator());
    
    if (!QFile(curSourceDirectory + path).exists())
        return;
    
    auto &loadedFile = files.emplace_back(curSourceDirectory, path, KFMTFile::KFMTFileType::MIX);
    auto &mixFile = *loadedFile.mixFile;
    
    loadedFile.treeItem = std::make_unique<QTreeWidgetItem>(ui->filesTree);
    loadedFile.treeItem->setIcon(0, QIcon(":/tfile_icon.png"));
    loadedFile.treeItem->setText(0, loadedFile.filePath);
    
    for (size_t fileIndex = 0; fileIndex < mixFile.size(); fileIndex++)
    {
        QByteArray &file = mixFile.getFile(fileIndex);
        if (Utilities::fileIsTMD(file))
            addModel(loadedFile.treeItem.get(), file, loadedFile.filePath + QString::number(fileIndex));
        else if (Utilities::fileIsTIM(file) || Utilities::fileIsRTIM(file))
            addTexture(loadedFile.treeItem.get(), file, loadedFile.filePath + QString::number(fileIndex));
        else if (Utilities::fileIsRTMD(file))
            addModel(loadedFile.treeItem.get(), file, loadedFile.filePath + QString::number(fileIndex));
        else if (Utilities::fileIsMO(file))
            addModel(loadedFile.treeItem.get(), file, loadedFile.filePath + QString::number(fileIndex));
    }
}

void MainWindow::loadRawFile(QString path)
{
    // Prepend the path with a forward slash
    path.prepend(QChar('/'));
    // Replace the unix-style forward slash with the current system's separator.
    path.replace(QChar('/'), QDir::separator());
    
    if (!QFile(curSourceDirectory + path).exists())
        return;
    
    auto &loadedFile = files.emplace_back(curSourceDirectory, path, KFMTFile::KFMTFileType::Raw);
    KFMTTreeWidgetItem *treeItem = nullptr;
    
    if (Utilities::fileIsTMD(loadedFile.rawFileData))
        treeItem = addModel(loadedFile.treeItem.get(), loadedFile.rawFileData, loadedFile.filePath);
    else if (Utilities::fileIsTIM(loadedFile.rawFileData) || Utilities::fileIsRTIM(loadedFile.rawFileData))
        treeItem = addTexture(loadedFile.treeItem.get(), loadedFile.rawFileData, loadedFile.filePath);
    else if (Utilities::fileIsRTMD(loadedFile.rawFileData))
        treeItem = addModel(loadedFile.treeItem.get(), loadedFile.rawFileData, loadedFile.filePath);
    else if (Utilities::fileIsMO(loadedFile.rawFileData))
        treeItem = addModel(loadedFile.treeItem.get(), loadedFile.rawFileData, loadedFile.filePath);
    
    if (treeItem != nullptr)
        loadedFile.treeItem.reset(treeItem);
}

void MainWindow::loadTFile(QString path)
{
    // Prepend the path with a forward slash
    path.prepend(QChar('/'));
    // Replace the unix-style forward slash with the current system's separator.
    path.replace(QChar('/'), QDir::separator());
    
    if (!QFile(curSourceDirectory + path).exists())
        return;
    
    auto &loadedFile = files.emplace_back(curSourceDirectory, path, KFMTFile::KFMTFileType::T);
    auto &tFile = *loadedFile.tFile;
    loadedFile.treeItem = std::make_unique<QTreeWidgetItem>(ui->filesTree);
    loadedFile.treeItem->setIcon(0, QIcon(":/tfile_icon.png"));
    loadedFile.treeItem->setText(0, loadedFile.filePath);
    ui->filesTree->addTopLevelItem(loadedFile.treeItem.get());
    
    for (size_t fileIndex = 0; fileIndex < tFile.getNumFiles(); fileIndex++)
    {
        QByteArray &file = tFile.getFile(fileIndex);
        if (Utilities::fileIsTMD(file))
            addModel(loadedFile.treeItem.get(), file, tFile.getPrettyName(fileIndex));
        else if (Utilities::fileIsTIM(file) || Utilities::fileIsRTIM(file))
            addTexture(loadedFile.treeItem.get(), file, tFile.getPrettyName(fileIndex));
        else if (Utilities::fileIsRTMD(file))
            addModel(loadedFile.treeItem.get(), file, tFile.getPrettyName(fileIndex));
        else if (Utilities::fileIsMO(file))
            addModel(loadedFile.treeItem.get(), file, tFile.getPrettyName(fileIndex));
        else if (Utilities::fileIsMAP1(file))
        {
            QByteArray &file2 = tFile.getFile(fileIndex + 1);
            QByteArray &file3 = tFile.getFile(fileIndex + 2);
            addMap(loadedFile.treeItem.get(), file, file2, file3, tFile.getPrettyName(fileIndex));
        }
        else if (Utilities::fileIsGameDB(file))
            addGameDB(loadedFile.treeItem.get(), file);
    }
}

void MainWindow::writeFiles(QDir &outDir)
{
    for (auto &file : files)
    {
        file.saveChanges();
        file.writeFile(outDir);
    }
}

MainWindow::KFMTFile::KFMTFile(const QString& srcDir, const QString& path, MainWindow::KFMTFile::KFMTFileType fileType) :
    type(fileType)
{
    srcPath = srcDir + path;
    filePath = path.mid(1);
    
    if (type == KFMTFileType::MIX)
    {
        mixFile = std::make_unique<MIXFile>(srcDir + path);
    }
    else if (type == KFMTFileType::Raw)
    {
        QFile fileHandle(srcDir + path);
        if (!fileHandle.open(QIODevice::ReadOnly))
            return;
        rawFileData = fileHandle.readAll();
    }
    else //if (type == KFMTFileType::TFILE)
    {
        tFile = std::make_unique<TFile>(srcDir + path);
    }
}

void MainWindow::KFMTFile::saveChanges()
{
    if (type == KFMTFileType::Raw)
        dynamic_cast<KFMTTreeWidgetItem *>(treeItem.get())->writeChanges();
    else // MIX or T
    {
        for (int childId = 0; childId < treeItem->childCount(); childId++)
            dynamic_cast<KFMTTreeWidgetItem *>(treeItem->child(childId))->writeChanges();
    }
}

void MainWindow::KFMTFile::writeFile(const QDir& outDir)
{
    QString dirToCreate = filePath.left(filePath.lastIndexOf(QRegExp("[\\/]")) + 1);
    outDir.mkpath(dirToCreate);
    
    QFile output(outDir.filePath(filePath));
    if (!output.open(QIODevice::WriteOnly))
        KFMTError::fatalError("Unable to open output file for " + filePath);
    
    if (type == KFMTFileType::MIX)
        mixFile->writeTo(output);
    else if (type == KFMTFileType::Raw)
        output.write(rawFileData);
    else if (type == KFMTFileType::T)
        tFile->writeTo(output);
    
    output.close();
}
