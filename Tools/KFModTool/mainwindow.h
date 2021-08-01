#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "aboutdialog.h"
#include "kfmttreewidgetitem.h"
#include "mixfile.h"
#include "tfile.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QMainWindow>
#include <QMessageBox>
#include <memory>

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

    void on_filesTree_itemDoubleClicked(QTreeWidgetItem *item_, int);

    void on_editorTabs_tabCloseRequested(int index)
    {
        auto tabName = ui->editorTabs->tabText(index);
        openTabs.erase(openTabs.find(tabName));
        auto tabWidget = ui->editorTabs->widget(index);
        ui->editorTabs->removeTab(index);
        tabWidget->deleteLater();
    }

    void on_actionSave_changes_triggered();

    void on_actionExit_triggered()
    {
        close();
    }

private:
    struct KFMTFile
    {
        enum class KFMTFileType
        {
            MIX,
            Raw,
            T
        };
        KFMTFile(const QString& srcDir, const QString& path, KFMTFileType fileType);
        void saveChanges();
        void writeFile(const QDir& outDir);
        
        KFMTFileType type;
        
        std::unique_ptr<MIXFile> mixFile = nullptr;
        QString filePath;
        QByteArray rawFileData;
        QString srcPath;
        std::unique_ptr<QTreeWidgetItem> treeItem = nullptr;
        std::unique_ptr<TFile> tFile = nullptr;
    };
    
    KFMTTreeWidgetItem *addGameDB(QTreeWidgetItem *parent, QByteArray &file);
    KFMTTreeWidgetItem *addMap(QTreeWidgetItem *parent, QByteArray &file1, QByteArray & file2, QByteArray & file3, const QString &filename);
    KFMTTreeWidgetItem *addModel(QTreeWidgetItem *parent, QByteArray &file, const QString &filename);
    KFMTTreeWidgetItem *addTexture(QTreeWidgetItem *parent, QByteArray &file, const QString &filename);
    
    void loadJDemo();
    void loadJ();
    void load2J();
    void loadEU();
    void load3JorPS();

    // We don't support anything from the Armored Core P*.T files yet
    void loadACProto();
    void loadACSampler4Demo();

    /*!
     * \brief Loads the retail Shadow Tower CD.
     */
    void loadSTower();
    /*!
     * \brief Loads the Shadow Tower demo from the PlayStation Undeground v2.4 CD (SCUS-94298)
     */
    void loadSTowerDemo();

    void loadMIXFile(QString path);
    void loadRawFile(QString path);
    void loadTFile(QString path);
    
    void writeFiles(QDir &outDir);
    
    std::unique_ptr<Ui::MainWindow> ui;

    QString curSourceDirectory;

    std::list<KFMTFile> files;
    
    // TODO: Implement this stuff
    std::unordered_map<QString, QWidget *> openTabs;
};
#endif // MAINWINDOW_H
