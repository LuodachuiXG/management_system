#include "mysqlite.h"
#include "sqlexception.cpp"

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
}

/**
 * 打开数据库
 * @brief MySQLite::openDb
 * @return
 */
bool MySQLite::openDb()
{
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
        return false;
    }
    return true;
}

/**
 * 执行 SQL 语句
 * @brief execute
 * @param sql
 * @return 执行结果
 */
bool MySQLite::execute(QString sql)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare(sql);
    if (sqlQuery.exec()) {
        return true;
    }
    else {
        qDebug() << sqlQuery.lastError();
        return false;
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

