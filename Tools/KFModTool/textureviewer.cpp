#include "textureviewer.h"

TextureViewer::TextureViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextureViewer)
{
    ui->setupUi(this);
}

void TextureViewer::setTexture(std::shared_ptr<Texture> texture)
{
    curTexture = texture;
    ui->texWidget->setPixmap(QPixmap::fromImage(texture->getImage()));
}
