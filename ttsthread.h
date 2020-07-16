#ifndef TTSTHREAD_H
#define TTSTHREAD_H

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <QDebug>
#include <QDir>
#include <QObject>
#include <QString>

class TtsThread: public QObject
{
    Q_OBJECT
public:
    TtsThread(QObject* parent = nullptr);
    ~TtsThread();

public slots:
    void start_tts();
    void finish_tts();

    void run_tts(QString voice_info);

signals:
    void ttsStart();
    void ttsFinished();
};

#endif // TTSTHREAD_H
