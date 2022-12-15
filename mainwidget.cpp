#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "QMessageBox"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
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
    }
}
