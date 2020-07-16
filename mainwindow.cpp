#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculator.h"
#include "dialogwindow.h"
#include "playvideowindow.h"
#include "weatherwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->move(600,100);
    connect(this,SIGNAL(chat(QString)),this,SLOT(chat_with_robot(QString)));
    //开启语音识别的进程
    connect(&asr_process,SIGNAL(finished(int)),this,SLOT(asr_out(void)));
    QDir::setCurrent("/mnt/hgfs/WORK/Compound/bin");
    asr_process.start("asr_offline_sample");

    //新建语音合成线程
    main_ttsThread = new QThread();
    tts_thread = new TtsThread();
    tts_thread->moveToThread(main_ttsThread);

    //启动和释放线程
    connect(main_ttsThread, &QThread::started, tts_thread, &TtsThread::start_tts);
    connect(tts_thread, &TtsThread::ttsFinished, tts_thread, &TtsThread::finish_tts);

    connect(tts_thread, &TtsThread::ttsFinished, main_ttsThread, &QThread::quit);
    connect(main_ttsThread, &QThread::finished, main_ttsThread, &QThread::deleteLater);

    connect(this, SIGNAL(tts_Run(QString)), tts_thread, SLOT(run_tts(QString)));

    main_ttsThread->start();
    //新建录入语音线程
    main_asrThread = new QThread();
    asr_thread = new AsrThread();
    asr_thread->moveToThread(main_asrThread);

    //启动和释放线程
    connect(main_asrThread, &QThread::started, asr_thread, &AsrThread::start_asr);
    connect(asr_thread, &AsrThread::asrFinished, asr_thread, &AsrThread::finish_asr);

    connect(asr_thread, &AsrThread::asrFinished, main_asrThread, &QThread::quit);
    connect(main_asrThread, &QThread::finished, main_asrThread, &QThread::deleteLater);

    //主线程和次线程传递信息
    connect(asr_thread, SIGNAL(getStr(QString)), this, SLOT(do_something(QString)),Qt::QueuedConnection);

    //运行和暂停语音识别
    connect(asr_thread, &AsrThread::asrRun, asr_thread, &AsrThread::run_asr);
    connect(asr_thread, &AsrThread::asrStop, asr_thread, &AsrThread::stop_asr);

    //机器人聊天，网络请求
    connect(&manager,&QNetworkAccessManager::finished,this,&MainWindow::read_net_data);

    main_asrThread->start();

}

MainWindow::~MainWindow()
{
    emit asr_thread->asrFinished();
    asr_process.kill();
    asr_process.waitForFinished();
    delete ui;
}

void MainWindow::on_bt_cal_clicked()
{
    Calculator *cal_window = new Calculator(this);
    cal_window->show();
    this->hide();
}

void MainWindow::on_bt_exit_clicked()
{
    emit asr_thread->asrFinished();
    //返回登录界面
    this->parentWidget()->show();
    //删除
    delete this;
}

void MainWindow::on_bt_dialog_clicked()
{
    DialogWindow *dialog_window = new DialogWindow(this);
    dialog_window->show();
    this->hide();
}

void MainWindow::on_bt_video_clicked()
{
    PlayVideoWindow *play_video_window = new PlayVideoWindow(this);
    play_video_window->show();
    this->hide();
}

void MainWindow::on_bt_weather_clicked()
{
    WeatherWindow *weather_window = new WeatherWindow(this);
    weather_window->show();
    this->hide();
}

void MainWindow::asr_out()
{
    qDebug()<<"语音识别进程结束"<<endl;
}


void MainWindow::on_bt_say_pressed()
{
    ui->bt_say->setText("松开结束");
    emit asr_thread->asrRun();
}

void MainWindow::on_bt_say_released()
{
    ui->bt_say->setText("按压说话");
    emit asr_thread->asrStop();
}

void MainWindow::chat_with_robot(QString info)
{
    QString str_url = "http://api.qingyunke.com/api.php?key=free&appid=0&msg=";
    QUrl url(str_url + info);
    //创建请求
    QNetworkRequest request(url);
    //发射
    manager.get(request);
}

void MainWindow::read_net_data(QNetworkReply *app)
{
    //对数据进行读取
    QByteArray array = app->readAll();
    //判断是否为json数据
    QJsonParseError error;
    //对json数据进解析
    QJsonDocument doc = QJsonDocument::fromJson(array, &error);

    if (error.error != QJsonParseError::NoError)
    {
        qDebug() << "数据有误";
        return;
    }
    //一层一层解剖
    QJsonObject obj = doc.object();
    QString name_obj = obj.value("content").toString();
    emit this->tts_Run(name_obj);
    qDebug() << "哈哈哈哈";
}

void MainWindow::do_something(QString str){
    qDebug()<<str;
    if(str == "打开天气"){
        ui->bt_weather->clicked();
    }else if(str == "打开计算器"){
        ui->bt_cal->clicked();
    }else if(str == "播放视频"){
        ui->bt_video->clicked();
    }else if(str == "打开秒表"){
        ui->bt_cal->clicked();
    }else{
        emit MainWindow::chat(str);
    }

}

