#ifndef ASRTHREAD_H
#define ASRTHREAD_H

#include <QObject>
#include <QString>

class AsrThread : public QObject
{
    Q_OBJECT
public:
    AsrThread(QObject* parent = nullptr);
    ~AsrThread();

public slots:
    void start_asr();
    void finish_asr();

    void run_asr();
    void stop_asr();

signals:
    void asrStart();
    void asrFinished();

    void asrRun();
    void asrStop();

    void getStr(QString str);
};

#endif // ASRTHREAD_H
