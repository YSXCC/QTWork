#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QDebug>
#include <QString>
#include <QDialog>
#include <QPushButton>

#include <QProcess>
#include <QThread>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QByteArray>

#include "asrthread.h"
#include "ttsthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_bt_cal_clicked();

    void on_bt_exit_clicked();

    void on_bt_dialog_clicked();

    void on_bt_video_clicked();

    void on_bt_weather_clicked();

    void asr_out();

    void on_bt_say_pressed();

    void on_bt_say_released();

    void do_something(QString str);

    void chat_with_robot(QString info);

    void read_net_data(QNetworkReply *app);

signals:
    void get_str();

    void chat(QString info);

    void tts_Run(QString voice_info);

private:
    Ui::MainWindow *ui;

    QProcess asr_process;

    QThread *main_asrThread;

    QThread *main_ttsThread;

    AsrThread *asr_thread;

    TtsThread *tts_thread;

    //创建管理类对象
    QNetworkAccessManager manager;
};

#endif // MAINWINDOW_H
