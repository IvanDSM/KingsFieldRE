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
    
private slots:
    void on_exportBtn_clicked();
    
    void on_texList_activated(const QModelIndex &index);
    
private:
    size_t curTexture = 0;
    std::shared_ptr<TextureDB> curTextureDB = nullptr;
    Ui::TextureDBViewer *ui;
};

#endif // TEXTUREDBVIEWER_H
