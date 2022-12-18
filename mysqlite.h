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

    // 打开数据库
    void openDb(void);
    // 查询数据
    QSqlQuery query(QString sql);
    // 执行 SQL 语句
    void execute(QString sql);
    // 执行 SQL，QSqlQuery
    void execute(QSqlQuery query);
    // 表是否存在
    bool isTableExist(QString tableName);
    // 关闭数据库
    void close();

private:
    QSqlDatabase database;
};

#endif // MYSQLITE_H
