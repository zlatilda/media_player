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

    //connect(Player, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);
    //connect(Player, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);
    ui->horizontalSlider_Duration->setRange(0, Player->duration()/1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::durationChanged(quint64 duration)
{
   mDuration = duration/1000;
   ui->horizontalSlider_Duration->setMaximum(mDuration);
}

void MainWindow::positionChanged(quint64 progress)
{
    if(!ui->horizontalSlider_Duration->isSliderDown())
    {
        ui->horizontalSlider_Duration->setValue(progress/1000);
    }
    updateDuration(progress/1000);
}

void MainWindow::updateDuration(quint64 duration)
{
    if(duration || mDuration)
    {
        QTime CurrentTime((duration/3600)%60, (duration/60)%60, duration%60, (duration*1000)%1000);
        QTime TotalTime((mDuration/3600)%60, (mDuration/60)%60, mDuration%60, (mDuration*1000)%1000);
        QString format = "mm:ss";
        if(mDuration > 3600)
        {
            format = "hh:mm:ss";
        }
        ui->label_current_Time->setText(CurrentTime.toString(format));
        ui->label_Total_Time->setText(TotalTime.toString(format));
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString File_Name = QFileDialog::getOpenFileName(this, tr("Select Video File"), "", tr("MP4 Files (*.mp4)")); // plays mp3 too
    ui->label->setText(File_Name);
    Video = new QVideoWidget();
    Video->setGeometry(5, 5, ui->groupBox_Video->width()-10, ui->groupBox_Video->height()-10);
    Video->setParent(ui->groupBox_Video);
    Player->setVideoOutput(Video);
    Player->setMedia(QUrl(File_Name));
    Video->setVisible(true);
    Video->show();
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


void MainWindow::on_pushButton_Seek_Backward_clicked()
{
    ui->horizontalSlider_Duration->setValue(ui->horizontalSlider_Duration->value()-20);
    Player->setPosition(ui->horizontalSlider_Duration->value()*1000);
}


void MainWindow::on_pushButton_Seek_Forward_clicked()
{
    ui->horizontalSlider_Duration->setValue(ui->horizontalSlider_Duration->value()+20);
    Player->setPosition(ui->horizontalSlider_Duration->value()*1000);
}

