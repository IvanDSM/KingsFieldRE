#ifndef TEXTUREDBVIEWER_H
#define TEXTUREDBVIEWER_H

#include "datahandlers/texturedb.h"
#include "editors/kfmteditor.h"
#include "ui_texturedbviewer.h"
#include <QWidget>

class TextureDBViewer : public KFMTEditor
{
    Q_OBJECT
    
public:
    explicit TextureDBViewer(KFMTFile& file_, QWidget* parent = nullptr);
    ~TextureDBViewer() { delete ui; }

protected:
    void resizeEvent(QResizeEvent *) override { updateTextureLabel(); }
    
private slots:
    void on_exportBtn_clicked();

    void on_exportAllBtn_clicked();

    void on_texList_activated(const QModelIndex& index);

    void on_replaceNBtn_clicked();

    void on_replaceSBtn_clicked();

private:
    void replaceTexture(Qt::TransformationMode mode);

    void updateTextureLabel();
    void updateTextureViewer();
    
    QPixmap curTexPixmap {};
    size_t curTexture = 0;
    Ui::TextureDBViewer* ui;

    static const QString clutFbPosLabelPrefix;
    static const QString pixelFbPosLabelPrefix;
    static const QString pixelModePrefix;
    static const QString pixelSizePrefix;
};

#endif // TEXTUREDBVIEWER_H
