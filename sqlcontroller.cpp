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


/**
 * 获取所有行政人员数据
 * @brief getAllAdminTeacher
 * @return
 */
vector<AdminTeacher> SQLController::getAllAdminTeacher()
{
    vector<AdminTeacher> list;
    QString sql = "SELECT * FROM teacher WHERE type='行政人员';";
    QSqlQuery query = sqlite->query(sql);
    while (query.next())
    {
        AdminTeacher at;
        at.setId(query.value("id").toInt());
        at.setName(query.value("name").toString());
        at.setGender(query.value("gender").toString());
        at.setBirth(query.value("birth").toDate());
        at.setStartDate(query.value("startDate").toDate());
        at.setDepartment(query.value("department").toString());
        at.setPost(query.value("post").toString());
        list.push_back(at);
    }
    return list;
}

/**
 * 添加行政人员
 * @brief insertAdminTeacher
 * @param teacher
 */
void SQLController::insertAdminTeacher(AdminTeacher &teacher)
{
    QString sql = "INSERT INTO teacher(id, name, gender, birth, startDate, department, post, type)"
                  "VALUES(NULL, ?, ?, ?, ?, ?, ?, ?);";
    QSqlQuery query;
    query.prepare(sql);
    query.addBindValue(teacher.getName());
    query.addBindValue(teacher.getGender());
    query.addBindValue(teacher.getBirth());
    query.addBindValue(teacher.getStartDate());
    query.addBindValue(teacher.getDepartment());
    query.addBindValue(teacher.getPost());
    query.addBindValue("行政人员");
    sqlite->execute(query);
}

/**
 * 获取所有专任教师数据
 * @brief getAllFullTimeTeacher
 * @return
 */
vector<FullTimeTeacher> SQLController::getAllFullTimeTeacher()
{
    vector<FullTimeTeacher> list;
    QString sql = "SELECT * FROM teacher WHERE type='专任教师';";
    QSqlQuery query = sqlite->query(sql);
    while (query.next())
    {
        FullTimeTeacher ftt;
        ftt.setId(query.value("id").toInt());
        ftt.setName(query.value("name").toString());
        ftt.setGender(query.value("gender").toString());
        ftt.setBirth(query.value("birth").toDate());
        ftt.setStartDate(query.value("startDate").toDate());
        ftt.setDepartment(query.value("department").toString());
        ftt.setTitle(query.value("title").toString());
        list.push_back(ftt);
    }
    return list;
}

/**
 * 添加专任教师
 * @brief insertFullTimeTeacher
 * @param teacher
 */
void SQLController::insertFullTimeTeacher(FullTimeTeacher &teacher)
{
        QString sql = "INSERT INTO teacher(id, name, gender, birth, startDate, department, title, type)"
                      "VALUES(NULL, ?, ?, ?, ?, ?, ?, ?);";
        QSqlQuery query;
        query.prepare(sql);
        query.addBindValue(teacher.getName());
        query.addBindValue(teacher.getGender());
        query.addBindValue(teacher.getBirth());
        query.addBindValue(teacher.getStartDate());
        query.addBindValue(teacher.getDepartment());
        query.addBindValue(teacher.getTitle());
        query.addBindValue("专任教师");
        sqlite->execute(query);
}

/**
 * 更新行政人员
 * @brief SQLController::updateAdminTeacher
 * @param teacher
 * @param convertType 转换教师类型
 */
void SQLController::updateAdminTeacher(AdminTeacher &teacher, bool convertType)
{
    // 如果 convertType 为 true，证明要从行政人员转为专任教师，所以这里为 title 而不是 post
    QString sql = "UPDATE teacher SET name=?, gender=?, birth=?, startDate=?, department=?, "
                  + QString(convertType ? "title" : "post") + "=?, type=? WHERE id=?";
    QSqlQuery query;
    query.prepare(sql);
    query.addBindValue(teacher.getName());
    query.addBindValue(teacher.getGender());
    query.addBindValue(teacher.getBirth());
    query.addBindValue(teacher.getStartDate());
    query.addBindValue(teacher.getDepartment());
    query.addBindValue(teacher.getPost());
    query.addBindValue(convertType ? "专任教师" : "行政人员");
    query.addBindValue(teacher.getId());
    sqlite->execute(query);
}

/**
 * 更新专任教师
 * @brief SQLController::updateFullTimeTeacher
 * @param teacher
 * @param convertType
 */
void SQLController::updateFullTimeTeacher(FullTimeTeacher &teacher, bool convertType)
{
    // 如果 convertType 为 true，证明要从专任教师转为行政人员，所以这里为 post 而不是 title
    QString sql = "UPDATE teacher SET name=?, gender=?, birth=?, startDate=?, department=?,"
                  + QString(convertType ? "post" : "title") + " =?, type=? WHERE id=?";
    QSqlQuery query;
    query.prepare(sql);
    query.addBindValue(teacher.getName());
    query.addBindValue(teacher.getGender());
    query.addBindValue(teacher.getBirth());
    query.addBindValue(teacher.getStartDate());
    query.addBindValue(teacher.getDepartment());
    query.addBindValue(teacher.getTitle());
    query.addBindValue(convertType ? "行政人员" : "专任教师");
    query.addBindValue(teacher.getId());
    sqlite->execute(query);
}

/**
 * 删除教师
 * @brief SQLController::deleteTeachert
 * @param id
 */
void SQLController::deleteTeachert(QString &id)
{
    QString sql = "DELETE FROM teacher WHERE id=?";
    QSqlQuery query;
    query.prepare(sql);
    query.addBindValue(id);
    sqlite->execute(query);
}



/**
 * 根据姓名获取学生
 * @brief getStudentByName
 * @param name
 * @return
 */
vector<Student> SQLController::getStudentByName(QString name)
{
    vector<Student> students = getAllStudent();
    vector<Student> result;
    for (auto it = students.begin(); it != students.end(); it++)
    {
        if (it->getName() == name)
            result.push_back(*it);
    }
    return result;
}

/**
 * 根据专业获取学生
 * @brief SQLController::getStudentByMajor
 * @param major
 * @return
 */
vector<Student> SQLController::getStudentByMajor(QString major)
{
    vector<Student> students = getAllStudent();
    vector<Student> result;
    for (auto it = students.begin(); it != students.end(); it++)
    {
        if (it->getMajor() == major)
            result.push_back(*it);
    }
    return result;
}

/**
 * 根据姓名获取行政人员
 * @brief SQLController::getAdminTeacherByName
 * @param name
 * @return
 */
vector<AdminTeacher> SQLController::getAdminTeacherByName(QString name)
{
    vector<AdminTeacher> teachers = getAllAdminTeacher();
    vector<AdminTeacher> result;
    for (auto it = teachers.begin(); it != teachers.end(); it++)
    {
        if (it->getName() == name)
            result.push_back(*it);
    }
    return result;
}

/**
 * 根据系部获取行政人员
 * @brief SQLController::getAdminTeacherByDepartment
 * @param department
 * @return
 */
vector<AdminTeacher> SQLController::getAdminTeacherByDepartment(QString department)
{
    vector<AdminTeacher> teachers = getAllAdminTeacher();
    vector<AdminTeacher> result;
    for (auto it = teachers.begin(); it != teachers.end(); it++)
    {
        if (it->getDepartment() == department)
            result.push_back(*it);
    }
    return result;
}

/**
 * 根据姓名获取专任教师
 * @brief SQLController::getFullTimeTeacherByName
 * @param name
 * @return
 */
vector<FullTimeTeacher> SQLController::getFullTimeTeacherByName(QString name)
{
    vector<FullTimeTeacher> teachers = getAllFullTimeTeacher();
    vector<FullTimeTeacher> result;
    for (auto it = teachers.begin(); it != teachers.end(); it++)
    {
        if (it->getName() == name)
            result.push_back(*it);
    }
    return result;
}

/**
 * 根据系部获取专任教师
 * @brief SQLController::getFullTimeTeacherByDepartment
 * @param department
 * @return
 */
vector<FullTimeTeacher> SQLController::getFullTimeTeacherByDepartment(QString department)
{
    vector<FullTimeTeacher> teachers = getAllFullTimeTeacher();
    vector<FullTimeTeacher> result;
    for (auto it = teachers.begin(); it != teachers.end(); it++)
    {
        if (it->getDepartment() == department)
            result.push_back(*it);
    }
    return result;
}

