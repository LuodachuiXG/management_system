#include "person.h"

Person::Person() {}
Person::Person(int id, QString name, QString gender, QDate birth)
{
    this->id = id;
    this->name = name;
    this->gender = gender;
    this->birth = birth;
}

int Person::getId()
{
    return id;
}

void Person::setId(int id)
{

    this->id = id;
}

QString Person::getName()
{
    return name;
}

void Person::setName(QString name)
{
    this->name = name;
}

QString Person::getGender()
{
    return gender;
}

void Person::setGender(QString gender)
{
    this->gender = gender;
}

QDate Person::getBirth()
{
    return birth;
}

void Person::setBirth(QDate birth)
{
    this->birth = birth;
}

int Person::getAge()
{
    // 计算年龄
    QDate today = QDate::currentDate();
    return this->birth.daysTo(today) / 365;
}

Student::Student() {}
Student::Student(int id, QString name, QString gender, QDate birth, QString major, QString className):
        Person(id, name, gender, birth)
{
    this->major = major;
    this->className = className;
}

QString Student::getMajor()
{
    return major;
}

void Student::setMajor(QString major)
{
    this->major = major;
}

QString Student::getClassName()
{
    return className;
}

void Student::setClassName(QString className)
{
    this->className = className;
}

Teacher::Teacher() {}
Teacher::Teacher(int id, QString name, QString gender, QDate birth, QDate startDate, QString department):
        Person(id, name, gender, birth)
{
    this->startDate = startDate;
    this->department = department;
}

QDate Teacher::getStartDate()
{
    return startDate;
}

void Teacher::setStartDate(QDate startDate)
{
    this->startDate = startDate;
}

QString Teacher::getDepartment()
{
    return department;
}

void Teacher::setDepartment(QString department)
{
    this->department = department;
}

// 行政人员
AdminTeacher::AdminTeacher() {}
    AdminTeacher::AdminTeacher(int id, QString name, QString gender, QDate birth,
                        QDate startDate, QString department, QString post):
        Teacher(id, name, gender, birth, startDate, department)
{
    this->post = post;
}

QString AdminTeacher::getPost()
{
    return post;
}

void AdminTeacher::setPost(QString post)
{
    this->post = post;
}

// 专任教师
FullTimeTeacher::FullTimeTeacher() {}
FullTimeTeacher::FullTimeTeacher(int id, QString name, QString gender, QDate birth,
                    QDate startDate, QString department, QString title):
        Teacher(id, name, gender, birth, startDate, department)
{
    this->title = title;
}

QString FullTimeTeacher::getTitle()
{
    return title;
}

void FullTimeTeacher::setTitle(QString title)
{
    this->title = title;
}
