#include "playvideowindow.h"
#include "ui_playvideowindow.h"
#include <QDebug>

PlayVideoWindow::PlayVideoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayVideoWindow)
{
    ui->setupUi(this);
    this->move(600,100);
    connect(&mprocess,SIGNAL(finished(int)),this,SLOT(play_next(int)));
}

PlayVideoWindow::~PlayVideoWindow()
{
    delete ui;
}

//打开
void PlayVideoWindow::on_bt1_clicked()
{
    //通过文件对话框添加播放文件
    QStringList movies  = QFileDialog::getOpenFileNames(this,"选择视频","/mnt/hgfs/WORK");

    //把视频路径添加列表中
    ui->listWidget->addItems(movies);

}
//关闭
void PlayVideoWindow::on_bt2_clicked()
{
    //杀死进程
    mprocess.kill();
    //确定死透
    mprocess.waitForFinished();

}


void PlayVideoWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //检测到有进程在运行直接kill
    if(mprocess.state()  == QProcess::Running)
    {

        //杀死进程
        mprocess.kill();
        //确定死透
        mprocess.waitForFinished();

    }

    //在次获取视频路径
    QString moviesName = item->text();
    qDebug()<<moviesName;

    QStringList arguments;
    arguments<<"-slave"<<"-quiet"<<"-wid"<<QString::number(ui->label->winId())<< "-noaspect" <<moviesName;

    //启动进程
    mprocess.start("mplayer", arguments);


}

void PlayVideoWindow::play_next(int num)
{
    qDebug()<<QString::number(num);

}

void PlayVideoWindow::on_bt_return_clicked()
{
    //检测到有进程在运行直接kill
    if(mprocess.state()  == QProcess::Running)
    {

        //杀死进程
        mprocess.kill();
        //确定死透
        mprocess.waitForFinished();

    }
    //返回登录界面
    this->parentWidget()->show();
    //删除
    delete this;
}
