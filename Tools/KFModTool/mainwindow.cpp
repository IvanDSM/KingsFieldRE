#include "mainwindow.h"
#include "core/icons.h"
#include "editors/exeeditor.h"
#include "editors/gamedbeditwidget.h"
#include "editors/mapeditwidget.h"
#include "editors/modelviewerwidget.h"
#include "editors/texturedbviewer.h"
#include "utilities.h"
#include <memory>
#include <QFileDialog>

void MainWindow::on_actionLoad_files_triggered()
{
    auto directory = QFileDialog::getExistingDirectory(
        this, QStringLiteral("Select the root folder of your game's CD."), QDir::homePath());

    if (directory.isEmpty()) return;

    // Close all tabs
    for (int tab = ui->editorTabs->count() - 1; tab >= 0; tab++) ui->editorTabs->removeTab(tab);

    core.loadFrom(directory);

    dynamic_cast<FileListModel*>(ui->filesTree->model())->update();
}

void MainWindow::on_actionSave_changes_triggered()
{
    auto dirPath = QFileDialog::getExistingDirectory(this,
                                                     QStringLiteral(
                                                         "Select where to save the changed files"),
                                                     QDir::homePath());

    if (dirPath.isEmpty()) return;

    if (QDir(dirPath) == core.getSrcDir())
    {
        auto answer = QMessageBox::question(this,
                                            QStringLiteral("You're about to overwrite your files!"),
                                            QStringLiteral(
                                                "You just chose the same directory as your source "
                                                "files. Are you sure you want to overwrite them?"));

        if (answer != QMessageBox::Yes) return;
    }

    core.saveTo(dirPath);

    QMessageBox::information(this,
                             QStringLiteral("Changes saved successfully!"),
                             QStringLiteral("Your changes have been saved!"));
}

void MainWindow::on_filesTree_doubleClicked(const QModelIndex& index)
{
    auto* file = reinterpret_cast<KFMTFile*>(index.internalPointer());

    if (file->getDataType() == KFMTFile::DataType::Container) return;
    if (openTabs.find(file) != openTabs.end())
    {
        ui->editorTabs->setCurrentWidget(openTabs.find(file)->second);
        return;
    }

    KFMTEditor* editor = nullptr;

    switch (file->getDataType())
    {
        case KFMTFile::DataType::GameDB: {
            editor = new GameDBEditWidget(*file, ui->editorTabs);
            openTabs.emplace(file, editor);
            ui->editorTabs->addTab(editor, Icons::gameDb, index.data().value<QString>());
            break;
        }
        case KFMTFile::DataType::GameEXE: {
            editor = new EXEEditor(*file, ui->editorTabs);
            openTabs.emplace(file, editor);
            ui->editorTabs->addTab(editor, Icons::gameExe, index.data().value<QString>());
            break;
        }
        case KFMTFile::DataType::MapTilemap: {
            // FIXME: This way of getting the DB/script files is terrible. There must be a better way.
            auto firstNum = file->filePath.indexOf(QRegExp("[0-9]"));
            auto containerName = file->filePath.left(firstNum);
            auto tileIndex = file->filePath.midRef(firstNum).toULong();
            auto* db = core.getFile(containerName, tileIndex + 1);
            auto* sc = core.getFile(containerName, tileIndex + 2);

            auto tabTitle = index.data().value<QString>();
            tabTitle = tabTitle.left(tabTitle.lastIndexOf(' '));

            editor = new MapEditWidget(*file, *db, *sc, ui->editorTabs);
            openTabs.emplace(file, editor);
            ui->editorTabs->addTab(editor, Icons::map, tabTitle);

            break;
        }
        case KFMTFile::DataType::MapDB: {
            // FIXME: This way of getting the tilemap/script files is terrible. There must be a better way.
            auto firstNum = file->filePath.indexOf(QRegExp("[0-9]"));
            auto containerName = file->filePath.left(firstNum);
            auto tileIndex = file->filePath.midRef(firstNum).toULong();

            auto* tm = core.getFile(containerName, tileIndex - 1);
            if (openTabs.find(tm) != openTabs.end())
            {
                ui->editorTabs->setCurrentWidget(openTabs.find(tm)->second);
                return;
            }
            auto* sc = core.getFile(containerName, tileIndex + 1);

            auto tabTitle = index.data().value<QString>();
            tabTitle = tabTitle.left(tabTitle.lastIndexOf(" M"));

            editor = new MapEditWidget(*tm, *file, *sc, ui->editorTabs);
            openTabs.emplace(tm, editor);
            ui->editorTabs->addTab(editor, Icons::map, tabTitle);
            break;
        }
        case KFMTFile::DataType::MapScript: {
            // FIXME: This way of getting the tilemap/script files is terrible. There must be a better way.
            auto firstNum = file->filePath.indexOf(QRegExp("[0-9]"));
            auto containerName = file->filePath.left(firstNum);
            auto tileIndex = file->filePath.midRef(firstNum).toULong();

            auto* tm = core.getFile(containerName, tileIndex - 2);
            if (openTabs.find(tm) != openTabs.end())
            {
                ui->editorTabs->setCurrentWidget(openTabs.find(tm)->second);
                return;
            }
            auto* db = core.getFile(containerName, tileIndex - 1);

            auto tabTitle = index.data().value<QString>();
            tabTitle = tabTitle.left(tabTitle.lastIndexOf(' '));

            editor = new MapEditWidget(*tm, *db, *file, ui->editorTabs);
            openTabs.emplace(tm, editor);
            ui->editorTabs->addTab(editor, Icons::map, tabTitle);
            break;
        }
        case KFMTFile::DataType::Model: {
            editor = new ModelViewerWidget(*file, ui->editorTabs);
            openTabs.emplace(file, editor);
            ui->editorTabs->addTab(editor, Icons::model, index.data().value<QString>());
            break;
        }
        case KFMTFile::DataType::TextureDB: {
            editor = new TextureDBViewer(*file, ui->editorTabs);
            openTabs.emplace(file, editor);
            ui->editorTabs->addTab(editor, Icons::textureDb, index.data().value<QString>());
        }
        default: break;
    }

    if (editor != nullptr) ui->editorTabs->setCurrentWidget(editor);
}
