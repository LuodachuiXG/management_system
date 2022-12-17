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
    void updateStudent(Student &student);
    void deleteStudent(QString &id);

    vector<AdminTeacher> getAllAdminTeacher();
    void insertAdminTeacher(AdminTeacher &teacher);
    vector<FullTimeTeacher> getAllFullTimeTeacher();
    void insertFullTimeTeacher(FullTimeTeacher &teacher);
    void updateAdminTeacher(AdminTeacher &teacher, bool convertType);
    void updateFullTimeTeacher(FullTimeTeacher &teacher, bool convertType);
    void deleteTeachert(QString &id);
private:
    MySQLite *sqlite;
};

#endif // SQLCONTROLLER_H
