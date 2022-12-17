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
    void init();
    void updateStudents();
    void clearStudentEdit();
    ~MainWindow();

private slots:
    void on_student_addBtn_clicked();
    // 右键学生表格弹出菜单
    void slotStudentTableViewMenu(QPoint pos);
    // 删除学生槽
    void slotDeleteStudent();
    // 计算学生平均年龄槽
    void slotcalStudentAvgAge();

    void on_student_tableView_clicked(const QModelIndex &index);

    void on_student_saveBtn_clicked();

    void on_student_returnBtn_clicked();

private:
    // 当前选中的表行数索引
    int currentIndex = 0;

    Ui::MainWindow *ui;
    SQLController *sqlController;

    QStandardItemModel *studentModel;
    vector<Student> students;
    QMenu *studentPopMenu;
    QAction *deleteStudent;
    QAction *calStudentAvgAge;


    QStandardItemModel *teacherModel;

};

#endif // MAINWINDOW_H
