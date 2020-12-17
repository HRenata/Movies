#include "openwindow.h"
#include "ui_openwindow.h"

OpenWindow::OpenWindow(QModelIndex index, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Просмотр информации о фильме");

    this->index = index;

    int row = index.row();
    QString movie = index.sibling(row, 1).data().toString();
    QString year = index.sibling(row, 2).data().toString();
    QString category = index.sibling(row, 3).data().toString();
    QString description = index.sibling(row, 4).data().toString();

    ui->labelMovieValue->setText(movie);
    ui->labelYearValue->setText(year);
    ui->labelCategoryValue->setText(category);
    ui->textBrowserDescriptionValue->setText(description);
}

OpenWindow::~OpenWindow()
{
    delete ui;
}

void OpenWindow::on_pushButtonClose_clicked()
{
    this->close();
}
