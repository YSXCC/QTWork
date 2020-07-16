#include "dayweather.h"

DayWeather::DayWeather()
{
    this->icon_path = "/weather/resource/weather/";
}

DayWeather::DayWeather(QString path)
{
    this->icon_path = path;
}

QString DayWeather::setDate(QString date)
{
    this->date = date;
    return this->date;
}

QString DayWeather::setIcon(QString icon_no)
{
    this->icon = icon_no+".png";
    return this->icon;
}

QString DayWeather::setWeatherText(QString weather_text)
{
    this->weather_text = weather_text;
    return this->weather_text;
}

QString DayWeather::setTemp(QString temp_min,QString temp_max)
{
    this->temp = temp_max+"℃/"+temp_min+"℃";
    return this->temp;
}
