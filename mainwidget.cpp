#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "QMessageBox"
#include "mainwindow.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    ui->username_edit->setText("admin");
    ui->password_edit->setText("123456");
    ui->password_edit->setFocus();
    setFixedSize(450, 300);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_login_btn_clicked()
{
    QString username = ui->username_edit->toPlainText();
    QString password = ui->password_edit->text();
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::information(this, "温馨提示", "请将内容输入完整", "确定");
        return;
    }
    if (username == "admin" && password == "123456")
    {
        MainWindow *mw = new MainWindow();
        mw->show();
        this->close();
    }
    else
    {
        QMessageBox::critical(this, "温馨提示", "账号或密码错误", "确定");
        return;
    }
}
