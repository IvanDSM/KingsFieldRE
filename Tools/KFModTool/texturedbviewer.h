#ifndef TEXTUREDBVIEWER_H
#define TEXTUREDBVIEWER_H

#include "texturedb.h"
#include "ui_texturedbviewer.h"
#include <QWidget>

class TextureDBViewer : public QWidget
{
    Q_OBJECT
    
public:
    explicit TextureDBViewer(QWidget *parent = nullptr);
    ~TextureDBViewer() {delete ui;}
    
    void setTextureDB(std::shared_ptr<TextureDB> textureDB);
    
protected:
    void resizeEvent(QResizeEvent *) override { updateTextureLabel(); }
    
private slots:
    void on_exportBtn_clicked();
    
    void on_texList_activated(const QModelIndex &index);
    
    void on_replaceNBtn_clicked();
    
    void on_replaceSBtn_clicked();
    
    
private:
    void replaceTexture(bool smooth);
    
    void updateTextureLabel();
    void updateTextureViewer();
    
    QPixmap curTexPixmap {};
    size_t curTexture = 0;
    std::shared_ptr<TextureDB> curTextureDB = nullptr;
    Ui::TextureDBViewer *ui;
    
    const QString clutFbPosLabelPrefix = "CLUT Framebuffer Position: ";
    const QString pixelFbPosLabelPrefix = "Pixel Framebuffer Position: ";
    const QString pixelModePrefix = "Pixel Mode: ";
    const QString pixelSizePrefix = "Pixel Size: ";
};

#endif // TEXTUREDBVIEWER_H
