#include "models/texturelistmodel.h"
#include "texturedbviewer.h"
#include "QFileDialog"

TextureDBViewer::TextureDBViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextureDBViewer)
{
    ui->setupUi(this);
}

void TextureDBViewer::setTextureDB(std::shared_ptr<TextureDB> textureDB)
{
    curTextureDB = textureDB;
    ui->texList->setModel(new TextureListModel(ui->texList, textureDB));
    updateTextureView();
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
    updateTextureView();
}

void TextureDBViewer::on_replaceNBtn_clicked()
{
    replaceTexture(false);
}

void TextureDBViewer::on_replaceSBtn_clicked()
{
    replaceTexture(true);
}

void TextureDBViewer::updateTextureView()
{
    ui->texWidget->setPixmap(QPixmap::fromImage(curTextureDB->getTexture(curTexture).image));
}

void TextureDBViewer::replaceTexture(bool smooth)
{
    auto filter = "Images (*.bmp *.gif *.jpg *.jpeg *.png *.ppm *.xbm *.xpm)";
    auto fileName = QFileDialog::getOpenFileName(this, "Import image", QDir::currentPath(), filter);
    
    if (fileName.isEmpty())
        return;
    
    QImage replacement(fileName);
    curTextureDB->replaceTexture(replacement, curTexture, smooth);
    updateTextureView();
}
