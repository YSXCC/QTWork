#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    this->move(500,200);
    QPalette PAllbackground = this->palette();
    QImage ImgAllbackground(":/other/resource/other/login.jpg");

    QImage fitimgpic=ImgAllbackground.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
    this->setPalette(PAllbackground);

    ui->input_user->setPlaceholderText("请输入用户名！");
    ui->input_pwd->setPlaceholderText("请输入密码！");
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_bt_login_clicked()
{
    //获取字符串
    QString str_user = ui->input_user->text();
    QString str_pwd  = ui->input_pwd->text();

    if(str_user == "12345" && str_pwd == "12345"){
        QMessageBox::information(NULL, "登录成功", "跳转", QMessageBox::Yes, QMessageBox::Yes);
        MainWindow *main_window = new MainWindow(this);
        main_window->show();
        this->hide();
    }else{
        QMessageBox::warning(NULL, "登录失败", "确定", QMessageBox::Yes, QMessageBox::Yes);
    }
}

void LoginWindow::on_bt_exit_clicked()
{
    QApplication::exit();
}

