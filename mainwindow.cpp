#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Player = new QMediaPlayer();

    ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButton_Stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pushButton_Seek_Backward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->pushButton_Seek_Forward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

    ui->horizontalSlider_Volume->setMinimum(0);
    ui->horizontalSlider_Volume->setMaximum(100);
    ui->horizontalSlider_Volume->setValue(30);

    Player->setVolume(ui->horizontalSlider_Volume->value());

    Playlist = new QMediaPlaylist(Player);

    //Slider = new QSlider(this);
    //Bar = new QProgressBar(this);

    //Slider->setOrientation(Qt::Horizontal);

    //ui->statusbar->addPermanentWidget(Slider);
    //ui->statusbar->addPermanentWidget(Bar);

    /*connect(Player, &QMediaPlayer::durationChanged, Slider, &QSlider::setMaximum);
    connect(Player, &QMediaPlayer::positionChanged, Slider, &QSlider::setValue);
    connect(Slider, &QSlider::sliderMoved, Player, &QMediaPlayer::setPosition);*/

    connect(Player, &QMediaPlayer::durationChanged, ui->horizontalSlider, &QSlider::setMaximum);
    connect(Player, &QMediaPlayer::positionChanged, ui->horizontalSlider, &QSlider::setValue);
    connect(ui->horizontalSlider, &QSlider::sliderMoved, Player, &QMediaPlayer::setPosition);

    //connect(Player, &QMediaPlayer::durationChanged, Bar, &QProgressBar::setMaximum);
    //connect(Player, &QMediaPlayer::positionChanged, Bar, &QProgressBar::setValue);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_video_triggered()
{
    /*QString File_Name = QFileDialog::getOpenFileName(this, tr("Select Video File"), "", tr("MP4 Files (*.mp4)"));

    Video = new QVideoWidget();
    Video->setGeometry(5, 5, ui->groupBox_Video->width()-10, ui->groupBox_Video->height()-10);
    Video->setParent(ui->groupBox_Video);
    Player->setVideoOutput(Video);
    #ifdef _WIN32
        Player->setMedia(QUrl(File_Name));
    #elif __linux__
        Player->setMedia(QUrl("file:"%File_Name));
    #endif
    Video->setVisible(true);
        Video->show();*/

    Playlist->clear();
    ui->play_list->clear();
    Play_list_index = 0;
    Play_list_size = 0;
    QFileInfo* fi;
    QStringList filenames = QFileDialog::getOpenFileNames(this, "Open a File","","Video File(*.mp4)");
    for(const QString & filename: filenames){
        Playlist->addMedia(QMediaContent(QUrl::fromLocalFile(filename)));
        fi = new QFileInfo(QUrl::fromLocalFile(filename).toString());
        ui->play_list->addItem(fi->fileName());
        Play_list_size++;
    }

    Video = new QVideoWidget();
    Video->setGeometry(5, 5, ui->groupBox_Video->width()-10, ui->groupBox_Video->height()-10);
    Video->setParent(ui->groupBox_Video);
    Player->setVideoOutput(Video);
    Player->setPlaylist(Playlist);
    Video->setVisible(true);
    Video->show();

    ui->play_list->item(Play_list_index)->setSelected(true);
}

void MainWindow::on_horizontalSlider_Duration_valueChanged(int value)
{
    Player->setPosition(value*1000);
}

void MainWindow::on_pushButton_Play_Pause_clicked()
{
    if(is_Pause == true)
    {
        is_Pause = false;
        Player->play();
        ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }
    else
    {
        is_Pause = true;
        Player->pause();
        ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}

void MainWindow::on_pushButton_Stop_clicked()
{
    Player->stop();
    is_Pause = true;
    ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
}

void MainWindow::on_pushButton_Volume_clicked()
{
    if(is_Muted == false)
    {
        is_Muted = true;
        ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        Player->setMuted(true);
    }
    else
    {
        is_Muted = false;
        ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        Player->setMuted(false);

    }
}

void MainWindow::on_horizontalSlider_Volume_valueChanged(int value)
{
    Player->setVolume(value);
}


void MainWindow::on_actionOpen_music_triggered()
{   
    Playlist->clear();
    ui->play_list->clear();
    Play_list_index = 0;
    Play_list_size = 0;
    QFileInfo* fi;
    QStringList filenames = QFileDialog::getOpenFileNames(this, "Open a File","","Video File(*.mp3)");
    for(const QString & filename: filenames){
        Playlist->addMedia(QMediaContent(QUrl::fromLocalFile(filename)));
        fi = new QFileInfo(QUrl::fromLocalFile(filename).toString());
        ui->play_list->addItem(fi->fileName());
        Play_list_size++;
    }

    Audio = new QAudioOutput();
    Player->setPlaylist(Playlist);

    ui->play_list->item(Play_list_index)->setSelected(true);
}

void MainWindow::on_pushButton_Seek_Forward_clicked()
{
    Playlist->next();

    Play_list_index = (Play_list_index+1) % Play_list_size;
    ui->play_list->item(Play_list_index)->setSelected(true);
}


void MainWindow::on_pushButton_Seek_Backward_clicked()
{

    if(Play_list_index-1 >= 0)
    {
        Playlist->previous();
        Play_list_index--;
    }

    ui->play_list->item(Play_list_index)->setSelected(true);
}


void MainWindow::on_actionManage_libraries_triggered()
{

}

