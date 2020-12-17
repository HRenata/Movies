#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{

}

/* Методы для подключения к базе данных
 * */
void DataBase::connectToDataBase()
{
    /* Перед подключением к базе данных производим проверку на её существование.
     * В зависимости от результата производим открытие базы данных или её восстановление
     * */

    QDir().mkdir("../db");

    if(!QFile("../db/" DATABASE_NAME).exists())
    {
        this->restoreDataBase();
    }
    else
    {
        this->openDataBase();
    }
}

/* Методы восстановления базы данных
 * */
bool DataBase::restoreDataBase()
{
    if(this->openDataBase())
    {
        if(!this->createTable())
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

/* Метод для открытия базы данных
 * */
bool DataBase::openDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName("../db/" DATABASE_NAME);
    if(db.open())
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* Методы закрытия базы данных
 * */
void DataBase::closeDataBase()
{
    db.close();
}

/* Метод для создания таблицы в базе данных
 * */
bool DataBase::createTable()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " TABLE " ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    TABLE_NAME          " VARCHAR(255)    NOT NULL,"
                    TABLE_YEAR          " INTEGER         NOT NULL,"
                    TABLE_CATEGORY      " VARCHAR(255)    NOT NULL,"
                    TABLE_DESCRIPTION   " TEXT            NOT NULL"
                    ")"
                    )
            )
    {
        qDebug() << "DataBase: error of create " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    }
    else
    {
        return true;
    }
    return false;
}

/* Метод для вставки записи в базу данных
 * */
bool DataBase::inserIntoTable(const QVariantList &data)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO " TABLE " ( " TABLE_NAME ", "
                                             TABLE_YEAR ", "
                                             TABLE_CATEGORY ", "
                                             TABLE_DESCRIPTION " ) "
                  "VALUES (:Name, :Year, :Category, :Description )");
    query.bindValue(":Name",            data[0].toString());
    query.bindValue(":Year",            data[1].toInt());
    query.bindValue(":Category",        data[2].toString());
    query.bindValue(":Description",     data[3].toString());
    // После чего выполняется запросом методом exec()
    if(!query.exec())
    {
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    }
    else
    {
        return true;
    }
    return false;
}

/* Метод для редактирования записи из базы данных
 * */
bool DataBase::updateNode(const int id, const QVariantList &data)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("UPDATE " TABLE " SET "
                  TABLE_NAME "=:Name, "
                  TABLE_YEAR "=:Year, "
                  TABLE_CATEGORY "=:Category, "
                  TABLE_DESCRIPTION "=:Description  "
                                    "WHERE id = :Id");
    query.bindValue(":Name",            data[0].toString());
    query.bindValue(":Year",            data[1].toInt());
    query.bindValue(":Category",        data[2].toString());
    query.bindValue(":Description",     data[3].toString());
    query.bindValue(":Id",              id);

    // После чего выполняется запросом методом exec()
    if(!query.exec())
    {
        qDebug() << "error deleting from " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    }
    else
    {
        return true;
    }
    return false;
}

/* Метод для удаления записи из базы данных
 * */
bool DataBase::deleteFromTable(const int &id)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("DELETE FROM " TABLE " WHERE id = :Id ");
    query.bindValue(":Id",            id);

    // После чего выполняется запросом методом exec()
    if(!query.exec())
    {
        qDebug() << "error deleting from " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    }
    else
    {
        return true;
    }
    return false;
}
