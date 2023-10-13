#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia/QtMultimedia>
#include <QtMultimediaWidgets/QtMultimediaWidgets>
#include <QtCore>
#include <QtWidgets>
#include <QtGui>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void durationChanged(quint64 duration);

    void positionChanged(quint64 progress);

    void on_actionOpen_triggered();

    void on_horizontalSlider_Duration_valueChanged(int value);

    void on_pushButton_Play_Pause_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButton_Volume_clicked();

    void on_horizontalSlider_Volume_valueChanged(int value);

    void on_pushButton_Seek_Backward_clicked();

    void on_pushButton_Seek_Forward_clicked();

private:
    Ui::MainWindow* ui;
    QMediaPlayer* Player;
    QVideoWidget* Video;
    qint64 mDuration;
    bool is_Pause = true;
    bool is_Muted = false;

    void updateDuration(quint64 duration);
};
#endif // MAINWINDOW_H
