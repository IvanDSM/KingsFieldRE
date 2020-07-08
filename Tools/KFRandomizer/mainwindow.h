#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pickFileButton_clicked();

    void on_randomizeButton_clicked();

    void randomizerStatusUpdate(const QString &status);

    void on_itemDropCheck_stateChanged(int arg1);

    void on_seedCheck_stateChanged(int arg1);

private:
    QString filename = "";
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
