#ifndef CLOCKWINDOW_H
#define CLOCKWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>

namespace Ui {
class ClockWindow;
}

class ClockWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClockWindow(QWidget *parent = nullptr);
    ~ClockWindow();

private slots:

    void updateDisplay();

    void on_btn_start_clicked();

    void on_btn_stop_clicked();

    void on_btn_pause_clicked();

    void on_btn_point_clicked();

    void on_btn_back_clicked();

private:
    Ui::ClockWindow *ui;

    QTimer *pTimer;
    //基础时间
    QTime baseTime;
    //显示的时间
    QString timeStr;
};

#endif // CLOCKWINDOW_H
