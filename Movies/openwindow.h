#ifndef OPENWINDOW_H
#define OPENWINDOW_H

#include <QDialog>
#include <connectdatabase.h>

namespace Ui {
class OpenWindow;
}

class OpenWindow : public QDialog
{
    Q_OBJECT

public:
    explicit OpenWindow(QModelIndex index, QWidget *parent = nullptr);
    ~OpenWindow();

private slots:
    void on_pushButtonClose_clicked();

private:
    Ui::OpenWindow *ui;
    QModelIndex index;
};

#endif // OPENWINDOW_H
