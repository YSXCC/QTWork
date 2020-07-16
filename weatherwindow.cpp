#include "weatherwindow.h"
#include "ui_weatherwindow.h"
#include <QtDebug>
#include <QSslSocket>

WeatherWindow::WeatherWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WeatherWindow)
{
    ui->setupUi(this);
    this->move(400,50);
    WeatherWindow::dateTimeTimer();
    timer_date_and_time = new QTimer();
    connect(timer_date_and_time, SIGNAL(timeout()), this, SLOT(dateTimeTimer()));
    timer_date_and_time->start(1000);

    connect(&manager_city_id,&QNetworkAccessManager::finished,this,&WeatherWindow::parseCityId);
    connect(&manager_now_weather,&QNetworkAccessManager::finished,this,&WeatherWindow::parseNowWeather);
    connect(&manager_future_weather,&QNetworkAccessManager::finished,this,&WeatherWindow::parseFutureWeather);

    label_date[0] = ui->lbl_future_1_date;
    label_date[1] = ui->lbl_future_2_date;
    label_date[2] = ui->lbl_future_3_date;
    label_date[3] = ui->lbl_future_4_date;
    label_date[4] = ui->lbl_future_5_date;
    label_date[5] = ui->lbl_future_6_date;

    label_icon[0] = ui->lbl_future_1_img;
    label_icon[1] = ui->lbl_future_2_img;
    label_icon[2] = ui->lbl_future_3_img;
    label_icon[3] = ui->lbl_future_4_img;
    label_icon[4] = ui->lbl_future_5_img;
    label_icon[5] = ui->lbl_future_6_img;

    label_weather[0] = ui->lbl_future_1_weather;
    label_weather[1] = ui->lbl_future_2_weather;
    label_weather[2] = ui->lbl_future_3_weather;
    label_weather[3] = ui->lbl_future_4_weather;
    label_weather[4] = ui->lbl_future_5_weather;
    label_weather[5] = ui->lbl_future_6_weather;

    label_temp[0] = ui->lbl_future_1_temp;
    label_temp[1] = ui->lbl_future_2_temp;
    label_temp[2] = ui->lbl_future_3_temp;
    label_temp[3] = ui->lbl_future_4_temp;
    label_temp[4] = ui->lbl_future_5_temp;
    label_temp[5] = ui->lbl_future_6_temp;

}

WeatherWindow::~WeatherWindow()
{
    delete timer_date_and_time;
    delete ui;
}

//时间日期定时器槽函数
void WeatherWindow::dateTimeTimer()
{
    QTime qtimeObj = QTime::currentTime();
    QString strTime = qtimeObj.toString("hh:mm:ss ap");
    strTime.prepend("  Time is: ");
    QDate qdateObj = QDate::currentDate();
    QString strDate = qdateObj.toString("yyyy,MMMM,dd");//年、月、日、星期
    strDate.prepend("Today is: ");

    ui->lbl_date->setText(strDate);
    ui->lbl_time->setText(strTime);
}

//点击按钮查询城市代码
void WeatherWindow::on_bt_search_clicked()
{
    QString location = ui->edit_city_name->text();
    QString str_url = this->api_url_cityId+location;
    QUrl url(str_url);
    QNetworkRequest request(url);
    manager_city_id.get(request);
}

//处理json数据，获取城市ID,并调用天气接口显示
void WeatherWindow::parseCityId(QNetworkReply *app)
{
    //对数据进行读取
    QByteArray array = app->readAll();
    //判断是否为json数据
    QJsonParseError error;
    //对json数据进解析
    QJsonDocument doc  = QJsonDocument::fromJson(array,&error);

    if(error.error != QJsonParseError::NoError)
    {
        qDebug()<<"数据有误";
        return;
    }
    QJsonObject root_obj = doc.object();
    QJsonValue location = root_obj.value("location");

    QJsonObject location_obj = location.toArray().at(0).toObject();
    QString city_id = location_obj.value("id").toString();
    qDebug()<<city_id;
    getNowWeather(city_id);
    getFutureWeather(city_id);
}

void WeatherWindow::getNowWeather(QString city_id)
{
    QString str_url = this->api_url_now+city_id;
    QUrl url(str_url);
    QNetworkRequest request(url);
    manager_now_weather.get(request);
}

//请求未来天气json
void WeatherWindow::getFutureWeather(QString city_id)
{
    QString str_url = this->api_url_7d+city_id;
    QUrl url(str_url);
    QNetworkRequest request(url);
    manager_future_weather.get(request);
}

//请求现在天气json
void WeatherWindow::parseNowWeather(QNetworkReply *app)
{
    //对数据进行读取
    QByteArray array = app->readAll();
    //判断是否为json数据
    QJsonParseError error;
    //对json数据进解析
    QJsonDocument doc  = QJsonDocument::fromJson(array,&error);

    if(error.error != QJsonParseError::NoError)
    {
        qDebug()<<"数据有误";
        return;
    }
    QJsonObject root_obj = doc.object();
    QJsonValue now = root_obj.value("now");

    QJsonObject now_obj = now.toObject();
    QString temp = now_obj.value("temp").toString();
    QString now_weather = now_obj.value("text").toString();
    QString now_temp = now_obj.value("temp").toString();
    QString now_humidity = now_obj.value("humidity").toString();
    QString now_precip = now_obj.value("precip").toString();
    QString now_icon = now_obj.value("icon").toString();
    QString now_feelsLike = now_obj.value("feelsLike").toString();
    QString now_windDir = now_obj.value("windDir").toString();
    QString now_windSpeed = now_obj.value("windSpeed").toString();
    QString now_pressure = now_obj.value("pressure").toString();
    QString now_vis = now_obj.value("vis").toString();
    QString now_cloud = now_obj.value("cloud").toString();

    if(temp != ""){
        ui->lbl_now_weather->setText(now_weather);
    }else{
        ui->lbl_now_weather->setText("没有查询到");
    }
    if(now_icon != ""){
        ui->lbl_now_img_weather->setStyleSheet(QString("image: url(:/weather/resource/weather/%1.png/)").arg(now_icon));
    }else{
        ui->lbl_now_img_weather->setStyleSheet("image: url(:/weather/resource/weather/999.png/)");
    }
    ui->lbl_now_temp->setText(QString("%1℃").arg(now_temp));
    ui->lbl_now_humidity->setText(QString("(实时)湿度：%1").arg(now_humidity));
    ui->lbl_now_precip->setText(QString("(实时)降水：%1").arg(now_precip));
    ui->lbl_now_feelslike->setText(QString("体感温度：%1℃").arg(now_feelsLike));
    ui->lbl_now_winddir->setText(QString("风向：%1").arg(now_windDir));
    ui->lbl_now_windspeed->setText(QString("风速：%1 公里/小时").arg(now_windSpeed));
    ui->lbl_now_pressure->setText(QString("大气压强：%1").arg(now_pressure));
    ui->lbl_now_vis->setText(QString("能见度：%1 公里").arg(now_vis));
    ui->lbl_now_cloud->setText(QString("云量：%1").arg(now_cloud));
}

//请求未来天气json
void WeatherWindow::parseFutureWeather(QNetworkReply *app)
{
    //对数据进行读取
    QByteArray array = app->readAll();
    //判断是否为json数据
    QJsonParseError error;
    //对json数据进解析
    QJsonDocument doc  = QJsonDocument::fromJson(array,&error);

    if(error.error != QJsonParseError::NoError)
    {
        qDebug()<<"数据有误";
        return;
    }
    QJsonObject root_obj = doc.object();
    QJsonValue future = root_obj.value("daily");
    QList<DayWeather>* future_weather = new QList<DayWeather>;
    for (int i = 0 ; i < 7; i++) {
        DayWeather *dayweather = new DayWeather();
        QJsonObject daily_obj = future.toArray().at(i).toObject();
        QString date = daily_obj.value("fxDate").toString();
        QString icon = daily_obj.value("iconDay").toString();
        QString weather = daily_obj.value("textDay").toString();
        QString temp_max = daily_obj.value("tempMax").toString();
        QString temp_min = daily_obj.value("tempMin").toString();
        dayweather->setDate(date);
        dayweather->setIcon(icon);
        dayweather->setWeatherText(weather);
        dayweather->setTemp(temp_min,temp_max);
        future_weather->append(*dayweather);
    }
    DayWeather now_weather = future_weather->at(0);
    ui->lbl_today_weather->setText(QString("今日天气：%1").arg(now_weather.weather_text));
    QStringList temp_list = now_weather.temp.split("/");
    ui->lbl_day_tempMax->setText(QString("最高温度：%1").arg(temp_list[0]));
    ui->lbl_day_tempMin->setText(QString("最低温度：%1").arg(temp_list[1]));

    for (int i = 1;i < 7;i++) {
        DayWeather day = future_weather->at(i);
        label_date[i-1]->setText(QString("日期:%1").arg(day.date));
        label_icon[i-1]->setStyleSheet(QString("image: url(:%1%2/)").arg(day.icon_path).arg(day.icon));
        label_weather[i-1]->setText(QString("天气:%1").arg(day.weather_text));
        label_temp[i-1]->setText(QString("温度:%1").arg(day.temp));
    }
}

void WeatherWindow::on_bt_back_clicked()
{
    //返回登录界面
    this->parentWidget()->show();
    //删除
    delete this;
}
