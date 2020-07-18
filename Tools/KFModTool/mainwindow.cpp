#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "map.h"
#include "mapeditwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_actionAbout_KFModTool_triggered()
{
    QMessageBox::information(this, "TODO", "Implement this about box!");
}

void MainWindow::on_actionLoad_files_triggered()
{
    auto directory = QFileDialog::getExistingDirectory(this, "Select the folder with your King's Field T files.", QDir::homePath());
    if (directory.isEmpty())
        return;

    QDir tfile_dir(directory);
    if (!tfile_dir.exists("FDAT.T"))
    {
        QMessageBox::critical(this, "Error loading files!", "FDAT.T not found in the provided directory");
        return;
    }

    // We don't use C++14 so no make_unique :(
    fdat.reset(new TFile(tfile_dir.filePath("FDAT.T")));
    loadFdat();
}

void MainWindow::addMap(const unsigned int &index, const QString &name)
{
    std::shared_ptr<Map> map(new Map(*fdat, index, name));
    KFMTTreeWidgetItem* mapTreeItem = new KFMTTreeWidgetItem(ui->filesTree->itemAt(0,0), map);
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
        auto kfmtItem = reinterpret_cast<KFMTTreeWidgetItem *>(item);
        if (kfmtItem->getType() == KFMTDataType::KFMT_MAP)
        {
            auto mapIndex = kfmtItem->getMap()->getIndex();
            if (openMaps.count(mapIndex))
            {
                ui->editorTabs->setCurrentIndex(openMaps.at(mapIndex));
            }
            else
            {
                auto map = kfmtItem->getMap();
                MapEditWidget* mapEditor = new MapEditWidget(ui->editorTabs);
                mapEditor->setMap(map);
                ui->editorTabs->addTab(mapEditor, map->getName());
                ui->editorTabs->setCurrentIndex(ui->editorTabs->count() - 1);
                ui->editorTabs->setTabIcon(ui->editorTabs->count() - 1, QIcon(":/map_icon.png"));
                openMaps[mapIndex] = ui->editorTabs->count() - 1;
            }
        }

    }
}

void MainWindow::on_editorTabs_tabCloseRequested(int index)
{
    ui->editorTabs->removeTab(index);
}

void MainWindow::on_actionSave_changes_triggered()
{
    for (auto curChild = 0; curChild < ui->filesTree->itemAt(0, 0)->childCount(); curChild++)
    {
        KFMTTreeWidgetItem *child = reinterpret_cast<KFMTTreeWidgetItem *>(ui->filesTree->itemAt(0,0)->child(curChild));

        if (child->getType() == KFMTDataType::KFMT_MAP)
            child->getMap()->writeChanges();
    }

    QDir dir(QFileDialog::getExistingDirectory(this, "Select where to save the changed files",
                                               QDir::homePath()));

    QFile fdatOut(dir.filePath("FDAT.T"));
    fdatOut.open(QIODevice::WriteOnly);
    fdatOut.write(fdat->getTFile());
    fdatOut.close();
}

void MainWindow::addGameDB()
{
    KFMTTreeWidgetItem* gameDBTreeItem = new KFMTTreeWidgetItem(ui->filesTree->itemAt(0,0), gameDB);
    gameDBTreeItem->setText(0, "Game Database");

    ui->filesTree->itemAt(0, 0)->addChild(gameDBTreeItem);
}
