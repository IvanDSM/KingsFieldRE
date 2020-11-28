#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <memory>
#include <tfile.h>
#include "kfmttreewidgetitem.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
    {
        ui->setupUi(this);
        KFMTError::setParent(this);
        //std::fill(openMaps.begin(), openMaps.end(), -1);
    }

private slots:
    void on_actionAbout_Qt_triggered()
    {
        QMessageBox::aboutQt(this);
    }

    void on_actionAbout_KFModTool_triggered()
    {
        AboutDialog about;
        about.exec();
    }

    void on_actionLoad_files_triggered();

    void on_filesTree_itemDoubleClicked(QTreeWidgetItem *item, int);

    void on_editorTabs_tabCloseRequested(int index)
    {
        auto tabName = ui->editorTabs->tabText(index);
        openTabs.erase(openTabs.find(tabName));
        ui->editorTabs->removeTab(index);
    }

    void on_actionSave_changes_triggered();

    void on_actionExit_triggered()
    {
        close();
    }

private:
    void addGameDB(TFile & tFile, unsigned int index);
    void addMap(TFile &tFile, unsigned int index);
    void addModel(TFile &tFile, unsigned int index);
    void addTexture(TFile &tFile, unsigned int index);
    
    void loadFdat();
    void loadMo();
    void loadRtmd();
    
    void loadTFile(TFile & tFile, std::unique_ptr<QTreeWidgetItem> &tFileTreeItem);
    
    std::unique_ptr<Ui::MainWindow> ui;

    QString curSourceDirectory;
    
    // TODO: Implement this stuff
    std::unordered_map<QString, QWidget *> openTabs; 

    // T File pointers
    std::unique_ptr<TFile> fdat = nullptr;
    std::unique_ptr<TFile> item = nullptr;
    std::unique_ptr<TFile> mo = nullptr;
    std::unique_ptr<TFile> rtim = nullptr;
    std::unique_ptr<TFile> rtmd = nullptr;
    std::unique_ptr<TFile> talk = nullptr;
    
    // T file tree item pointers
    std::unique_ptr<QTreeWidgetItem> fdatTreeItem = nullptr;
    std::unique_ptr<QTreeWidgetItem> itemTreeItem = nullptr;
    std::unique_ptr<QTreeWidgetItem> moTreeItem = nullptr;
    std::unique_ptr<QTreeWidgetItem> rtimTreeItem = nullptr;
    std::unique_ptr<QTreeWidgetItem> rtmdTreeItem = nullptr;
    std::unique_ptr<QTreeWidgetItem> talkTreeItem = nullptr;
    
};
#endif // MAINWINDOW_H
