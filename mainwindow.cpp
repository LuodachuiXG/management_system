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

MainWindow::~MainWindow()
{
    delete ui;
    delete sqlController;
    delete studentModel;
    delete studentPopMenu;
    delete deleteStudent;
    delete teacherModel;
}

/**
 * 初始化数据
 * @brief MainWindow::init
 */
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
    // 只能选择一列，选中整行，不可编辑
    ui->student_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->student_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->student_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 设置学生表格可弹出右键菜单
    ui->student_tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    // 新建右键弹出菜单
    studentPopMenu = new QMenu(ui->student_tableView);
    deleteStudent = new QAction("删除学生", ui->student_tableView);
    calStudentAvgAge = new QAction("计算平均年龄", ui->student_tableView);
    studentPopMenu->addAction(deleteStudent);
    studentPopMenu->addAction(calStudentAvgAge);

    // 设置右键弹出菜单和删除学生、计算平均年龄事件槽
    connect(deleteStudent, SIGNAL(triggered()), this, SLOT(slotDeleteStudent()));
    connect(calStudentAvgAge, SIGNAL(triggered()), this, SLOT(slotcalStudentAvgAge()));
    connect(ui->student_tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotStudentTableViewMenu(QPoint)));
    // 刷新学生数据
    updateStudents();
    // 设置学生保存和返回添加按钮默认不显示
    ui->student_saveBtn->setVisible(false);
    ui->student_returnBtn->setVisible(false);


    // 初始化学生页面添加学生组件数据
    ui->student_genderComboBox->addItem("男");
    ui->student_genderComboBox->addItem("女");

}

/**
 * 刷新学生数据
 * @brief MainWindow::updateStudents
 */
void MainWindow::updateStudents()
{
    studentModel->removeRows(0, studentModel->rowCount());
    // 获取数据库中所有学生
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

/**
 * 添加学生按钮单击事件
 * @brief MainWindow::on_student_addBtn_clicked
 */
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

/**
 * 保存学生按钮单击事件
 * @brief MainWindow::on_student_saveBtn_clicked
 */
void MainWindow::on_student_saveBtn_clicked()
{
    int id = students[currentIndex].getId();
    QString name = ui->student_nameEdit->toPlainText();
    QString gender = ui->student_genderComboBox->currentText();
    QDate birth = ui->student_birthDateEdit->date();
    QString major = ui->student_majorEdit->toPlainText();
    QString className = ui->student_classNameEdit->toPlainText();
    Student s(id, name, gender, birth, major, className);
    if (name.isEmpty() || major.isEmpty() || className.isEmpty())
    {
        QMessageBox::information(this, "保存失败", "请将信息填写完整");
        return;
    }
    try
    {
        sqlController->updateStudent(s);
        // 保存成功，刷新学生数据
        updateStudents();
        // 调用返回学生添加按钮点击事件
        on_student_returnBtn_clicked();
    }
    catch (SQLException e)
    {
        // 保存失败
        QMessageBox::critical(this, "保存失败", e.message());
    }
}

/**
 * 返回学生添加按钮单击事件
 * @brief MainWindow::on_student_returnBtn_clicked
 */
void MainWindow::on_student_returnBtn_clicked()
{
    ui->student_saveBtn->setVisible(false);
    ui->student_returnBtn->setVisible(false);
    ui->student_addBtn->setVisible(true);
    // 清除学生信息编辑处的信息
    clearStudentEdit();
    ui->student_tableView->setCurrentIndex(QModelIndex());
}

/**
 * 学生表格右键菜单事件
 * @brief MainWindow::slotStudentTableViewMenu
 * @param pos
 */
void MainWindow::slotStudentTableViewMenu(QPoint pos){
    // 鼠标点击位置索引
    QModelIndex index = ui->student_tableView->indexAt(pos);
    if (index.isValid())
    {
        // 右键数据项有效
        studentPopMenu->exec(QCursor::pos());
    }
}

/**
 * 删除学生点击事件
 * @brief MainWindow::slotDeleteStudent
 */
void MainWindow::slotDeleteStudent()
{
    // 右键的行索引
    int row = ui->student_tableView->currentIndex().row();
    QString id = QString::number(students[row].getId());
    try
    {
        sqlController->deleteStudent(id);
        // 删除成功，刷新学生数据
        updateStudents();
    }
    catch(SQLException e)
    {
        // 删除失败
        QMessageBox::critical(this, "删除失败", e.message());
    }
}

/**
 * 计算学生平均年龄点击事件
 * @brief slotcalStudentAvgAge
 */
void MainWindow::slotcalStudentAvgAge()
{
    int sumAge = 0;
    int avg = 0;
    for (auto it = students.begin(); it != students.end(); it++)
    {
        sumAge += it->getAge();
    }
    avg = sumAge / students.size();
    QMessageBox::information(this, "温馨提示", "学生平均年龄是：" + QString::number(avg));
}

/**
 * 学生表点击事件，如果选中了某个学生就进入对该学生编辑模式
 * @brief MainWindow::on_student_tableView_clicked
 * @param index
 */
void MainWindow::on_student_tableView_clicked(const QModelIndex &index)
{
    if (index.isValid())
    {
        currentIndex = index.row();
        ui->student_saveBtn->setVisible(true);
        ui->student_returnBtn->setVisible(true);
        ui->student_addBtn->setVisible(false);

        Student s = students[currentIndex];
        ui->student_nameEdit->setPlainText(s.getName());
        ui->student_genderComboBox->setCurrentIndex(s.getGender() == "男" ? 0 : 1);
        ui->student_birthDateEdit->setDate(s.getBirth());
        ui->student_majorEdit->setPlainText(s.getMajor());
        ui->student_classNameEdit->setPlainText(s.getClassName());
    }
}

/**
 * 清除学生编辑区域的数据
 * @brief MainWindow::clearStudentEdit
 */
void MainWindow::clearStudentEdit()
{
    ui->student_nameEdit->clear();
    ui->student_genderComboBox->setCurrentIndex(0);
    ui->student_birthDateEdit->setDate(QDate(2001, 1, 1));
    ui->student_majorEdit->clear();
    ui->student_classNameEdit->clear();
}


