#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "aboutdialog.h"
#include "core/kfmtcore.h"
#include "core/kfmterror.h"
#include "editors/kfmteditor.h"
#include "models/filelistmodel.h"
#include "ui_mainwindow.h"
#include <memory>
#include <QDir>
#include <QMainWindow>
#include <QMessageBox>
#include <QTreeWidgetItem>

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
        if (strcmp(RUNID, "DEVELOPMENT") != 0) setWindowTitle("KFModTool r" RUNID);
        KFMTError::setParent(this);
        ui->filesTree->setModel(new FileListModel(ui->filesTree));
    }

    ~MainWindow() { delete ui; }

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

    void on_editorTabs_tabCloseRequested(int index)
    {
        auto* tab = ui->editorTabs->widget(index);
        auto it = std::find_if(openTabs.begin(), openTabs.end(), [&](auto& entry) {
            return entry.second == tab;
        });

        if (it != openTabs.end()) openTabs.erase(it);
        ui->editorTabs->removeTab(index);
        // FIXME: Is this necessary?
        tab->deleteLater();
    }

    void on_actionSave_changes_triggered();

    void on_actionExit_triggered() { close(); }

    void on_filesTree_doubleClicked(const QModelIndex& index);

private:
    Ui::MainWindow* ui;

    std::unordered_map<KFMTFile*, KFMTEditor*> openTabs;
};
#endif // MAINWINDOW_H
