#include "models/texturelistmodel.h"
#include "texturedbviewer.h"
#include "QFileDialog"

TextureDBViewer::TextureDBViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextureDBViewer)
{
    ui->setupUi(this);
    ui->clutFbPosLabel->setText(clutFbPosLabelPrefix);
    ui->pixelFbPosLabel->setText(pixelFbPosLabelPrefix);
    ui->pixelModeLabel->setText(pixelModePrefix);
    ui->pixelSizeLabel->setText(pixelSizePrefix);
}

void TextureDBViewer::setTextureDB(std::shared_ptr<TextureDB> textureDB)
{
    curTextureDB = textureDB;
    ui->texList->setModel(new TextureListModel(ui->texList, textureDB));
    updateTextureViewer();
}

void TextureDBViewer::on_exportBtn_clicked()
{
    QFileDialog exportDlg(this, "Export texture", QDir::currentPath(),
                          "BMP (*.bmp);;PNG (*.png);;PPM (*.ppm);;XBM (*.xbm);;XPM (*.xpm)");
    
    exportDlg.setAcceptMode(QFileDialog::AcceptSave);
    exportDlg.setFileMode(QFileDialog::ExistingFile);
    
    if (!exportDlg.exec())
        return;
    
    QString &fileName = exportDlg.selectedFiles().first();
    const char *format = exportDlg.selectedNameFilter().left(3).toStdString().c_str();
    
    curTextureDB->getTexture(curTexture).image.save(fileName, format, 0);
}

void TextureDBViewer::on_texList_activated(const QModelIndex &index)
{
    curTexture = index.row();
    updateTextureViewer();
}

void TextureDBViewer::on_replaceNBtn_clicked()
{
    replaceTexture(false);
}

void TextureDBViewer::on_replaceSBtn_clicked()
{
    replaceTexture(true);
}

void TextureDBViewer::replaceTexture(bool smooth)
{
    auto filter = "Images (*.bmp *.gif *.jpg *.jpeg *.png *.ppm *.xbm *.xpm)";
    auto fileName = QFileDialog::getOpenFileName(this, "Import image", QDir::currentPath(), filter);
    
    if (fileName.isEmpty())
        return;
    
    QImage replacement(fileName);
    curTextureDB->replaceTexture(replacement, curTexture, smooth);
    updateTextureViewer();
}

void TextureDBViewer::updateTextureLabel()
{
    if (!curTexPixmap.isNull())
        ui->texWidget->setPixmap(curTexPixmap.scaled(ui->texWidget->size(), Qt::KeepAspectRatio,
                                                     Qt::FastTransformation));
}

void TextureDBViewer::updateTextureViewer()
{
    auto &texture = curTextureDB->getTexture(curTexture);
    curTexPixmap = QPixmap::fromImage(texture.image);
    updateTextureLabel();
    
    ui->clutFbPosLabel->setText(clutFbPosLabelPrefix + QString::asprintf("{%d, %d}",
                                                                         texture.clutVramX,
                                                                         texture.clutVramY));
    ui->pixelFbPosLabel->setText(pixelFbPosLabelPrefix + QString::asprintf("{%d, %d}",
                                                                           texture.pxVramX,
                                                                           texture.pxVramY));
    ui->pixelSizeLabel->setText(pixelSizePrefix + QString::asprintf("%dx%d",
                                                                    texture.pxWidth,
                                                                    texture.pxHeight));
    QString pixelModeString;
    
    switch (texture.pMode)
    {
    case TextureDB::PixelMode::CLUT4Bit:
        pixelModeString = "CLUT 4bpp";
        break;
    case TextureDB::PixelMode::CLUT8Bit:
        pixelModeString = "CLUT 8bpp";
        break;
    case TextureDB::PixelMode::Direct15Bit:
        pixelModeString = "Direct 15bpp";
        break;
    case TextureDB::PixelMode::Dir24Bit:
        pixelModeString = "Direct 24bpp";
        break;
    case TextureDB::PixelMode::Mixed:
        pixelModeString = "Mixed";
        break;
    }
    
    ui->pixelModeLabel->setText(pixelModePrefix + pixelModeString);
}
