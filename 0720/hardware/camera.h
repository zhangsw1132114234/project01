#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QImage>
#include <QTimer>

namespace cv {
class VideoCapture;
class Mat;
}

class Camera : public QObject
{
    Q_OBJECT
public:
    explicit Camera(QObject *parent = nullptr);
    ~Camera();


signals:
    /* 传递图像信号*/
    void readyImage(const QImage&);

public slots:
    void selectCameraDevice(int);
    bool cameraProcess(bool);
private slots:
    /* 定时器发送图像信号*/
    void timerTimeOut();



private:
    QTimer *timer;
    cv::VideoCapture *capture;

    QImage matToQImage(const cv::Mat &img);
    void cameraStop();

};

#endif // CAMERA_H
