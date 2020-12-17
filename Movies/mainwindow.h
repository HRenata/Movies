#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QMessageBox>
#include <connectdatabase.h>
#include <addwindow.h>
#include <openwindow.h>
#include <editwindow.h>

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
    void on_pushButtonSearch_clicked();

    void on_pushButtonSort_clicked();

    void on_pushButtonOpen_clicked();

    void on_pushButtonAdd_clicked();

    void on_pushButtonEdit_clicked();

    void on_pushButtonDelete_clicked();

    void on_pushButtonClean_clicked();

    void on_tableViewMovies_pressed(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QModelIndex index;

    void createUI();
};
#endif // MAINWINDOW_H
