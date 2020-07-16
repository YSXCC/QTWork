#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QPushButton>

//Layout
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

#include <QLineEdit>  //单行输入框

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:  //slot function
    //返回主界面
    void Back_Main_Window();
    //获取输入符号
    void Get_Input_Char();

private:
    Ui::Calculator *ui;

    QLineEdit *lineEdit;
    QVBoxLayout *vbox;
    QGridLayout *grid;
    //计算按钮
    QPushButton *buttons;
    //返回按钮
    QPushButton *back_button;

    //设置第一次和第二次数据的保存
    QString frist_num;
    QString second_num;

    //创建一个判断函数
    void Input_Num(QString ch);
    void Input_Type(QString ch);
    void OutPut();

    //创建一个标志位(作用是判断是第一次输入还是第二次输入)
    int input_flag = 0;
};
#endif // CALCULATOR_H
