#ifndef MYIO_H
#define MYIO_H
#include "person.h"
class MyIO
{
public:
    MyIO();
    ~MyIO();
    // 将学生写到文件
    void writeStudents(vector<Student> students, QString path);
    // 从文件读取学生
    vector<Student> readStudents(QString path);

    // 将行政人员写到文件
    void writeTeacher(vector<AdminTeacher> teachers, QString path);
    // 将专任教师写到文件
    void writeTeacher(vector<FullTimeTeacher> teachers, QString path);
    // 从文件读取行政人员
    vector<AdminTeacher> readAdminTeachers(QString path);
    // 从文件读取专任教师
    vector<FullTimeTeacher> readFullTimeTeachers(QString path);
};

#endif // MYIO_H
