#ifndef DAYWEATHER_H
#define DAYWEATHER_H

#include <QString>

class DayWeather
{
public:
    DayWeather();
    DayWeather(QString path);
    QString setDate(QString date);
    QString setIcon(QString icon_no);
    QString setWeatherText(QString weather_text);
    QString setTemp(QString temp_min,QString temp_max);
    QString date;
    QString icon_path;
    QString icon;
    QString weather_text;
    QString temp;
};

#endif // DAYWEATHER_H
