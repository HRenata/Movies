#include "connectdatabase.h"

DataBase        *ConnectDataBase::db = new DataBase();

QSqlTableModel  *ConnectDataBase::model = new QSqlTableModel();

void ConnectDataBase::connectToDataBase()
{
    db->connectToDataBase();
}

void ConnectDataBase::setupModel(const QString &tableName, const QStringList &headers)
{
    model->setTable(tableName);

    /* Устанавливаем названия колонок в таблице с сортировкой данных
     * */
    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
    // Устанавливаем сортировку по возрастанию данных по нулевой колонке
    model->setSort(0, Qt::AscendingOrder);
}
