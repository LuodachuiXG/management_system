#ifndef SQLCONTROLLER_H
#define SQLCONTROLLER_H
#include <mysqlite.h>
#include <vector>
#include <person.h>


class SQLController
{
public:
    SQLController();
    ~SQLController();
    // 获取所有学生
    vector<Student> getAllStudent();
    // 插入学生
    void insertStudent(Student &student);
    // 更新学生数据
    void updateStudent(Student &student);
    // 删除学生
    void deleteStudent(QString &id);

    // 获取所有行政人员
    vector<AdminTeacher> getAllAdminTeacher();
    // 获取所有专任教师
    vector<FullTimeTeacher> getAllFullTimeTeacher();
    // 插入行政人员
    void insertAdminTeacher(AdminTeacher &teacher);
    // 插入专任教师
    void insertFullTimeTeacher(FullTimeTeacher &teacher);
    // 更新行政人员数据
    void updateAdminTeacher(AdminTeacher &teacher, bool convertType);
    // 更新专任教师数据
    void updateFullTimeTeacher(FullTimeTeacher &teacher, bool convertType);
    // 删除教师
    void deleteTeachert(QString &id);

    // 根据姓名获取学生
    vector<Student> getStudentByName(QString name);
    // 根据专业获取学生
    vector<Student> getStudentByMajor(QString major);
    // 根据姓名获取行政人员
    vector<AdminTeacher> getAdminTeacherByName(QString name);
    // 根据系部获取行政人员
    vector<AdminTeacher> getAdminTeacherByDepartment(QString department);
    // 根据姓名获取专任教师
    vector<FullTimeTeacher> getFullTimeTeacherByName(QString name);
    // 根据系部获取专任教师
    vector<FullTimeTeacher> getFullTimeTeacherByDepartment(QString department);
private:
    MySQLite *sqlite;
};

#endif // SQLCONTROLLER_H
