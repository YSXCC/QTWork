#include "ttsthread.h"
#include <QProcess>

TtsThread::TtsThread(QObject* parent) : QObject(parent)
{
}

TtsThread::~TtsThread()
{
}

void TtsThread::start_tts()
{
    qDebug()<<"start tts thread success";
}

void TtsThread::finish_tts()
{
    qDebug()<<"quit tts thread success";
}

void TtsThread::run_tts(QString voice_info)
{
    QDir::setCurrent("/mnt/hgfs/WORK/Compound/bin");
    QString cmd = "./tts_offline_sample \"" + voice_info +"\"";
    system(cmd.toUtf8().data());
    system("aplay tts_sample.wav &");
    qDebug()<<voice_info;
}
