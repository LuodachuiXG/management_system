#include "mysqlite.h"
#include "sqlexception.cpp"
#include <iostream>
using namespace std;

MySQLite::MySQLite()
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        // 建立数据库连接
        database = QSqlDatabase::addDatabase("QSQLITE");
        // 设置数据库文件名
        database.setDatabaseName("MyDataBase.db");
    }

    openDb();
    if (!isTableExist("student"))
    {
        // 学生表不存在，创建学生表
        QString sql = "CREATE TABLE student("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                      "name TEXT NOT NULL,"
                      "gender TEXT NOT NULL,"
                      "birth DATETIME NOT NULL,"
                      "major TEXT NOT NULL,"
                      "className TEXT NOT NULL"
                      ");";
        execute(sql);
    }

    if (!isTableExist("teacher"))
    {
        // 教师不存在，创建教师表
        QString sql = "CREATE TABLE teacher("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                      "name TEXT NOT NULL,"
                      "gender TEXT NOT NULL,"
                      "birth DATETIME NOT NULL,"
                      "startDate DATETIME NOT NULL,"
                      "department TEXT NOT NULL,"
                      "post TEXT NULL,"
                      "title TEXT NULL,"
                      "type TEXT NOT NULL"
                      ");";
        execute(sql);
    }
}

/**
 * 打开数据库
 * @brief MySQLite::openDb
 * @return
 */
void MySQLite::openDb()
{
    if (!database.open())
    {
        throw SQLException("Error: Failed to connect database.\n" + database.lastError().text());
    }
}

/**
 * 执行 SQL 语句
 * @brief execute
 * @param sql
 * @return 执行结果
 */
void MySQLite::execute(QString sql)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare(sql);
    execute(sqlQuery);
}

/**
 * 执行 SQL 语句
 * @brief execute
 * @param query
 * @return 执行结果
 */
void MySQLite::execute(QSqlQuery query)
{
    if (!query.exec()) {
        throw SQLException(query.lastError().text());
    }
}

/**
 * 查询 SQL 语句
 * @brief query
 * @param sql
 * @return
 */
QSqlQuery MySQLite::query(QString sql)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare(sql);
    if (sqlQuery.exec()) {
        return sqlQuery;
    }
    else
    {
        throw SQLException(sqlQuery.lastError().text());
    }
}

/**
 * 查询表是否存在
 * @brief isTableExist
 * @param tableName
 * @return
 */
bool MySQLite::isTableExist(QString tableName)
{
    QSqlDatabase database = QSqlDatabase::database();
    if (database.tables().contains(tableName))
    {
        return true;
    }
    return false;
}

/**
 * 关闭数据库
 * @brief close
 */
void MySQLite::close()
{
    database.close();
}

