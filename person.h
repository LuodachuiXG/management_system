#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QDate>
using namespace std;

class Person {
    int id;
    QString name;
    QString gender;
    QDate birth;
public:
    Person();
    Person(int id, QString name, QString gender, QDate birth);
    int getId();
    void setId(int id);
    QString getName();
    void setName(QString name);
    QString getGender();
    void setGender(QString gender);
    QDate getBirth();
    void setBirth(QDate birth);
    int getAge();
};

class Student: public Person
{
    QString major;
    QString className;
public:
    Student();
    Student(int id, QString name, QString gender, QDate birth, QString major, QString className);
    QString getMajor();
    void setMajor(QString major);
    QString getClassName();
    void setClassName(QString className);
};


class Teacher: public Person
{
    QDate startDate;
    QString department;
public:
    Teacher();
    Teacher(int id, QString name, QString gender, QDate birth, QDate startDate, QString department);
    QDate getStartDate();
    void setStartDate(QDate startDate);
    QString getDepartment();
    void setDepartment(QString department);
};

// 行政人员
class AdminTeacher: public Teacher
{
    // 职务
    QString post;
public:
    AdminTeacher();
    AdminTeacher(int id, QString name, QString gender, QDate birth,
                        QDate startDate, QString department, QString post);
    QString getPost();
    void setPost(QString post);
};

// 专任教师
class FullTimeTeacher: public Teacher
{
    // 职称
    QString title;
public:
    FullTimeTeacher();
    FullTimeTeacher(int id, QString name, QString gender, QDate birth,
                    QDate startDate, QString department, QString title);
    QString getTitle();
    void setTitle(QString title);
};
#endif // PERSON_H
