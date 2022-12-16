#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sqlexception.cpp>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(900, 700);
    init();
}

// 初始化数据
void MainWindow::init()
{
    // 初始化 SQLController
    sqlController = new SQLController;

    // 设置学生表格项
    studentModel = new QStandardItemModel();
    ui->student_tableView->setModel(studentModel);
    studentModel->setHorizontalHeaderItem(0, new QStandardItem("编号"));
    studentModel->setHorizontalHeaderItem(1, new QStandardItem("姓名"));
    studentModel->setHorizontalHeaderItem(2, new QStandardItem("性别"));
    studentModel->setHorizontalHeaderItem(3, new QStandardItem("出生年月"));
    studentModel->setHorizontalHeaderItem(4, new QStandardItem("年龄"));
    studentModel->setHorizontalHeaderItem(5, new QStandardItem("专业"));
    studentModel->setHorizontalHeaderItem(6, new QStandardItem("班级"));
    ui->student_tableView->setColumnWidth(0, 30);
    ui->student_tableView->setColumnWidth(1, 90);
    ui->student_tableView->setColumnWidth(2, 20);
    ui->student_tableView->setColumnWidth(3, 150);
    ui->student_tableView->setColumnWidth(4, 20);
    ui->student_tableView->setColumnWidth(5, 140);
    // 只能选择一列
    ui->student_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    // 可弹出右键菜单
    ui->student_tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    // 新建右键弹出菜单
    studentPopMenu = new QMenu(ui->student_tableView);
    deleteStudent = new QAction("删除学生", ui->student_tableView);
    studentPopMenu->addAction(deleteStudent);
    connect(deleteStudent, SIGNAL(triggered()), this, SLOT(slotDeleteStudent()));
    connect(ui->student_tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotStudentTableViewMenu(QPoint)));

    // 刷新学生数据
    updateStudents();

    // 初始化学生页面添加学生组件数据
    ui->student_genderComboBox->addItem("男");
    ui->student_genderComboBox->addItem("女");

}

MainWindow::~MainWindow()
{
    delete ui;
}

// 刷新学生数据
void MainWindow::updateStudents()
{
    studentModel->removeRows(0, studentModel->rowCount());
    // 获取数据库中所有学生
    vector<Student> students;
    students = sqlController->getAllStudent();
    int cout = 0;
    for (auto it = students.begin(); it != students.end(); it++)
    {
        studentModel->setItem(cout, 0, new QStandardItem(QString::number(it->getId())));
        studentModel->setItem(cout, 1, new QStandardItem(it->getName()));
        studentModel->setItem(cout, 2, new QStandardItem(it->getGender()));
        studentModel->setItem(cout, 3, new QStandardItem(it->getBirth().toString("yyyy年MM月dd日")));
        studentModel->setItem(cout, 4, new QStandardItem(QString::number(it->getAge())));
        studentModel->setItem(cout, 5, new QStandardItem(it->getMajor()));
        studentModel->setItem(cout, 6, new QStandardItem(it->getClassName()));
        cout++;
    }
}

// 添加学生按钮单击事件
void MainWindow::on_student_addBtn_clicked()
{
    QString name = ui->student_nameEdit->toPlainText();
    QString gender = ui->student_genderComboBox->currentText();
    QDate birth = ui->student_birthDateEdit->date();
    QString major = ui->student_majorEdit->toPlainText();
    QString className = ui->student_classNameEdit->toPlainText();
    Student s(0, name, gender, birth, major, className);
    if (name.isEmpty() || major.isEmpty() || className.isEmpty())
    {
        QMessageBox::information(this, "添加失败", "请将信息填写完整");
        return;
    }
    try
    {
        sqlController->insertStudent(s);
        // 添加成功，刷新学生数据
        updateStudents();
    }
    catch(SQLException e)
    {
        // 添加失败
        QMessageBox::critical(this, "添加失败", e.message());
    }

}

// 学生表格右键菜单事件
void MainWindow::slotStudentTableViewMenu(QPoint pos){
    // 鼠标点击位置索引
    QModelIndex index = ui->student_tableView->indexAt(pos);
    if (index.isValid())
    {
        // 右键数据项有效
        studentPopMenu->exec(QCursor::pos());
    }
}

// 删除学生点击事件
void MainWindow::slotDeleteStudent()
{
    // 右键的行索引
    int row = ui->student_tableView->currentIndex().row();
    QModelIndex index = studentModel->index(row, 0);
    QString id = studentModel->data(index).toString();
    try
    {
        sqlController->deleteStudent(id);
        // 删除成功，刷新学生数据
        updateStudents();
    }
    catch(SQLException e)
    {
        // 删除失败
        QMessageBox::critical(this, "添加失败", e.message());
    }
}

