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
        std::fill(openMaps.begin(), openMaps.end(), -1);
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
        std::replace(openMaps.begin(), openMaps.end(), index, -1);
        ui->editorTabs->removeTab(index);
    }

    void on_actionSave_changes_triggered();

    void on_actionExit_triggered()
    {
        close();
    }

private:
    void addGameDB();
    void addMap(unsigned int index, const QString &name);
    void addModel(TFile &tFile, unsigned int index, const QString &name);
    void loadFdat();
    void loadItem();
    void loadMo();
    void loadRtmd();
    
    std::unique_ptr<Ui::MainWindow> ui;

    int openGameDB = -1;
    QString curSourceDirectory;
    std::array<int, 9> openMaps;

    // T File pointers
    std::unique_ptr<TFile> fdat = nullptr;
    std::unique_ptr<TFile> item = nullptr;
    std::unique_ptr<TFile> mo = nullptr;
    std::unique_ptr<TFile> rtmd = nullptr;
    
    // T file tree item pointers
    std::unique_ptr<QTreeWidgetItem> fdatTreeItem = nullptr;
    std::unique_ptr<QTreeWidgetItem> itemTreeItem = nullptr;
    std::unique_ptr<QTreeWidgetItem> moTreeItem = nullptr;
    std::unique_ptr<QTreeWidgetItem> rtmdTreeItem = nullptr;
    
};
#endif // MAINWINDOW_H
