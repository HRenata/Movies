#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Фильмы");

    /* Первым делом необходимо создать объект, который будет использоваться для работы с данными нашей БД
     * и инициализировать подключение к базе данных
     * */
    ConnectDataBase::connectToDataBase();

    /* После чего производим наполнение таблицы базы данных
     * контентом, который будет отображаться в TableView
     * */
    ConnectDataBase::model = new QSqlTableModel(this);

    /* Инициализируем модель для представления данных
     * с заданием названий колонок
     * */
    ConnectDataBase::setupModel(TABLE,
                     QStringList() << trUtf8("id")
                     << trUtf8("Фильм")
                     << trUtf8("Год")
                     << trUtf8("Жанр")
                     << trUtf8("Описание")
                     );

    /* Инициализируем внешний вид таблицы с данными
     * */
    this->createUI();

    QDir().mkdir("../images");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createUI()
{
    ui->tableViewMovies->setModel(ConnectDataBase::model);     // Устанавливаем модель на TableView
    ui->tableViewMovies->setColumnHidden(0, true);    // Скрываем колонку с id записей
    // Разрешаем выделение строк
    ui->tableViewMovies->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui->tableViewMovies->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewMovies->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewMovies->horizontalHeader()->setStretchLastSection(true);

    ConnectDataBase::model->select(); // Делаем выборку данных из таблицы
}

void MainWindow::on_pushButtonSearch_clicked()
{
    QString movie = ui->lineEditMovie->text();
    QString year = ui->lineEditYear->text();
    QString category = ui->lineEditCategory->text();

    if(movie != "" && year != "" && category != "" ){ // поиск по всем полям
        ConnectDataBase::model->setFilter(" Name = '" + movie  +"' And Year = '" + year + "' and Category = '" + category + "' ");
    }

    if(movie != "" && year != "" && category == "" ){  //поиск по названию и году
        ConnectDataBase::model->setFilter(" Name = '" + movie + "' And Year = '" + year + "' ");
    }

    if(movie != "" && year == "" && category != "" ){ // поиск по названию и жанру
        ConnectDataBase::model->setFilter(" Name = '" + movie + "'  and Category = '" + category + "' ");
    }

    if(movie == "" && year != "" && category != "" ){  // поиск по году и жанру
        ConnectDataBase::model->setFilter("  Year = '" + year + "' and Category = '" + category + "' ");
    }

    if(movie == "" && year == "" && category != "" ){ // поиск по жанру
        ConnectDataBase::model->setFilter("  Category = '" + category + "' ");
    }

    if(movie == "" && year != "" && category == "" ){ // поиск по году
        ConnectDataBase::model->setFilter("  Year = '" + year + "'  ");
    }

    if(movie != "" && year == "" && category == "" ){ // поиск по названию
        ConnectDataBase::model->setFilter(" Name = '" + movie + "'");
    }

    ConnectDataBase::model->select(); // Делаем выборку данных из таблицы
}

void MainWindow::on_pushButtonSort_clicked()
{
    QButtonGroup group;
    QList<QRadioButton *> allButtons = ui->groupBoxSort->findChildren<QRadioButton *>();

    for(int i = 0; i < allButtons.size(); ++i)
    {
        group.addButton(allButtons[i], i);
    }

    switch(group.checkedId())
    {
    case 0:
        ConnectDataBase::model->setSort(1, Qt::AscendingOrder);
        break;
    case 1:
        ConnectDataBase::model->setSort(2, Qt::AscendingOrder);
        break;
    case 2:
        ConnectDataBase::model->setSort(3, Qt::AscendingOrder);
        break;
    default:
        break;
    }

    ConnectDataBase::model->select(); // Делаем выборку данных из таблицы
}

void MainWindow::on_pushButtonOpen_clicked()
{
    if(index.row() < 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Выберите фильм");
        msgBox.exec();
    }
    else
    {
        OpenWindow windowOpen(index);
        windowOpen.setModal(true);
        windowOpen.exec();
    }

    ConnectDataBase::model->select(); // Делаем выборку данных из таблицы
}

void MainWindow::on_pushButtonAdd_clicked()
{
    AddWindow windowAdd;
    windowAdd.setModal(true);
    windowAdd.exec();

    ConnectDataBase::model->select(); // Делаем выборку данных из таблицы
}

void MainWindow::on_pushButtonEdit_clicked()
{
    EditWindow windowEdit(index);
    windowEdit.setModal(true);
    windowEdit.exec();

    ConnectDataBase::model->select(); // Делаем выборку данных из таблицы
}

void MainWindow::on_pushButtonDelete_clicked()
{
    if(index.row() < 0)
    {
        QMessageBox msgBoxChoose;
        msgBoxChoose.setText("Выберите фильм");
        msgBoxChoose.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Вы действительно хотите удалить данный фильм?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int res = msgBox.exec();
        switch(res)
        {
        case QMessageBox::Yes:
             ConnectDataBase::db->deleteFromTable(index.sibling(index.row(), 0).data().toInt());
             break;
         case QMessageBox::No:
             break;
         default:
             break;
        }
    }

    ConnectDataBase::model->select(); // Делаем выборку данных из таблицы
}

void MainWindow::on_pushButtonClean_clicked()
{
    ui->lineEditMovie->clear();
    ui->lineEditYear->clear();
    ui->lineEditCategory->clear();

    ConnectDataBase::model->setFilter("");
    ConnectDataBase::model->select();
}

void MainWindow::on_tableViewMovies_pressed(const QModelIndex &index)
{
    this->index = index;
}
