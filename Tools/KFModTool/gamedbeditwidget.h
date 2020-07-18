#ifndef GAMEDBEDITWIDGET_H
#define GAMEDBEDITWIDGET_H

#include <QWidget>

namespace Ui {
    class GameDBEditWidget;
}

class GameDBEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameDBEditWidget(QWidget *parent = nullptr);
    ~GameDBEditWidget();

private:
    Ui::GameDBEditWidget *ui;
};

#endif // GAMEDBEDITWIDGET_H
