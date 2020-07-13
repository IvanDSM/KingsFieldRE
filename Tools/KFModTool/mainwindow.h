#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <tfile.h>
#include "kfmttreewidgetitem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAbout_Qt_triggered();

    void on_actionAbout_KFModTool_triggered();

    void on_actionLoad_files_triggered();

    void on_filesTree_itemDoubleClicked(QTreeWidgetItem *item, int);

    void on_editorTabs_tabCloseRequested(int index);

    void on_actionSave_changes_triggered();

private:
    void addMap(const unsigned int &index, const QString &name);
    void loadFdat();

    std::unordered_map<unsigned int, unsigned int> openMaps;

    std::unique_ptr<TFile> fdat = nullptr;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
