#ifndef MYIO_H
#define MYIO_H
#include "person.h"
class MyIO
{
public:
    MyIO();
    ~MyIO();
    void writeStudents(vector<Student> students, QString path);
    vector<Student> readStudents(QString path);

    void writeTeacher(vector<AdminTeacher> teachers, QString path);
    void writeTeacher(vector<FullTimeTeacher> teachers, QString path);
    vector<AdminTeacher> readAdminTeachers(QString path);
    vector<FullTimeTeacher> readFullTimeTeachers(QString path);
};

#endif // MYIO_H
