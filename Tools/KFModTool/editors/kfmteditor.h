#ifndef KFMTEDITOR_H
#define KFMTEDITOR_H

#include "core/kfmterror.h"
#include "datahandlers/kfmtdatahandler.h"
#include <QCloseEvent>
#include <QWidget>

class KFMTEditor : public QWidget
{
    Q_OBJECT
public:
    explicit KFMTEditor(KFMTFile& file_, QWidget* parent = nullptr) : QWidget(parent)
    {
        Q_UNUSED(file_);
    }
    virtual ~KFMTEditor() { saveChanges(); }

    void saveChanges() { handler->saveChanges(); }

protected:
    std::unique_ptr<KFMTDataHandler> handler;

signals:
};

#endif // KFMTEDITOR_H
