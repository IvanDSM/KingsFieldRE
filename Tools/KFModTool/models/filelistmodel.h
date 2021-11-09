#ifndef FILELISTMODEL_H
#define FILELISTMODEL_H

#include "core/kfmtcore.h"
#include "core/kfmterror.h"
#include <QAbstractItemModel>
#include <QFileDialog>
#include <QMenu>

class FileListModel : public QAbstractItemModel
{
    Q_OBJECT
    
public:
    explicit inline FileListModel(QObject* parent = nullptr) : QAbstractItemModel(parent)
    {
        containerContextMenu = new QMenu("Container context menu", dynamic_cast<QWidget*>(parent));
        extractContainerAction = new QAction("Extract files...", containerContextMenu);
        // This bit of code sets up the context menu
        containerContextMenu->addAction(extractContainerAction);
        dynamic_cast<QWidget*>(parent)->setContextMenuPolicy(
            Qt::ContextMenuPolicy::CustomContextMenu);
        connect(dynamic_cast<QWidget*>(parent),
                &QWidget::customContextMenuRequested,
                this,
                &FileListModel::contextMenu);
        connect(extractContainerAction, &QAction::triggered, this, &FileListModel::extractContainer);
    }

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    
    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    void update();

public slots:
    void contextMenu(const QPoint& pos);

private:
    QMenu* containerContextMenu;
    QAction* extractContainerAction;
    KFMTFile* contextMenuFile = nullptr;

private slots:
    void extractContainer(bool)
    {
        if (contextMenuFile == nullptr) return;

        auto dir
            = QFileDialog::getExistingDirectory(dynamic_cast<QWidget*>(QObject::parent()),
                                                "Select the directory to extract the files to");

        if (dir.isEmpty()) return;

        contextMenuFile->extractTo(dir);

        KFMTError::warning(QStringLiteral("Extraction complete!"));
    }
};

#endif // FILELISTMODEL_H
