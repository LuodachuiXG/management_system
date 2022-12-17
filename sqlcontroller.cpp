#include "sqlcontroller.h"
SQLController::SQLController()
{
    sqlite = new MySQLite;
}

SQLController::~SQLController()
{
    sqlite->close();
}

/**
 * 获取所有学生数据
 * @brief SQLController::getAllStudent
 * @return
 */
vector<Student> SQLController::getAllStudent()
{
    vector<Student> list;
    QString sql = "SELECT * FROM student;";
    QSqlQuery query = sqlite->query(sql);
    while (query.next())
    {
        Student s;
        s.setId(query.value("id").toInt());
        s.setName(query.value("name").toString());
        s.setGender(query.value("gender").toString());
        s.setBirth(query.value("birth").toDate());
        s.setMajor(query.value("major").toString());
        s.setClassName(query.value("className").toString());
        list.push_back(s);
    }
    return list;
}


/**
 * 添加学生
 * @brief SQLController::insertStudent
 * @param student
 */
void SQLController::insertStudent(Student &student)
{
    QString sql = "INSERT INTO student(id, name, gender, birth, major, className)"
                  "VALUES(NULL, ?, ?, ?, ?, ?);";
    QSqlQuery query;
    query.prepare(sql);
    query.addBindValue(student.getName());
    query.addBindValue(student.getGender());
    query.addBindValue(student.getBirth());
    query.addBindValue(student.getMajor());
    query.addBindValue(student.getClassName());
    sqlite->execute(query);
}

/**
 * 更新学生
 * @brief SQLController::updateStudent
 * @param student
 */
void SQLController::updateStudent(Student &student)
{
    QString sql = "UPDATE student SET name=?, gender=?, birth=?, major=?, className=? WHERE id=?";
    QSqlQuery query;
    query.prepare(sql);
    query.addBindValue(student.getName());
    query.addBindValue(student.getGender());
    query.addBindValue(student.getBirth());
    query.addBindValue(student.getMajor());
    query.addBindValue(student.getClassName());
    query.addBindValue(student.getId());
    sqlite->execute(query);
}

/**
 * 删除学生
 * @brief SQLController::deleteStudent
 * @param id
 */
void SQLController::deleteStudent(QString &id)
{
    QString sql = "DELETE FROM student WHERE id=?";
    QSqlQuery query;
    query.prepare(sql);
    query.addBindValue(id);
    sqlite->execute(query);
}

