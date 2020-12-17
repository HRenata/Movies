#ifndef CONNECTDATABASE_H
#define CONNECTDATABASE_H

#include <QSqlTableModel>
#include "database.h"

class ConnectDataBase
{
public:
    static DataBase        *db;
    static QSqlTableModel  *model;

    static void connectToDataBase();
    static void setupModel(const QString &tableName, const QStringList &headers);
};

#endif // CONNECTDATABASE_H
