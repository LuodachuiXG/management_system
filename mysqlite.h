#ifndef MYSQLITE_H
#define MYSQLITE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class MySQLite
{
public:
    MySQLite();
    bool openDb(void);
    QSqlQuery query(QString sql);
    bool execute(QString sql);
    bool isTableExist(QString tableName);
    void close();

private:
    QSqlDatabase database;
};

#endif // MYSQLITE_H
