#include <QString>
#include <QDate>
#include <iostream>
using namespace std;

class Person {
    int id;
    QString name;
    QString gender;
    QDate birth;
public:
    Person() {}
    Person(int id, QString name, QString gender, QDate birth)
    {
        this->id = id;
        this->name = name;
        this->gender = gender;
        this->birth = birth;
    }

    int getId()
    {
        return id;
    }

    void setId(int id)
    {

        this->id = id;
    }

    QString getName()
    {
        return name;
    }

    void setName(QString name)
    {
        this->name = name;
    }

    QString getGender()
    {
        return gender;
    }

    void setGender(QString gender)
    {
        this->gender = gender;
    }

    QDate getBirth()
    {
        return birth;
    }

    void setBirth(QDate birth)
    {
        this->birth = birth;
    }

    int getAge()
    {
        // 计算年龄
        QDate today = QDate::currentDate();
        return this->birth.daysTo(today) / 365;
    }
};

class Student: public Person
{
    QString major;
    QString className;
public:
    Student() {}
    Student(int id, QString name, QString gender, QDate birth, QString major, QString className):
        Person(id, name, gender, birth)
    {
        this->major = major;
        this->className = className;
    }

    QString getMajor()
    {
        return major;
    }

    void setMajor(QString major)
    {
        this->major = major;
    }

    QString getClassName()
    {
        return className;
    }

    void setClassName(QString className)
    {
        this->className = className;
    }

};


class Teacher: public Person
{
    QDate startDate;
    QString department;
public:
    Teacher(int id, QString name, QString gender, QDate birth, QDate startDate, QString department):
        Person(id, name, gender, birth)
    {
        this->startDate = startDate;
        this->department = department;
    }

    QDate getStartDate()
    {
        return startDate;
    }

    void setStartDater(QDate startDate)
    {
        this->startDate = startDate;
    }

    QString getDepartment()
    {
        return department;
    }

    void setDepartment(QString department)
    {
        this->department = department;
    }
};

// 行政人员
class AdministrativeStaff: public Teacher
{
    // 职务
    QString post;
public:
    AdministrativeStaff(int id, QString name, QString gender, QDate birth,
                        QDate startDate, QString department, QString post):
        Teacher(id, name, gender, birth, startDate, department)
    {
        this->post = post;
    }

    QString getPost()
    {
        return post;
    }

    void setPost(QString post)
    {
        this->post = post;
    }
};

// 专任教师
class FullTimeTeacher: public Teacher
{
    // 职称
    QString title;
public:
    FullTimeTeacher(int id, QString name, QString gender, QDate birth,
                    QDate startDate, QString department, QString title):
        Teacher(id, name, gender, birth, startDate, department)
    {
        this->title = title;
    }

    QString getTitle()
    {
        return title;
    }

    void setTitle(QString title)
    {
        this->title = title;
    }
};
