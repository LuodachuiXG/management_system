#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "about.h"
#include "QFileDialog"
#include "myexception.cpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1041, 700);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete sqlController;
    delete studentModel;
    delete studentPopMenu;
    delete deleteStudent;
    delete calStudentAvgAge;
    delete exportStudents;
    delete adminTeacherModel;
    delete fullTimeTeacherModel;
    delete teacherPopMenu;
    delete deleteTeacher;
    delete calTeacherAvgAge;
    delete exportTeachers;
    delete searchStudentModel;
    delete searchAdminTeacherModel;
    delete searchFullTimeTeacherModel;
}
/**
 * 初始化数据
 * @brief MainWindow::init
 */
void MainWindow::init()
{
    // 初始化 SQLController
    sqlController = new SQLController;

    /** 设置学生表格项 **/
    studentModel = new QStandardItemModel();
    ui->student_tableView->setModel(studentModel);
    studentModel->setHorizontalHeaderItem(0, new QStandardItem("编号"));
    studentModel->setHorizontalHeaderItem(1, new QStandardItem("姓名"));
    studentModel->setHorizontalHeaderItem(2, new QStandardItem("性别"));
    studentModel->setHorizontalHeaderItem(3, new QStandardItem("出生年月"));
    studentModel->setHorizontalHeaderItem(4, new QStandardItem("年龄"));
    studentModel->setHorizontalHeaderItem(5, new QStandardItem("专业"));
    studentModel->setHorizontalHeaderItem(6, new QStandardItem("班级"));

    // 设置学生表格参数
    ui->student_tableView->setColumnWidth(0, 40);
    ui->student_tableView->setColumnWidth(1, 100);
    ui->student_tableView->setColumnWidth(2, 30);
    ui->student_tableView->setColumnWidth(3, 160);
    ui->student_tableView->setColumnWidth(4, 30);
    ui->student_tableView->setColumnWidth(5, 200);
    ui->student_tableView->setColumnWidth(6, 160);

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
    exportStudents = new QAction("导出学生数据", ui->student_tableView);
    studentPopMenu->addAction(deleteStudent);
    studentPopMenu->addAction(calStudentAvgAge);
    studentPopMenu->addSeparator();
    studentPopMenu->addAction(exportStudents);

    // 设置右键弹出菜单和删除学生、计算平均年龄、导出学生数据槽
    connect(deleteStudent, SIGNAL(triggered()), this, SLOT(slotDeleteStudent()));
    connect(calStudentAvgAge, SIGNAL(triggered()), this, SLOT(slotCalStudentAvgAge()));
    connect(exportStudents, SIGNAL(triggered()), this, SLOT(slotExportStudents()));
    connect(ui->student_tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotStudentTableViewMenu(QPoint)));

    // 初始化学生页面组件数据
    ui->student_genderComboBox->addItems({"男", "女"});
    // 设置学生保存和返回添加按钮默认不显示
    ui->student_saveBtn->setVisible(false);
    ui->student_returnBtn->setVisible(false);

    // 刷新学生数据
    updateStudents();





    /** 设置教师表格项 **/
    // 设置行政人员教师表格项
    adminTeacherModel = new QStandardItemModel();
    adminTeacherModel->setHorizontalHeaderItem(0, new QStandardItem("编号"));
    adminTeacherModel->setHorizontalHeaderItem(1, new QStandardItem("姓名"));
    adminTeacherModel->setHorizontalHeaderItem(2, new QStandardItem("性别"));
    adminTeacherModel->setHorizontalHeaderItem(3, new QStandardItem("出生年月"));
    adminTeacherModel->setHorizontalHeaderItem(4, new QStandardItem("年龄"));
    adminTeacherModel->setHorizontalHeaderItem(5, new QStandardItem("工作时间"));
    adminTeacherModel->setHorizontalHeaderItem(6, new QStandardItem("系部"));
    adminTeacherModel->setHorizontalHeaderItem(7, new QStandardItem("职务信息"));
    // 设置专任教师表格项
    fullTimeTeacherModel = new QStandardItemModel();
    fullTimeTeacherModel->setHorizontalHeaderItem(0, new QStandardItem("编号"));
    fullTimeTeacherModel->setHorizontalHeaderItem(1, new QStandardItem("姓名"));
    fullTimeTeacherModel->setHorizontalHeaderItem(2, new QStandardItem("性别"));
    fullTimeTeacherModel->setHorizontalHeaderItem(3, new QStandardItem("出生年月"));
    fullTimeTeacherModel->setHorizontalHeaderItem(4, new QStandardItem("年龄"));
    fullTimeTeacherModel->setHorizontalHeaderItem(5, new QStandardItem("工作时间"));
    fullTimeTeacherModel->setHorizontalHeaderItem(6, new QStandardItem("系部"));
    fullTimeTeacherModel->setHorizontalHeaderItem(7, new QStandardItem("职称信息"));

    // 设置教师表格参数
    ui->teacher_tableView->setModel(fullTimeTeacherModel);
    ui->teacher_tableView->setColumnWidth(0, 30);
    ui->teacher_tableView->setColumnWidth(1, 90);
    ui->teacher_tableView->setColumnWidth(2, 20);
    ui->teacher_tableView->setColumnWidth(3, 140);
    ui->teacher_tableView->setColumnWidth(4, 20);
    ui->teacher_tableView->setColumnWidth(5, 130);
    ui->teacher_tableView->setColumnWidth(6, 130);
    ui->teacher_tableView->setColumnWidth(7, 130);
    // 只能选择一列，选中整行，不可编辑
    ui->teacher_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->teacher_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->teacher_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 设置教师表格可弹出右键菜单
    ui->teacher_tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    // 新建右键弹出菜单
    teacherPopMenu = new QMenu(ui->teacher_tableView);
    deleteTeacher = new QAction("删除教师", ui->teacher_tableView);
    calTeacherAvgAge = new QAction("计算平均年龄", ui->teacher_tableView);
    exportTeachers = new QAction("导出教师数据", ui->teacher_tableView);
    teacherPopMenu->addAction(deleteTeacher);
    teacherPopMenu->addAction(calTeacherAvgAge);
    teacherPopMenu->addSeparator();
    teacherPopMenu->addAction(exportTeachers);

    // 设置右键弹出菜单和删除教师、计算平均年龄、导出教师数据槽
    connect(deleteTeacher, SIGNAL(triggered()), this, SLOT(slotDeleteTeacher()));
    connect(calTeacherAvgAge, SIGNAL(triggered()), this, SLOT(slotCalTeacherAvgAge()));
    connect(exportTeachers, SIGNAL(triggered()), this, SLOT(slotExportTeachers()));
    connect(ui->teacher_tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotTeacherTableViewMenu(QPoint)));

    // 初始化教师页面组件数据
    ui->teacher_typeComboBox->addItems({"行政人员", "专任教师"});
    ui->teacher_typeComboBoxEdit->addItems({"行政人员", "专任教师"});
    ui->teacher_genderComboBox->addItems({"男", "女"});
    // 设置教师保存和返回添加按钮默认不显示
    ui->teacher_saveBtn->setVisible(false);
    ui->teacher_returnBtn->setVisible(false);

    // 刷新教师数据
    updateTeachers(0);
    updateTeachers(1);






    /** 设置搜索页面组件数据 **/
    // 设置搜索页面学生表格项
    searchStudentModel = new QStandardItemModel();
    searchStudentModel->setHorizontalHeaderItem(0, new QStandardItem("编号"));
    searchStudentModel->setHorizontalHeaderItem(1, new QStandardItem("姓名"));
    searchStudentModel->setHorizontalHeaderItem(2, new QStandardItem("性别"));
    searchStudentModel->setHorizontalHeaderItem(3, new QStandardItem("出生年月"));
    searchStudentModel->setHorizontalHeaderItem(4, new QStandardItem("年龄"));
    searchStudentModel->setHorizontalHeaderItem(5, new QStandardItem("专业"));
    searchStudentModel->setHorizontalHeaderItem(6, new QStandardItem("班级"));

    // 设置搜索页面行政人员教师表格项
    searchAdminTeacherModel = new QStandardItemModel();
    searchAdminTeacherModel->setHorizontalHeaderItem(0, new QStandardItem("编号"));
    searchAdminTeacherModel->setHorizontalHeaderItem(1, new QStandardItem("姓名"));
    searchAdminTeacherModel->setHorizontalHeaderItem(2, new QStandardItem("性别"));
    searchAdminTeacherModel->setHorizontalHeaderItem(3, new QStandardItem("出生年月"));
    searchAdminTeacherModel->setHorizontalHeaderItem(4, new QStandardItem("年龄"));
    searchAdminTeacherModel->setHorizontalHeaderItem(5, new QStandardItem("工作时间"));
    searchAdminTeacherModel->setHorizontalHeaderItem(6, new QStandardItem("系部"));
    searchAdminTeacherModel->setHorizontalHeaderItem(7, new QStandardItem("职务信息"));

    // 设置搜索页面专任教师表格项
    searchFullTimeTeacherModel = new QStandardItemModel();
    searchFullTimeTeacherModel->setHorizontalHeaderItem(0, new QStandardItem("编号"));
    searchFullTimeTeacherModel->setHorizontalHeaderItem(1, new QStandardItem("姓名"));
    searchFullTimeTeacherModel->setHorizontalHeaderItem(2, new QStandardItem("性别"));
    searchFullTimeTeacherModel->setHorizontalHeaderItem(3, new QStandardItem("出生年月"));
    searchFullTimeTeacherModel->setHorizontalHeaderItem(4, new QStandardItem("年龄"));
    searchFullTimeTeacherModel->setHorizontalHeaderItem(5, new QStandardItem("工作时间"));
    searchFullTimeTeacherModel->setHorizontalHeaderItem(6, new QStandardItem("系部"));
    searchFullTimeTeacherModel->setHorizontalHeaderItem(7, new QStandardItem("职称信息"));


    ui->search_groupComboBox->addItems({"学生", "行政人员", "专任教师"});
    // 搜索页面表格只能选择一列，选中整行，不可编辑
    ui->search_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->search_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->search_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 设置搜索表格可弹出右键菜单
    ui->search_tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    // 新建右键弹出菜单
    searchPopMenu = new QMenu(ui->search_tableView);
    searchDelete = new QAction("删除", ui->search_tableView);
    searchCalAvgAge = new QAction("计算平均年龄", ui->search_tableView);
    searchExport = new QAction("导出数据", ui->search_tableView);
    searchPopMenu->addAction(searchDelete);
    searchPopMenu->addAction(searchCalAvgAge);
    searchPopMenu->addSeparator();
    searchPopMenu->addAction(searchExport);

    // 设置右键弹出菜单和删除、计算平均年龄、导出数据槽
    connect(searchDelete, SIGNAL(triggered()), this, SLOT(slotSearchDelete()));
    connect(searchCalAvgAge, SIGNAL(triggered()), this, SLOT(slotSearchCalAvgAge()));
    connect(searchExport, SIGNAL(triggered()), this, SLOT(slotSearchExport()));
    connect(ui->search_tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotSearchTableViewMenu(QPoint)));

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
    int id = students[currentStudentIndex].getId();
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
    Student s = students[row];
    QString id = QString::number(s.getId());
    auto result = QMessageBox::information(this,
                                           "温馨提示", "确定要删除\"" + s.getName() + "\"吗",
                                           QMessageBox::Yes|QMessageBox::No,
                                           QMessageBox::No);
    if (result == QMessageBox::Yes)
    {
        try
        {
            sqlController->deleteStudent(id);
            // 删除成功，刷新学生数据
            updateStudents();
            // 调用返回学生添加按钮点击事件，清除学生编辑数据并且返回添加学生模式
            // 防止删除的是正在编辑的学生，产生 BUG
            on_student_returnBtn_clicked();
        }
        catch(SQLException e)
        {
            // 删除失败
            QMessageBox::critical(this, "删除失败", e.message());
        }
    }
}

/**
 * 计算学生平均年龄点击事件
 * @brief slotcalStudentAvgAge
 */
void MainWindow::slotCalStudentAvgAge()
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
 * 导出学生点击事件槽
 * @brief MainWindow::slotExportStudents
 */
void MainWindow::slotExportStudents()
{
    QString dirPath = QFileDialog::getExistingDirectory(this, "选择导出目录", "./", QFileDialog::ShowDirsOnly);
    if (dirPath.isEmpty())
        return;
    try {
        myio.writeStudents(students, dirPath + "/导出学生数据.txt");
        QMessageBox::information(this, "导出成功", "学生数据已经成功导出到\"" + dirPath + "/导出学生数据.txt\"");
    } catch (IOException e) {
        QMessageBox::critical(this, "导出失败", e.message());
    }
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
        currentStudentIndex = index.row();
        ui->student_saveBtn->setVisible(true);
        ui->student_returnBtn->setVisible(true);
        ui->student_addBtn->setVisible(false);

        Student s = students[currentStudentIndex];
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


/**
 * 教师类别改变事件
 * @brief MainWindow::on_teacher_typeComboBox_currentIndexChanged
 * @param index
 */
void MainWindow::on_teacher_typeComboBox_currentIndexChanged(int index)
{
    if (index == 0)
    {
        // 行政人员教师
        ui->teacher_tableView->setModel(adminTeacherModel);
        updateTeachers(0);
    }
    else {
        // 专任教师
        ui->teacher_tableView->setModel(fullTimeTeacherModel);
        updateTeachers(1);
    }
}


/**
 * 编辑区教师类别改变事件
 * @brief MainWindow::on_teacher_typeComboBoxEdit_currentIndexChanged
 * @param index
 */
void MainWindow::on_teacher_typeComboBoxEdit_currentIndexChanged(int index)
{
    if (index == 0)
    {
        // 行政人员教师
        ui->teacher_typeLabel->setText("职务");
    }
    else {
        // 专任教师
        ui->teacher_typeLabel->setText("职称");
    }
}

/**
 * 添加教师按钮点击事件
 * @brief MainWindow::on_teacher_addBtn_clicked
 */
void MainWindow::on_teacher_addBtn_clicked()
{
    QString name = ui->teacher_nameEdit->toPlainText();
    QString gender = ui->teacher_genderComboBox->currentText();
    QDate birth = ui->teacher_birthDateEdit->date();
    QDate startDate = ui->teacher_startDateEdit->date();
    QString department = ui->teacher_departmentEdit->toPlainText();
    QString type = ui->teacher_typeComboBoxEdit->currentText();
    QString postAndTitle = ui->teacher_postAndTitleEdit->toPlainText();

    if (name.isEmpty() || department.isEmpty() || postAndTitle.isEmpty())
    {
        QMessageBox::information(this, "添加失败", "请将信息填写完整");
        return;
    }
    try
    {
        if (type == "行政人员")
        {
            AdminTeacher at(0, name, gender, birth, startDate, department, postAndTitle);
            sqlController->insertAdminTeacher(at);
            // 添加成功，刷新教师数据
            updateTeachers(0);
        }
        else
        {
            FullTimeTeacher ftt(0, name, gender, birth, startDate, department, postAndTitle);
            sqlController->insertFullTimeTeacher(ftt);
            // 添加成功，刷新教师数据
            updateTeachers(1);
        }

    }
    catch(SQLException e)
    {
        // 添加失败
        QMessageBox::critical(this, "添加失败", e.message());
    }
}

/**
 * 刷新教师数据，0：行政人员，1：专任教师
 * @brief MainWindow::updateStudents
 */
void MainWindow::updateTeachers(int type)
{
    int cout = 0;
    if (type == 0)
    {
        // 行政人员
        adminTeacherModel->removeRows(0, adminTeacherModel->rowCount());
        adminTeachers = sqlController->getAllAdminTeacher();
        for (auto it = adminTeachers.begin(); it != adminTeachers.end(); it++)
        {
            adminTeacherModel->setItem(cout, 0, new QStandardItem(QString::number(it->getId())));
            adminTeacherModel->setItem(cout, 1, new QStandardItem(it->getName()));
            adminTeacherModel->setItem(cout, 2, new QStandardItem(it->getGender()));
            adminTeacherModel->setItem(cout, 3, new QStandardItem(it->getBirth().toString("yyyy年MM月dd日")));
            adminTeacherModel->setItem(cout, 4, new QStandardItem(QString::number(it->getAge())));
            adminTeacherModel->setItem(cout, 5, new QStandardItem(it->getStartDate().toString("yyyy年MM月dd日")));
            adminTeacherModel->setItem(cout, 6, new QStandardItem(it->getDepartment()));
            adminTeacherModel->setItem(cout, 7, new QStandardItem(it->getPost()));
            cout++;
        }
    }
    else
    {
        // 专任教师
        fullTimeTeacherModel->removeRows(0, fullTimeTeacherModel->rowCount());
        fullTimeTeachers = sqlController->getAllFullTimeTeacher();
        for (auto it = fullTimeTeachers.begin(); it != fullTimeTeachers.end(); it++)
        {
            fullTimeTeacherModel->setItem(cout, 0, new QStandardItem(QString::number(it->getId())));
            fullTimeTeacherModel->setItem(cout, 1, new QStandardItem(it->getName()));
            fullTimeTeacherModel->setItem(cout, 2, new QStandardItem(it->getGender()));
            fullTimeTeacherModel->setItem(cout, 3, new QStandardItem(it->getBirth().toString("yyyy年MM月dd日")));
            fullTimeTeacherModel->setItem(cout, 4, new QStandardItem(QString::number(it->getAge())));
            fullTimeTeacherModel->setItem(cout, 5, new QStandardItem(it->getStartDate().toString("yyyy年MM月dd日")));
            fullTimeTeacherModel->setItem(cout, 6, new QStandardItem(it->getDepartment()));
            fullTimeTeacherModel->setItem(cout, 7, new QStandardItem(it->getTitle()));
            cout++;
        }
    }
}

/**
 * 清除教师编辑区域的数据
 * @brief MainWindow::clearStudentEdit
 */
void MainWindow::clearTeacherEdit()
{
    ui->teacher_nameEdit->clear();
    ui->teacher_genderComboBox->setCurrentIndex(0);
    ui->teacher_birthDateEdit->setDate(QDate(2001, 1, 1));
    ui->teacher_startDateEdit->setDate(QDate(2001, 1, 1));
    ui->teacher_departmentEdit->clear();
    ui->teacher_typeComboBoxEdit->setCurrentIndex(0);
    ui->teacher_postAndTitleEdit->clear();
}

/**
 * 教师表格右键弹出菜单事件槽
 * @brief MainWindow::slotTeacherTableViewMenu
 * @param pos
 */
void MainWindow::slotTeacherTableViewMenu(QPoint pos)
{
    // 鼠标点击位置索引
    QModelIndex index = ui->teacher_tableView->indexAt(pos);
    if (index.isValid())
    {
        // 右键数据项有效
        teacherPopMenu->exec(QCursor::pos());
    }
}

/**
 * 删除教师事件槽
 * @brief MainWindow::slotDeleteTeacher
 */
void MainWindow::slotDeleteTeacher()
{
    // 右键的行索引
    int row = ui->teacher_tableView->currentIndex().row();
    int teacherType = ui->teacher_typeComboBox->currentIndex();
    QString id;
    QString name;
    if (teacherType == 0)
    {
        // 行政人员
        AdminTeacher at = adminTeachers[row];
        id = QString::number(at.getId());
        name = at.getName();
    }
    else
    {
        // 专任教师
        FullTimeTeacher ftt = fullTimeTeachers[row];
        id = QString::number(ftt.getId());
        name = ftt.getName();
    }
    auto result = QMessageBox::information(this,
                                           "温馨提示", "确定要删除\"" + name + "\"吗",
                                           QMessageBox::Yes|QMessageBox::No,
                                           QMessageBox::No);
    if (result == QMessageBox::Yes)
    {
        try
        {
            sqlController->deleteTeachert(id);
            // 删除成功，刷新教师数据
            updateTeachers(teacherType);
            // 调用返回教师添加按钮点击事件，清除教师编辑数据并且返回添加教师模式
            // 防止删除的是正在编辑的教师，产生 BUG
            on_teacher_returnBtn_clicked();
        }
        catch(SQLException e)
        {
            // 删除失败
            QMessageBox::critical(this, "删除失败", e.message());
        }
    }
}

/**
 * 计算教师平均年龄事件槽
 * @brief MainWindow::slotcalTeacherAvgAge
 */
void MainWindow::slotCalTeacherAvgAge()
{
    int sumAge = 0;
    int avg = 0;
    int teacherType = ui->teacher_typeComboBox->currentIndex();
    if (teacherType == 0)
    {
        // 行政人员
        for (auto it = adminTeachers.begin(); it != adminTeachers.end(); it++)
        {
            sumAge += it->getAge();
        }
        avg = sumAge / adminTeachers.size();
    }
    else
    {
        // 专任教师
        for (auto it = fullTimeTeachers.begin(); it != fullTimeTeachers.end(); it++)
        {
            sumAge += it->getAge();
        }
        avg = sumAge / fullTimeTeachers.size();
    }
    QMessageBox::information(this, "温馨提示",
                             QString(teacherType == 0 ? "行政人员" : "专任教师") + "平均年龄是：" + QString::number(avg));
}

/**
 * 导出教师数据事件槽
 * @brief MainWindow::slotExportTeachers
 */
void MainWindow::slotExportTeachers()
{
    QString dirPath = QFileDialog::getExistingDirectory(this, "选择导出目录", "./", QFileDialog::ShowDirsOnly);
    if (dirPath.isEmpty())
        return;
    try {
        QString path = dirPath;
        if (ui->teacher_typeComboBox->currentIndex() == 0)
        {
            // 行政人员
            path.append("/导出行政人员数据.txt");
            myio.writeTeacher(adminTeachers, path);
        }
        else
        {
            // 专任教师
            path.append("/导出专任教师数据.txt");
            myio.writeTeacher(fullTimeTeachers, path);
        }
        QMessageBox::information(this, "导出成功", "学生数据已经成功导出到\"" + path + "\"");
    } catch (IOException e) {
        QMessageBox::critical(this, "导出失败", e.message());
    }
}


/**
 * 返回添加教师按钮单击事件
 * @brief MainWindow::on_teacher_returnBtn_clicked
 */
void MainWindow::on_teacher_returnBtn_clicked()
{
    ui->teacher_saveBtn->setVisible(false);
    ui->teacher_returnBtn->setVisible(false);
    ui->teacher_addBtn->setVisible(true);
    // 清除教师信息编辑处的信息
    clearTeacherEdit();
    ui->teacher_tableView->setCurrentIndex(QModelIndex());
}


/**
 * 教师表点击事件，如果选中了某个教师就进入对该教师的编辑模式
 * @brief MainWindow::on_teacher_tableView_clicked
 * @param index
 */
void MainWindow::on_teacher_tableView_clicked(const QModelIndex &index)
{
    int teacherType = ui->teacher_typeComboBox->currentIndex();
    currentTeacherType = teacherType;
    if (index.isValid())
    {
        currentTeacherIndex = index.row();
        ui->teacher_saveBtn->setVisible(true);
        ui->teacher_returnBtn->setVisible(true);
        ui->teacher_addBtn->setVisible(false);

        QString name;
        int genderIndex;
        QDate birth;
        QDate startDate;
        QString department;
        QString postAndTitle;
        if (teacherType == 0)
        {
            // 行政人员
            AdminTeacher at = adminTeachers[currentTeacherIndex];
            name = at.getName();
            genderIndex = at.getGender() == "男" ? 0 : 1;
            birth = at.getBirth();
            startDate = at.getStartDate();
            department = at.getDepartment();
            postAndTitle = at.getPost();
        }
        else
        {
            // 专任教师
            FullTimeTeacher ftt = fullTimeTeachers[currentTeacherIndex];
            name = ftt.getName();
            genderIndex = ftt.getGender() == "男" ? 0 : 1;
            birth = ftt.getBirth();
            startDate = ftt.getStartDate();
            department = ftt.getDepartment();
            postAndTitle = ftt.getTitle();
        }
        ui->teacher_nameEdit->setPlainText(name);
        ui->teacher_genderComboBox->setCurrentIndex(genderIndex);
        ui->teacher_birthDateEdit->setDate(birth);
        ui->teacher_startDateEdit->setDate(startDate);
        ui->teacher_departmentEdit->setPlainText(department);
        ui->teacher_typeComboBoxEdit->setCurrentIndex(teacherType);
        ui->teacher_postAndTitleEdit->setPlainText(postAndTitle);
    }
}

/**
 * 保存教师按钮单击事件
 * @brief MainWindow::on_teacher_saveBtn_clicked
 */
void MainWindow::on_teacher_saveBtn_clicked()
{
    AdminTeacher at;
    FullTimeTeacher ftt;
    QString name = ui->teacher_nameEdit->toPlainText();
    QString gender = ui->teacher_genderComboBox->currentIndex() == 0 ? "男" : "女";
    QDate birth = ui->teacher_birthDateEdit->date();
    QDate startDate = ui->teacher_startDateEdit->date();
    QString department = ui->teacher_departmentEdit->toPlainText();
    QString postAndTitle = ui->teacher_postAndTitleEdit->toPlainText();
    int teacherType = ui->teacher_typeComboBoxEdit->currentIndex();
    if (name.isEmpty() || department.isEmpty() || postAndTitle.isEmpty())
    {
        QMessageBox::information(this, "保存失败", "请将信息填写完整");
        return;
    }

    if (currentTeacherType == 0)
    {
        // 修改的教师之前是行政人员
        at = adminTeachers[currentTeacherIndex];
        at.setName(name);
        at.setGender(gender);
        at.setBirth(birth);
        at.setStartDate(startDate);
        at.setDepartment(department);
        at.setPost(postAndTitle);
    }
    else
    {
        // 修改的教师之前是专任教师
        ftt = fullTimeTeachers[currentTeacherIndex];
        ftt.setName(name);
        ftt.setGender(gender);
        ftt.setBirth(birth);
        ftt.setStartDate(startDate);
        ftt.setDepartment(department);
        ftt.setTitle(postAndTitle);
    }

    try
    {
        // 如果当前选择的教师类型和修改之前的教师类型不一样，就要转换教师类型，相应的这里为 true
        bool convertType = !(currentTeacherType == teacherType);
        if (currentTeacherType == 0)
            sqlController->updateAdminTeacher(at, convertType);
        else
            sqlController->updateFullTimeTeacher(ftt, convertType);
        // 保存成功，刷新教师数据
        updateTeachers(0);
        updateTeachers(1);
        // 调用返回教师添加按钮点击事件
        on_teacher_returnBtn_clicked();
    }
    catch (SQLException e)
    {
        // 保存失败
        QMessageBox::critical(this, "保存失败", e.message());
    }
}

/**
 * 窗口菜单，关于点击事件
 * @brief MainWindow::on_menu_about_triggered
 */
void MainWindow::on_menu_about_triggered()
{
    About a;
    a.exec();
}


/**
 * 窗口菜单，导入学生点击事件
 * @brief MainWindow::on_menu_importStudent_triggered
 */
void MainWindow::on_menu_importStudent_triggered()
{
    QMessageBox::information(this, "温馨提示", "请严格按照如下格式，否则读取失败\n"
                             "张三#男#2001年01月01日#软件工程#21200271\n\n"
                             "姓名#性别#出生年月#专业#班级");
    QString path = QFileDialog::getOpenFileName(this, "选择学生数据文件", "./");
    if (path.isEmpty())
        return;
    vector<Student> students;

    try {
        students = myio.readStudents(path);
    } catch (IOException e) {
        QMessageBox::critical(this, "导入失败", e.message());
        return;
    }

    int count = 0;
    for (int i = 0; i < students.size(); i++)
    {
        try {
            sqlController->insertStudent(students[i]);
            count++;
        } catch (SQLException e) {
            qDebug() << e.message();
        }
    }
    updateStudents();
    QMessageBox::information(this, "温馨提示", "总数据：" +
                             QString::number(students.size()) +
                             "，成功导入：" + QString::number(count));
}

/**
 * 窗口菜单，导入行政人员点击事件
 * @brief MainWindow::on_menu_importAdminTeacher_triggered
 */
void MainWindow::on_menu_importAdminTeacher_triggered()
{
    QMessageBox::information(this, "温馨提示", "请严格按照如下格式，否则读取失败\n"
                             "张三#男#2001年01月01日#2020年08月23日#信息工程学院#院长\n\n"
                             "姓名#性别#出生年月#工作时间#系部#职务");
    QString path = QFileDialog::getOpenFileName(this, "选择行政人员数据文件", "./");
    if (path.isEmpty())
        return;
    vector<AdminTeacher> teachers;

    try {
        teachers = myio.readAdminTeachers(path);
    } catch (IOException e) {
        QMessageBox::critical(this, "导入失败", e.message());
        return;
    }

    int count = 0;
    for (int i = 0; i < teachers.size(); i++)
    {
        try {
            sqlController->insertAdminTeacher(teachers[i]);
            count++;
        } catch (SQLException e) {
            qDebug() << e.message();
        }
    }
    updateTeachers(0);
    QMessageBox::information(this, "温馨提示", "总数据：" +
                             QString::number(teachers.size()) +
                             "，成功导入：" + QString::number(count));
}

/**
 * 导入专任教师点击事件
 * @brief MainWindow::on_menu_importFullTimeTeacher_triggered
 */
void MainWindow::on_menu_importFullTimeTeacher_triggered()
{
    QMessageBox::information(this, "温馨提示", "请严格按照如下格式，否则读取失败\n"
                             "张三#男#2001年01月01日#2020年08月23日#信息工程学院#老师\n\n"
                             "姓名#性别#出生年月#工作时间#系部#职称");
    QString path = QFileDialog::getOpenFileName(this, "选择专任教师数据文件", "./");
    if (path.isEmpty())
        return;
    vector<FullTimeTeacher> teachers;

    try {
        teachers = myio.readFullTimeTeachers(path);
    } catch (IOException e) {
        QMessageBox::critical(this, "导入失败", e.message());
        return;
    }

    int count = 0;
    for (int i = 0; i < teachers.size(); i++)
    {
        try {
            sqlController->insertFullTimeTeacher(teachers[i]);
            count++;
        } catch (SQLException e) {
            qDebug() << e.message();
        }
    }
    updateTeachers(1);
    QMessageBox::information(this, "温馨提示", "总数据：" +
                             QString::number(teachers.size()) +
                             "，成功导入：" + QString::number(count));
}

/**
 * 窗口菜单，退出程序
 * @brief MainWindow::on_menu_exit_triggered
 */
void MainWindow::on_menu_exit_triggered()
{
    qApp->quit();
}

/**
 * 窗口 TabWidget 改变事件
 * @brief MainWindow::on_tabWidget_currentChanged
 * @param index
 */
void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch (index)
    {
    case 0:
        // 学生
        updateStudents();
        break;
    case 1:
        // 教师
        updateTeachers(ui->teacher_typeComboBox->currentIndex());
        break;
    case 2:
        // 查询
        break;
    }
}

/**
 * 搜索页面，群体 ComboBox 选项变更事件
 * @brief MainWindow::on_search_groupComboBox_currentIndexChanged
 * @param index
 */
void MainWindow::on_search_groupComboBox_currentIndexChanged(int index)
{
    ui->search_typeComboBox->clear();
    if (index == 0)
    {
        // 学生
        ui->search_typeComboBox->addItems({"姓名", "专业"});
    }
    else
    {
        // 1 | 2，行政人员 | 专任教师
        ui->search_typeComboBox->addItems({"姓名", "系部"});
    }
}

/**
 * 搜索页面，类型 ComboBox 选项文字变更事件
 * @brief MainWindow::on_search_typeComboBox_currentTextChanged
 * @param arg1
 */
void MainWindow::on_search_typeComboBox_currentTextChanged(const QString &arg1)
{
    QString editStr = "请输入" + ui->search_groupComboBox->currentText() + arg1;
    ui->search_keyEdit->setPlaceholderText(editStr);
    ui->search_keyLabel->setText(arg1);
}

/**
 * 搜索页面，搜索按钮单击事件
 * @brief MainWindow::on_search_searchBtn_clicked
 */
void MainWindow::on_search_searchBtn_clicked()
{
    QString key = ui->search_keyEdit->toPlainText();
    QString group = ui->search_groupComboBox->currentText();
    QString type = ui->search_typeComboBox->currentText();
    searchKey = key;
    searchGroup = group;
    searchType = type;

    if (searchKey.isEmpty())
    {
        QMessageBox::information(this, "温馨提示", "请输入要搜索的关键词");
        return;
    }

    // 更新搜索数据
    updateSearch();
}


/**
 * 更新搜索数据
 * @brief MainWindow::updateSearch
 */
void MainWindow::updateSearch()
{
    if (searchGroup == "学生")
    {
        searchStudentModel->removeRows(0, searchStudentModel->rowCount());
        ui->search_tableView->setModel(searchStudentModel);
        if (searchType == "姓名")
            searchStudents = sqlController->getStudentByName(searchKey);
        else
            searchStudents = sqlController->getStudentByMajor(searchKey);
        int cout = 0;
        for (auto it = searchStudents.begin(); it != searchStudents.end(); it++)
        {
            searchStudentModel->setItem(cout, 0, new QStandardItem(QString::number(it->getId())));
            searchStudentModel->setItem(cout, 1, new QStandardItem(it->getName()));
            searchStudentModel->setItem(cout, 2, new QStandardItem(it->getGender()));
            searchStudentModel->setItem(cout, 3, new QStandardItem(it->getBirth().toString("yyyy年MM月dd日")));
            searchStudentModel->setItem(cout, 4, new QStandardItem(QString::number(it->getAge())));
            searchStudentModel->setItem(cout, 5, new QStandardItem(it->getMajor()));
            searchStudentModel->setItem(cout, 6, new QStandardItem(it->getClassName()));
            cout++;
        }
    }
    else if (searchGroup == "行政人员")
    {
        searchAdminTeacherModel->removeRows(0, searchAdminTeacherModel->rowCount());
        ui->search_tableView->setModel(searchAdminTeacherModel);
        if (searchType == "姓名")
            searchAdminTeachers = sqlController->getAdminTeacherByName(searchKey);
        else
            searchAdminTeachers = sqlController->getAdminTeacherByDepartment(searchKey);
        int cout = 0;
        for (auto it = searchAdminTeachers.begin(); it != searchAdminTeachers.end(); it++)
        {
            searchAdminTeacherModel->setItem(cout, 0, new QStandardItem(QString::number(it->getId())));
            searchAdminTeacherModel->setItem(cout, 1, new QStandardItem(it->getName()));
            searchAdminTeacherModel->setItem(cout, 2, new QStandardItem(it->getGender()));
            searchAdminTeacherModel->setItem(cout, 3, new QStandardItem(it->getBirth().toString("yyyy年MM月dd日")));
            searchAdminTeacherModel->setItem(cout, 4, new QStandardItem(QString::number(it->getAge())));
            searchAdminTeacherModel->setItem(cout, 5, new QStandardItem(it->getStartDate().toString("yyyy年MM月dd日")));
            searchAdminTeacherModel->setItem(cout, 6, new QStandardItem(it->getDepartment()));
            searchAdminTeacherModel->setItem(cout, 7, new QStandardItem(it->getPost()));
            cout++;
        }
    }
    else
    {
        // 专任教师
        searchFullTimeTeacherModel->removeRows(0, searchFullTimeTeacherModel->rowCount());
        ui->search_tableView->setModel(searchFullTimeTeacherModel);
        if (searchType == "姓名")
            searchFullTimeTeachers = sqlController->getFullTimeTeacherByName(searchKey);
        else
            searchFullTimeTeachers = sqlController->getFullTimeTeacherByDepartment(searchKey);
        int cout = 0;
        for (auto it = searchFullTimeTeachers.begin(); it != searchFullTimeTeachers.end(); it++)
        {
                searchFullTimeTeacherModel->setItem(cout, 0, new QStandardItem(QString::number(it->getId())));
                searchFullTimeTeacherModel->setItem(cout, 1, new QStandardItem(it->getName()));
                searchFullTimeTeacherModel->setItem(cout, 2, new QStandardItem(it->getGender()));
                searchFullTimeTeacherModel->setItem(cout, 3, new QStandardItem(it->getBirth().toString("yyyy年MM月dd日")));
                searchFullTimeTeacherModel->setItem(cout, 4, new QStandardItem(QString::number(it->getAge())));
                searchFullTimeTeacherModel->setItem(cout, 5, new QStandardItem(it->getStartDate().toString("yyyy年MM月dd日")));
                searchFullTimeTeacherModel->setItem(cout, 6, new QStandardItem(it->getDepartment()));
                searchFullTimeTeacherModel->setItem(cout, 7, new QStandardItem(it->getTitle()));
                cout++;
        }
    }

    if (searchGroup == "学生")
    {
        // 设置表格参数
        ui->search_tableView->setColumnWidth(0, 40);
        ui->search_tableView->setColumnWidth(1, 100);
        ui->search_tableView->setColumnWidth(2, 30);
        ui->search_tableView->setColumnWidth(3, 160);
        ui->search_tableView->setColumnWidth(4, 30);
        ui->search_tableView->setColumnWidth(5, 200);
        ui->search_tableView->setColumnWidth(6, 160);
    }
    else
    {
        // 行政人员 | 专任教师
        ui->search_tableView->setColumnWidth(0, 30);
        ui->search_tableView->setColumnWidth(1, 90);
        ui->search_tableView->setColumnWidth(2, 20);
        ui->search_tableView->setColumnWidth(3, 140);
        ui->search_tableView->setColumnWidth(4, 20);
        ui->search_tableView->setColumnWidth(5, 130);
        ui->search_tableView->setColumnWidth(6, 130);
        ui->search_tableView->setColumnWidth(7, 130);
    }
}

/**
 * 搜索表格右键弹出菜单事件
 * @brief MainWindow::slotSearchTableViewMenu
 * @param pos
 */
void MainWindow::slotSearchTableViewMenu(QPoint pos)
{
    // 鼠标点击位置索引
    QModelIndex index = ui->search_tableView->indexAt(pos);
    if (index.isValid())
    {
        // 右键数据项有效
        searchPopMenu->exec(QCursor::pos());
    }
}

/**
 * 搜索页面删除事件槽
 * @brief MainWindow::slotSearchDelete
 */
void MainWindow::slotSearchDelete()
{
    // 右键的行索引
    int row = ui->search_tableView->currentIndex().row();
    QString group = ui->search_groupComboBox->currentText();
    QString id;
    QString name;

    if (group == "行政人员")
    {
        // 行政人员
        AdminTeacher at = searchAdminTeachers[row];
        id = QString::number(at.getId());
        name = at.getName();
    }
    else if (group == "专任教师")
    {
        // 专任教师
        FullTimeTeacher ftt = searchFullTimeTeachers[row];
        id = QString::number(ftt.getId());
        name = ftt.getName();
    }
    else if (group == "学生")
    {
        // 学生
        Student student = searchStudents[row];
        id = QString::number(student.getId());
        name = student.getName();
    }

    auto result = QMessageBox::information(this,
                                           "温馨提示", "确定要删除\"" + name + "\"吗",
                                           QMessageBox::Yes|QMessageBox::No,
                                           QMessageBox::No);
    if (result == QMessageBox::Yes)
    {
        try
        {
            if (group == "行政人员" || group == "专任教师")
            {
                sqlController->deleteTeachert(id);
            }
            else if (group == "学生")
            {
                sqlController->deleteStudent(id);
            }
            // 删除成功，更新数据
            updateSearch();
        }
        catch(SQLException e)
        {
            // 删除失败
            QMessageBox::critical(this, "删除失败", e.message());
        }
    }
}
// 搜索页面计算平均年龄槽
void MainWindow::slotSearchCalAvgAge()
{
    int sumAge = 0;
    int avg = 0;
    if (searchGroup == "学生")
    {
        for (auto it = searchStudents.begin(); it != searchStudents.end(); it++)
        {
            sumAge += it->getAge();
        }
        avg = sumAge / searchStudents.size();
    }
    else if (searchGroup == "行政人员")
    {
        for (auto it = searchAdminTeachers.begin(); it != searchAdminTeachers.end(); it++)
        {
            sumAge += it->getAge();
        }
        avg = sumAge / searchAdminTeachers.size();
    }
    else if (searchGroup == "专任教师")
    {
        for (auto it = searchFullTimeTeachers.begin(); it != searchFullTimeTeachers.end(); it++)
        {
            sumAge += it->getAge();
        }
        avg = sumAge / searchFullTimeTeachers.size();
    }
    QMessageBox::information(this, "温馨提示", "平均年龄是：" + QString::number(avg));
}

// 搜索页面导出数据槽
void MainWindow::slotSearchExport()
{
    QString dirPath = QFileDialog::getExistingDirectory(this, "选择导出目录", "./", QFileDialog::ShowDirsOnly);
    if (dirPath.isEmpty())
        return;
    try {
        if (searchGroup == "学生")
        {
            dirPath.append("/导出学生搜索数据.txt");
            myio.writeStudents(searchStudents, dirPath);
        }
        else if (searchGroup == "行政人员")
        {
            dirPath.append("/导出行政人员搜索数据.txt");
            myio.writeTeacher(searchAdminTeachers, dirPath);
        }
        else if (searchGroup == "专任教师")
        {
            dirPath.append("/导出专任教师搜索数据.txt");
            myio.writeTeacher(searchFullTimeTeachers, dirPath);
        }
        QMessageBox::information(this, "导出成功", "数据已经成功导出到\"" + dirPath);
    } catch (IOException e) {
        QMessageBox::critical(this, "导出失败", e.message());
    }
}
