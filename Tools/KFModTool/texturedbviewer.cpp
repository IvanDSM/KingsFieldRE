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
    ui->texWidget->setPixmap(QPixmap::fromImage(textureDB->getTexture(curTexture)));
}

void TextureDBViewer::on_exportBtn_clicked()
{
    QFileDialog exportDlg(this, "Export texture", QDir::currentPath(),
                          "BMP (*.bmp);;PNG (*.png);;PPM (*.ppm);;XBM (*.xbm);;XPM (*xpm)");
    
    exportDlg.setAcceptMode(QFileDialog::AcceptSave);
    exportDlg.setFileMode(QFileDialog::ExistingFile);
    
    if (!exportDlg.exec())
        return;
    
    QString &fileName = exportDlg.selectedFiles().first();
    const char *format = exportDlg.selectedNameFilter().left(3).toStdString().c_str();
    
    curTextureDB->getTexture(curTexture).save(fileName, format, 0);
}

void TextureDBViewer::on_texList_doubleClicked(const QModelIndex &index)
{
    curTexture = index.row();
    ui->texWidget->setPixmap(QPixmap::fromImage(curTextureDB->getTexture(curTexture)));
}
