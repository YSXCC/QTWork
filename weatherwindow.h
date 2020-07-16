#ifndef WEATHERWINDOW_H
#define WEATHERWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QString>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>

#include <QList>

#include "dayweather.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WeatherWindow; }
QT_END_NAMESPACE

class WeatherWindow : public QMainWindow
{
    Q_OBJECT

public:
    WeatherWindow(QWidget *parent = nullptr);
    ~WeatherWindow();

private slots:
    void dateTimeTimer();

    void on_bt_search_clicked();

    void parseCityId(QNetworkReply *app);

    void parseNowWeather(QNetworkReply *app);

    void parseFutureWeather(QNetworkReply *app);

    void on_bt_back_clicked();

private:
    Ui::WeatherWindow *ui;
    QString api_url_now = "https://devapi.heweather.net/v7/weather/now?key=485ca4c2da144e9ba27d90977e5912f2&location=";
    QString api_url_7d  = "https://devapi.heweather.net/v7/weather/7d?key=485ca4c2da144e9ba27d90977e5912f2&location=";
    QString api_url_cityId = "https://geoapi.heweather.net/v2/city/lookup?key=485ca4c2da144e9ba27d90977e5912f2&location=";
    //日期时间展示
    QTimer *timer_date_and_time;
    //接受城市的网络管理类
    QNetworkAccessManager manager_city_id;
    //接受当前天气的网络管理类
    QNetworkAccessManager manager_now_weather;
    //接受未来天气的网络管理类
    QNetworkAccessManager manager_future_weather;
    //请求现在天气json
    void getNowWeather(QString city_id);
    //请求未来天气json
    void getFutureWeather(QString city_id);
    //未来天气控件数组
    QLabel *label_date[6];
    QLabel *label_icon[6];
    QLabel *label_weather[6];
    QLabel *label_temp[6];
};
#endif // WEATHERWINDOW_H
