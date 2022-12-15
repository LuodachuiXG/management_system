#include "mysqlite.h"

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
bool execute(QString &sql)
{

}

