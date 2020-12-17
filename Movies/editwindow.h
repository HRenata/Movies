#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QDialog>
#include <connectdatabase.h>

namespace Ui {
class EditWindow;
}

class EditWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditWindow(QModelIndex index, QWidget *parent = nullptr);
    ~EditWindow();

private slots:
    void on_pushButtonEdit_clicked();

private:
    Ui::EditWindow *ui;
    QModelIndex index;
};

#endif // EDITWINDOW_H
