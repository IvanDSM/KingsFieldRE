#ifndef EXEEDITOR_H
#define EXEEDITOR_H

#include "kfmteditor.h"
#include <QWidget>

namespace Ui
{
class EXEEditor;
}

class EXEEditor : public KFMTEditor
{
    Q_OBJECT
    
public:
    explicit EXEEditor(KFMTFile& file_, QWidget* parent = nullptr);
    ~EXEEditor();

private slots:
    void on_shopCombo_currentIndexChanged(int index);

private:
    Ui::EXEEditor *ui;
};

#endif // EXEEDITOR_H
