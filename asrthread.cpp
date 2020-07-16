#include "asrthread.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <QDebug>
#include <QDir>
#include "mainwindow.h"

AsrThread::AsrThread(QObject* parent) : QObject(parent)
{
}

AsrThread::~AsrThread()
{
}

void AsrThread::start_asr()
{
    qDebug()<<"start asr thread success";
}

void AsrThread::finish_asr()
{
    qDebug()<<"quit asr thread success";
}

void AsrThread::run_asr()
{
    qDebug()<<"run asr thread";
    system("echo  star  >  /home/gec/pipeg");
}

void AsrThread::stop_asr()
{
    //打开管道文件   open
    int fd = ::open("/home/gec/pipe",O_RDWR);
    //读取数据
    char buf[4096]={0};
    ::read(fd,buf,4096);

    QString  msg = buf;

    QString  tmp = msg;
    tmp = tmp.remove(0,tmp.indexOf("<rawtext>"));

    //处理一下服务器返回的数据
    int start_index = tmp.indexOf("<rawtext>");
    tmp = tmp.mid(start_index);
    int end_index = tmp.indexOf("</rawtext>");
    tmp = tmp.mid(9,end_index-9);
    qDebug()<<tmp;
    //关闭
    ::close(fd);
    qDebug()<<"stop asr thread";
    emit getStr(tmp);
}
