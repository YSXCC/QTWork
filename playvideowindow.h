#ifndef PLAYVIDEOWINDOW_H
#define PLAYVIDEOWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QFileDialog>
#include <QListWidget>

namespace Ui {
class PlayVideoWindow;
}

class PlayVideoWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void on_bt1_clicked();

    void on_bt2_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void play_next(int num);

    void on_bt_return_clicked();

public:
    explicit PlayVideoWindow(QWidget *parent = nullptr);
    ~PlayVideoWindow();

private:
    Ui::PlayVideoWindow *ui;
    QProcess mprocess;
};

#endif // PLAYVIDEOWINDOW_H
