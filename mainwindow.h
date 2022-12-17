#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <sqlcontroller.h>
#include <QMenu>
#include <QAction>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init();
    void updateStudents();
    void clearStudentEdit();

    void updateTeachers(int type);
    void clearTeacherEdit();


private slots:
    void on_student_addBtn_clicked();
    // 右键学生表格弹出菜单
    void slotStudentTableViewMenu(QPoint pos);
    // 删除学生槽
    void slotDeleteStudent();
    // 计算学生平均年龄槽
    void slotcalStudentAvgAge();

    // 右键教师表格弹出菜单
    void slotTeacherTableViewMenu(QPoint pos);
    // 删除教师槽
    void slotDeleteTeacher();
    // 计算教师平均年龄槽
    void slotcalTeacherAvgAge();


    void on_student_tableView_clicked(const QModelIndex &index);

    void on_student_saveBtn_clicked();

    void on_student_returnBtn_clicked();

    void on_action_3_triggered();

    void on_teacher_typeComboBox_currentIndexChanged(int index);

    void on_teacher_typeComboBoxEdit_currentIndexChanged(int index);

    void on_teacher_addBtn_clicked();

    void on_teacher_returnBtn_clicked();

    void on_teacher_tableView_clicked(const QModelIndex &index);

    void on_teacher_saveBtn_clicked();

    void on_action_triggered();

private:
    // 当前选中的学生表行数索引
    int currentStudentIndex = 0;
    // 当前选中的教师表行数索引
    int currentTeacherIndex = 0;
    // 当前选中的教师类型，0：行政人员，1：专任教师
    int currentTeacherType = 0;


    Ui::MainWindow *ui;
    SQLController *sqlController;

    QStandardItemModel *studentModel;
    vector<Student> students;
    QMenu *studentPopMenu;
    QAction *deleteStudent;
    QAction *calStudentAvgAge;
    QAction *exportStudents;


    QStandardItemModel *adminTeacherModel;
    QStandardItemModel *fullTimeTeacherModel;
    vector<AdminTeacher> adminTeachers;
    vector<FullTimeTeacher> fullTimeTeachers;
    QMenu *teacherPopMenu;
    QAction *deleteTeacher;
    QAction *calTeacherAvgAge;
    QAction *exportTeachers;

};

#endif // MAINWINDOW_H
