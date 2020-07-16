#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    //创建垂直布局
    this->vbox = new QVBoxLayout(ui->centralwidget);
    //创建单行输入框对象
    this->lineEdit = new QLineEdit();
    //设置一下单行输入框的属性
    this->lineEdit->setMinimumHeight(60);
    //设置单行输入框显示方向  (右边显示)
    this->lineEdit->setAlignment(Qt::AlignRight);
    //把标签插入到垂直布局里面
    this->vbox->addWidget(lineEdit);
    //创建栅栏布局
    this->grid = new QGridLayout();
    //创建按钮对象
    this->buttons = new QPushButton[16];

    //创建一个字符串
    QString sty = "789/456*123-=0.+";
    //把按钮加入到栅栏布局里面
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            QFont ft;
            ft.setPixelSize(15);
            //设置按钮大小
            buttons[i*4+j].setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
            buttons[i*4+j].setFont(ft);
            grid->addWidget(buttons+i*4+j,i,j);
            //设置按钮数字键
            buttons[i*4+j].setText(sty.at(i*4+j));
            //创建每一个按钮信号和槽(输入的字符)
            connect(buttons+i*4+j,&QPushButton::clicked,this,&Calculator::Get_Input_Char);
        }

    }
    //把栅栏布局插入到垂直布局
    this->vbox->addLayout(grid);
    //创建返回按钮
    this->back_button = new QPushButton("返回上界面");
    //把返回按钮插入到垂直布局
    this->vbox->addWidget(back_button);

    connect(back_button,&QPushButton::clicked,this,&Calculator::Back_Main_Window);

    this->setMaximumWidth(350);
    this->setMaximumHeight(500);
    this->move(700,100);
}

Calculator::~Calculator()
{
    delete ui;
    delete back_button;
    delete []this->buttons;
    delete grid;
    delete lineEdit;
    delete vbox;
}

//槽函数,返回主界面
void Calculator::Back_Main_Window()
{
    //返回登录界面
    this->parentWidget()->show();
    //删除
    delete this;
}

//槽函数,获取按键的字符，并进行判断
void Calculator::Get_Input_Char()
{
     //获取信号的发送者
     QPushButton *bt = static_cast<QPushButton *>(sender());
     //获取按钮信息
     QString ch = bt->text();
     //对获取的数据进行判断
     if(QString("0123456789.").indexOf(ch) >= 0)
     {
         qDebug()<<"输入的数字是："<<ch;
         Input_Num(ch);
     }
     else if(QString("+-/*").indexOf(ch) >=0)
     {
         qDebug()<<"输入的符号是："<<ch;
         Input_Type(ch);
     }
     else
     {
         qDebug()<<"输入的数字是："<<ch;
         OutPut();
     }

}

//对数字进行处理
void Calculator::Input_Num(QString ch)
{
    //标志位
    if(input_flag == 0) //第一次输入
    {
        //设置字符追加  (第一次输入的数)
        frist_num.append(ch);
        //打印一下数据
        qDebug()<<frist_num;
        //显示一下输入的字符串
        lineEdit->setText(frist_num);
    }
    else
    {
        //（第二次输入的数）
        second_num.append(ch);
        qDebug()<<second_num;
        //显示一下输入的字符串
        lineEdit->setText(second_num);
    }
}

//对符号的处理
void Calculator::Input_Type(QString ch)
{
    //对符号进行判断
    switch (ch.at(0).toLatin1())
    {
        case '+':  input_flag=1; break;
        case '-':  input_flag=2; break;
        case '*':  input_flag=3; break;
        case '/':  input_flag=4; break;
        default:break;
    }
}

//等于号操作
void Calculator::OutPut()
{
    QString srt;
    //先对calc进行判断
    switch (input_flag)
    {
        case 1 : srt=QString(frist_num+"+"+second_num+"="+QString::number(frist_num.toDouble()+second_num.toDouble())); break;
        case 2 : srt=QString(frist_num+"-"+second_num+"="+QString::number(frist_num.toDouble()-second_num.toDouble())); break;
        case 3 : srt=QString(frist_num+"*"+second_num+"="+QString::number(frist_num.toDouble()*second_num.toDouble())); break;
        case 4 : srt=QString(frist_num+"/"+second_num+"="+QString::number(frist_num.toDouble()/second_num.toDouble())); break;
       default:break;
    }

    qDebug()<<srt;
    //显示在单行输入框
    lineEdit->setText(srt);
    //把input_flag变回0
    input_flag = 0;
    //清空保存的上一次数据的字符串
    frist_num.clear();
    second_num.clear();

}
