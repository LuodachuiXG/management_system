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
    void openDb(void);
    QSqlQuery query(QString sql);
    void execute(QString sql);
    void execute(QSqlQuery query);
    bool isTableExist(QString tableName);
    void close();

private:
    QSqlDatabase database;
};

#endif // MYSQLITE_H
