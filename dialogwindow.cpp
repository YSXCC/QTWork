#include "dialogwindow.h"
#include "ui_dialogwindow.h"

DialogWindow::DialogWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DialogWindow)
{
    ui->setupUi(this);
    this->move(600,100);
}

DialogWindow::~DialogWindow()
{
    delete ui;
}
//消息对话框
void DialogWindow::on_boxBt_clicked()
{
    //调用信息对话框类
    //question   information
    int set = QMessageBox::question(this, "操作提示", "确定要退出？", QMessageBox::Yes, QMessageBox::No);
    if (set == QMessageBox::Yes)
    {
        qDebug() << set;
    }
    else
    {
        qDebug() << set;
    }
}
//文本对话框 (获取文件的路径)
void DialogWindow::on_fileBt_clicked()
{
    //调用文本对话框类  (返回的字符串是打开的文件的路径)
    QString file = QFileDialog::getOpenFileName(this, "选择源文件", "/");
    qDebug() << file;
    //返回的字符串显示在单行输入框
    ui->lineEdit->setText(file);
}
//set-> 组件设置    add-> 布局设置   get->对话框设置
//颜色对话框
void DialogWindow::on_colorBt_clicked()
{
//    QApplication::setQuitOnLastWindowClosed(false);
    QColorDialog color_dialog(this);
    //调用颜色对话框类
    QColor color = color_dialog.getColor(QColor(255,255,255),this);
    //获取字符串
    QString rgb = QString("background-color:%1").arg(color.name());
    qDebug() << rgb;
    //让颜色对话框返回的颜色显示在label
    ui->label->setStyleSheet(rgb);
}
//字体对话框
void DialogWindow::on_fontBt_clicked()
{
    bool ok = false;
    //调用字体对话框类
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok)
    {
        ui->label->setFont(font);
    }
}
//输入对话框
void DialogWindow::on_inputBt_clicked()
{
    //调用输入对话框类
    QString text = QInputDialog::getText(this, "输入你想插入的内容", "请输入！", QLineEdit::Password);

    qDebug() << text;
    //将获取到的text显示label
    ui->label->setText(text);
}
//自定义对话框
void DialogWindow::on_selfBt_clicked()
{
    //自定义的步骤如下
    QDialog dialog(this);                             //先创建框的对象
    dialog.setWindowTitle("自定义的对话框2.0"); //设置标题
    dialog.resize(200, 100);                    //设置框的大小
    //添加组件 (先创建)
    QPushButton yesbt("Yes", &dialog);
    yesbt.setGeometry(0, 40, 100, 40);
    QPushButton nobt("NO", &dialog);
    nobt.setGeometry(100, 40, 100, 40);
    //创建信号与槽
    connect(&yesbt, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(&nobt, &QPushButton::clicked, &dialog, &QDialog::reject);
    //显示窗体
    int ret = dialog.exec();
    if (ret == QDialog::Accepted)
    {
        qDebug() << "YES";
    }
    if (ret == QDialog::Rejected)
    {
        qDebug() << "NO";
    }
}

void DialogWindow::on_bt_return_clicked()
{
    //返回登录界面
    this->parentWidget()->show();
    //删除
    delete this;
}
