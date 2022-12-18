#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <sqlcontroller.h>
#include <QMenu>
#include <QAction>
#include <myio.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 初始化窗口
    void init();

    // 更新学生数据
    void updateStudents();

    // 清除学生页面编辑区域数据
    void clearStudentEdit();

    // 更新教师数据，0：行政人员，1：专任教师
    void updateTeachers(int type);

    // 清除教师页面编辑区域数据
    void clearTeacherEdit();

    // 更新搜索结果
    void updateSearch();


private slots:
    void on_student_addBtn_clicked();
    // 右键学生表格弹出菜单
    void slotStudentTableViewMenu(QPoint pos);
    // 删除学生槽
    void slotDeleteStudent();
    // 计算学生平均年龄槽
    void slotCalStudentAvgAge();
    // 导出学生槽
    void slotExportStudents();

    // 右键教师表格弹出菜单
    void slotTeacherTableViewMenu(QPoint pos);
    // 删除教师槽
    void slotDeleteTeacher();
    // 计算教师平均年龄槽
    void slotCalTeacherAvgAge();
    // 导出教师槽
    void slotExportTeachers();

    // 右键搜索表格弹出菜单
    void slotSearchTableViewMenu(QPoint pos);
    // 搜索页面删除槽
    void slotSearchDelete();
    // 搜索页面计算平均年龄槽
    void slotSearchCalAvgAge();
    // 搜索页面导出数据槽
    void slotSearchExport();


    void on_student_tableView_clicked(const QModelIndex &index);

    void on_student_saveBtn_clicked();

    void on_student_returnBtn_clicked();

    void on_teacher_typeComboBox_currentIndexChanged(int index);

    void on_teacher_typeComboBoxEdit_currentIndexChanged(int index);

    void on_teacher_addBtn_clicked();

    void on_teacher_returnBtn_clicked();

    void on_teacher_tableView_clicked(const QModelIndex &index);

    void on_teacher_saveBtn_clicked();

    void on_menu_about_triggered();

    void on_menu_importStudent_triggered();

    void on_menu_importAdminTeacher_triggered();

    void on_menu_importFullTimeTeacher_triggered();

    void on_menu_exit_triggered();

    void on_tabWidget_currentChanged(int index);

    void on_search_groupComboBox_currentIndexChanged(int index);

    void on_search_typeComboBox_currentTextChanged(const QString &arg1);

    void on_search_searchBtn_clicked();

    void on_search_typeComboBox_currentIndexChanged(int index);

private:
    // 当前选中的学生表行数索引
    int currentStudentIndex = 0;
    // 当前选中的教师表行数索引
    int currentTeacherIndex = 0;
    // 当前选中的教师类型，0：行政人员，1：专任教师
    int currentTeacherType = 0;

    Ui::MainWindow *ui;
    SQLController *sqlController;
    // 文件输入输出流
    MyIO myio;

    /** 学生页面变量 **/
    QStandardItemModel *studentModel;
    vector<Student> students;
    QMenu *studentPopMenu;
    QAction *deleteStudent;
    QAction *calStudentAvgAge;
    QAction *exportStudents;

    /** 教师页面变量 **/
    QStandardItemModel *adminTeacherModel;
    QStandardItemModel *fullTimeTeacherModel;
    vector<AdminTeacher> adminTeachers;
    vector<FullTimeTeacher> fullTimeTeachers;
    QMenu *teacherPopMenu;
    QAction *deleteTeacher;
    QAction *calTeacherAvgAge;
    QAction *exportTeachers;


    /** 搜索页面变量 **/
    QStandardItemModel *searchStudentModel;
    vector<Student> searchStudents;
    QStandardItemModel *searchAdminTeacherModel;
    QStandardItemModel *searchFullTimeTeacherModel;
    vector<AdminTeacher> searchAdminTeachers;
    vector<FullTimeTeacher> searchFullTimeTeachers;
    QMenu *searchPopMenu;
    QAction *searchDelete;
    QAction *searchCalAvgAge;
    QAction *searchExport;
    // 搜索条件存储
    QString searchKey;
    QString searchGroup;
    QString searchType;




};

#endif // MAINWINDOW_H
