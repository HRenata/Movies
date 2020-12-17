#include "editwindow.h"
#include "ui_editwindow.h"

EditWindow::EditWindow(QModelIndex index, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditWindow)
{
    ui->setupUi(this);
     this->setWindowTitle("Редактирование информации о фильме");

     this->index = index;

     int row = index.row();
     QString movie = index.sibling(row, 1).data().toString();
     QString year = index.sibling(row, 2).data().toString();
     QString category = index.sibling(row, 3).data().toString();
     QString description = index.sibling(row, 4).data().toString();

     ui->lineEditMovie->setText(movie);
     ui->lineEditYear->setText(year);
     ui->lineEditCategory->setText(category);
     ui->textEditDescription->setText(description);
}

EditWindow::~EditWindow()
{
    delete ui;
}

void EditWindow::on_pushButtonEdit_clicked()
{
    const int id = index.sibling(index.row(), 0).data().toInt();

    QVariantList data;
    data.append(ui->lineEditMovie->text());
    data.append(ui->lineEditYear->text().toInt());
    data.append(ui->lineEditCategory->text());
    data.append(ui->textEditDescription->toPlainText());

    // Вставляем данные в БД
    ConnectDataBase::db->updateNode(id, data);
    this->close();
}
