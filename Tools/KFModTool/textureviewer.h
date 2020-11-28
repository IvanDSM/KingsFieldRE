#ifndef TEXTUREVIEWER_H
#define TEXTUREVIEWER_H

#include "texture.h"
#include "ui_textureviewer.h"
#include <QWidget>

class TextureViewer : public QWidget
{
    Q_OBJECT
    
public:
    explicit TextureViewer(QWidget *parent = nullptr);
    void setTexture(std::shared_ptr<Texture> texture);
    
private:
    std::shared_ptr<Texture> curTexture = nullptr;
    std::unique_ptr<Ui::TextureViewer> ui;
};

#endif // TEXTUREVIEWER_H
