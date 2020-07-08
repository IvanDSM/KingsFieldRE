#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "randomizer.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pickFileButton_clicked()
{
    QString result = QFileDialog::getOpenFileName(this, "Select your FDAT.T file.", QDir::homePath(), "FDAT.T (FDAT.T)");
    if (result != "")
    {
        filename = result;
        ui->pickFileButton->setText(filename);
        ui->randomizeButton->setEnabled(true);
    }
}

void MainWindow::on_randomizeButton_clicked()
{
    ui->statusView->clear();

    Randomizer randomizer(this, filename);
    connect(&randomizer, &Randomizer::statusUpdate, this, &MainWindow::randomizerStatusUpdate);
    if (ui->itemDropCheck->isChecked() && ui->noEmptyDropsCheck->isChecked())
        randomizer.setNoEmptyDrops(ui->noEmptyDropsCheck->isChecked());

    if (ui->monsterCheck->isChecked())
        randomizer.randomizeMonsters(ui->itemDropCheck->isChecked());

    if (ui->itemCheck->isChecked())
        randomizer.randomizeItems();

    auto fdat = randomizer.getFile();

    QMessageBox::information(this, "Almost done!", "Randomization done!\nYou will now be prompted to save the randomized FDAT.T we just generated.");

    QString outFilename = QFileDialog::getSaveFileName(this, "Choose where to save the new FDAT.T file.", QDir::homePath(), "FDAT.T (FDAT.T)");
    if (!outFilename.isEmpty())
    {
        QFile outFile(outFilename);
        if (!outFile.open(QIODevice::WriteOnly))
            QMessageBox::critical(this,
                                  "Randomizer: Failed to open file",
                                  "The file failed to open :(");
        else
        {
            outFile.write(fdat);
            outFile.close();
            QMessageBox::information(this, "Done!", "Randomized FDAT.T written!\nNow all you need to do is use a program like CDmage 1.02.1 to replace your CD image's FDAT.T with the one the program generated.\nBe sure to do it on a copy of your original image!");
        }
    }
}

void MainWindow::randomizerStatusUpdate(const QString &status)
{
    ui->statusView->addItem(status);
}

void MainWindow::on_itemDropCheck_stateChanged(int arg1)
{
    if (arg1 == Qt::CheckState::Checked)
        ui->noEmptyDropsCheck->setEnabled(true);
    else
        ui->noEmptyDropsCheck->setEnabled(false);
}
