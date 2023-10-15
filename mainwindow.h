#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia/QtMultimedia>
#include <QtMultimediaWidgets/QtMultimediaWidgets>
#include <QtMultimedia/QMediaObject>
#include <QtCore>
#include <QtWidgets>
#include <QtGui>
#include <QMediaMetaData>

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

    void on_actionOpen_video_triggered();

    void on_horizontalSlider_Duration_valueChanged(int value);

    void on_pushButton_Play_Pause_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButton_Volume_clicked();

    void on_horizontalSlider_Volume_valueChanged(int value);

    void on_actionOpen_music_triggered();

    void on_pushButton_Seek_Forward_clicked();

    void on_pushButton_Seek_Backward_clicked();

    void on_actionManage_libraries_triggered();

private:
    Ui::MainWindow* ui;
    QMediaPlayer* Player;
    QVideoWidget* Video;
    QAudioOutput* Audio;
    bool is_Pause = true;
    bool is_Muted = false;

    QProgressBar* Bar;
    QSlider* Slider;
    QMediaPlaylist * Playlist;
    QDir m_musicPath;
    QVariantList _music;
    int Play_list_index;
    int Play_list_size;

    void updateDuration(quint64 duration);
};
#endif // MAINWINDOW_H
