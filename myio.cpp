#include "myio.h"
#include "fstream"
#include "myexception.h"
#include <iostream>
using namespace std;

MyIO::MyIO()
{

}

MyIO::~MyIO()
{

}


/**
 * 将学生数据写到文件
 * @brief MyIO::writeStudents
 * @param students
 * @param path
 */
void MyIO::writeStudents(vector<Student> students, QString path)
{
    ofstream outfile;
    outfile.open(path.toLocal8Bit().data());
    if (!outfile.is_open())
    {
        throw IOException("保存文件失败，请检查文件是否被占用或无权限读写");
    }
    for (auto it = students.begin(); it != students.end(); it++)
    {
        outfile << it->getName().toLocal8Bit().data() << "\t"
                << it->getGender().toLocal8Bit().data() << "\t"
                << it->getBirth().toString("yyyy年MM月dd日").toLocal8Bit().data() << "\t"
                << it->getAge() << "\t"
                << it->getMajor().toLocal8Bit().data() << "\t"
                << it->getClassName().toLocal8Bit().data() << endl;
    }
    outfile.close();
}

/**
 * 从文件读取学生数据
 * @brief MyIO::readStudents
 * @param path
 * @return
 */
vector<Student> MyIO::readStudents(QString path)
{
    vector<Student> students;
    ifstream infile;
    infile.open(path.toLocal8Bit().data());
    if (!infile.is_open())
    {
        throw IOException("打开文件失败，请检查文件是否被占用或无权限读写");
    }

    string str;
    while (getline(infile, str))
    {
        Student student;
        QString myStr = QString::fromLocal8Bit(str.c_str());
        QStringList myStrSplice = myStr.split("#");
        if (myStrSplice.size() < 5)
            throw IOException("数据格式有误，导入数据失败");
        student.setName(myStrSplice[0]);
        student.setGender(myStrSplice[1]);
        if (myStrSplice[2].size() < 11)
            throw IOException("出生日期格式有误，导入数据失败");
        int year, month, day;
        year = myStrSplice[2].split("年")[0].toInt();
        month = myStrSplice[2].split("月")[0].rightRef(2).toInt();
        day = myStrSplice[2].split("日")[0].rightRef(2).toInt();
        student.setBirth(QDate(year, month, day));
        student.setMajor(myStrSplice[3]);
        student.setClassName(myStrSplice[4]);
        students.push_back(student);
    }
    return students;
}

/**
 * 将行政人员数据写到文件
 * @brief MyIO::writeTeacher
 * @param teachers
 * @param path
 */
void MyIO::writeTeacher(vector<AdminTeacher> teachers, QString path)
{
    ofstream outfile;
    outfile.open(path.toLocal8Bit().data());
    if (!outfile.is_open())
    {
        throw IOException("保存文件失败，请检查文件是否被占用或无权限读写");
    }
    for (auto it = teachers.begin(); it != teachers.end(); it++)
    {
        outfile << it->getName().toLocal8Bit().data() << "\t"
                << it->getGender().toLocal8Bit().data() << "\t"
                << it->getBirth().toString("yyyy年MM月dd日").toLocal8Bit().data() << "\t"
                << it->getAge() << "\t"
                << it->getStartDate().toString("yyyy年MM月dd日").toLocal8Bit().data() << "\t"
                << it->getDepartment().toLocal8Bit().data() << "\t"
                << it->getPost().toLocal8Bit().data() << endl;
    }
    outfile.close();
}

/**
 * 将专任教师写到文件
 * @brief writeTeacher
 * @param teachers
 * @param path
 */
void MyIO::writeTeacher(vector<FullTimeTeacher> teachers, QString path)
{
    ofstream outfile;
    outfile.open(path.toLocal8Bit().data());
    if (!outfile.is_open())
    {
        throw IOException("保存文件失败，请检查文件是否被占用或无权限读写");
    }
    for (auto it = teachers.begin(); it != teachers.end(); it++)
    {
        outfile << it->getName().toLocal8Bit().data() << "\t"
                << it->getGender().toLocal8Bit().data() << "\t"
                << it->getBirth().toString("yyyy年MM月dd日").toLocal8Bit().data() << "\t"
                << it->getAge() << "\t"
                << it->getStartDate().toString("yyyy年MM月dd日").toLocal8Bit().data() << "\t"
                << it->getDepartment().toLocal8Bit().data() << "\t"
                << it->getTitle().toLocal8Bit().data() << endl;
    }
    outfile.close();
}


/**
 * 从文件读取行政人员数据
 * @brief readAdminTeachers
 * @param path
 * @return
 */
vector<AdminTeacher> MyIO::readAdminTeachers(QString path)
{
    vector<AdminTeacher> teachers;
    ifstream infile;
    infile.open(path.toLocal8Bit().data());
    if (!infile.is_open())
    {
        throw IOException("打开文件失败，请检查文件是否被占用或无权限读写");
    }

    string str;
    while (getline(infile, str))
    {
        AdminTeacher teacher;
        QString myStr = QString::fromLocal8Bit(str.c_str());
        QStringList myStrSplice = myStr.split("#");
        if (myStrSplice.size() < 6)
            throw IOException("数据格式有误，导入数据失败");
        teacher.setName(myStrSplice[0]);
        teacher.setGender(myStrSplice[1]);

        if (myStrSplice[2].size() < 11)
            throw IOException("出生日期格式有误，导入数据失败");
        int year, month, day;
        year = myStrSplice[2].split("年")[0].toInt();
        month = myStrSplice[2].split("月")[0].rightRef(2).toInt();
        day = myStrSplice[2].split("日")[0].rightRef(2).toInt();
        teacher.setBirth(QDate(year, month, day));

        if (myStrSplice[3].size() < 11)
            throw IOException("工作时间格式有误，导入数据失败");
        year = myStrSplice[3].split("年")[0].toInt();
        month = myStrSplice[3].split("月")[0].rightRef(2).toInt();
        day = myStrSplice[3].split("日")[0].rightRef(2).toInt();
        teacher.setStartDate(QDate(year, month, day));
        teacher.setDepartment(myStrSplice[4]);
        teacher.setPost(myStrSplice[5]);
        teachers.push_back(teacher);
    }
    return teachers;
}

/**
 * 从文件读取专任教师数据
 * @brief readFullTimeTeachers
 * @param path
 * @return
 */
vector<FullTimeTeacher> MyIO::readFullTimeTeachers(QString path)
{
    vector<FullTimeTeacher> teachers;
    ifstream infile;
    infile.open(path.toLocal8Bit().data());
    if (!infile.is_open())
    {
        throw IOException("打开文件失败，请检查文件是否被占用或无权限读写");
    }

    string str;
    while (getline(infile, str))
    {
        FullTimeTeacher teacher;
        QString myStr = QString::fromLocal8Bit(str.c_str());
        QStringList myStrSplice = myStr.split("#");
        if (myStrSplice.size() < 6)
            throw IOException("数据格式有误，导入数据失败");
        teacher.setName(myStrSplice[0]);
        teacher.setGender(myStrSplice[1]);

        if (myStrSplice[2].size() < 11)
            throw IOException("出生日期格式有误，导入数据失败");
        int year, month, day;
        year = myStrSplice[2].split("年")[0].toInt();
        month = myStrSplice[2].split("月")[0].rightRef(2).toInt();
        day = myStrSplice[2].split("日")[0].rightRef(2).toInt();
        teacher.setBirth(QDate(year, month, day));

        if (myStrSplice[3].size() < 11)
            throw IOException("工作时间格式有误，导入数据失败");
        year = myStrSplice[3].split("年")[0].toInt();
        month = myStrSplice[3].split("月")[0].rightRef(2).toInt();
        day = myStrSplice[3].split("日")[0].rightRef(2).toInt();
        teacher.setStartDate(QDate(year, month, day));
        teacher.setDepartment(myStrSplice[4]);
        teacher.setTitle(myStrSplice[5]);
        teachers.push_back(teacher);
    }
    return teachers;
}
