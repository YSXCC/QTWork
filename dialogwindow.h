#ifndef DIALOGWINDOW_H
#define DIALOGWINDOW_H

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

namespace Ui {
class DialogWindow;
}

class DialogWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DialogWindow(QWidget *parent = nullptr);
    ~DialogWindow();

private slots:
    void on_boxBt_clicked();

    void on_fileBt_clicked();

    void on_colorBt_clicked();

    void on_fontBt_clicked();

    void on_inputBt_clicked();

    void on_selfBt_clicked();

    void on_bt_return_clicked();

private:
    Ui::DialogWindow *ui;
};

#endif // DIALOGWINDOW_H
