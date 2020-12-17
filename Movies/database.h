#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QDir>

/* Директивы имен таблицы, полей таблицы и базы данных */
#define DATABASE_HOSTNAME   "MoviesDatabase"
#define DATABASE_NAME       "MoviesDataBase.db"

#define TABLE                   "Movies"
#define TABLE_NAME              "Name"
#define TABLE_YEAR              "Year"
#define TABLE_CATEGORY          "Category"
#define TABLE_DESCRIPTION       "Description"
#define TABLE_IMAGE             "Image"

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    /* Методы для непосредственной работы с классом
     * Подключение к базе данных и вставка записей в таблицу
     * */
    void connectToDataBase();
    bool inserIntoTable(const QVariantList &data);
    bool updateNode(const int id, const QVariantList &data);
    bool deleteFromTable(const int &id);

private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase    db;

private:
    /* Внутренние методы для работы с базой данных
     * */
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTable();
};

#endif // DATABASE_H
