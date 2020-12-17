#include "addwindow.h"
#include "ui_addwindow.h"

AddWindow::AddWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Добавление фильма");
}

AddWindow::~AddWindow()
{
    delete ui;
}

void AddWindow::on_pushButtonAdd_clicked()
{
    QVariantList data;
    data.append(ui->lineEditMovie->text());
    data.append(ui->lineEditYear->text().toInt());
    data.append(ui->lineEditCategory->text());
    data.append(ui->textEditDescription->toPlainText());

    // Вставляем данные в БД
    ConnectDataBase::db->inserIntoTable(data);
    this->close();
}
