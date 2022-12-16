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
    ~MainWindow();

private slots:
    void on_student_addBtn_clicked();
    // 右键学生表格弹出菜单
    void slotStudentTableViewMenu(QPoint pos);
    void slotDeleteStudent();

private:
    Ui::MainWindow *ui;

    SQLController *sqlController;
    QStandardItemModel *studentModel;
    QMenu *studentPopMenu;
    QAction *deleteStudent;
    QStandardItemModel *teacherModel;

};

#endif // MAINWINDOW_H
