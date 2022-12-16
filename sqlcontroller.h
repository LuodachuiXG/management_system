#ifndef SQLCONTROLLER_H
#define SQLCONTROLLER_H
#include <mysqlite.h>
#include <vector>
#include <person.cpp>


class SQLController
{
public:
    SQLController();
    ~SQLController();
    vector<Student> getAllStudent();
    void insertStudent(Student &student);
    void deleteStudent(QString &id);
private:
    MySQLite *sqlite;
};

#endif // SQLCONTROLLER_H
