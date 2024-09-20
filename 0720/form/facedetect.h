#ifndef FACEDETECT_H
#define FACEDETECT_H

#include <QWidget>
#include <QList>
#include <QGuiApplication>
#include <QScreen>
#include <QImage>
#include "camera.h"

namespace Ui {
class faceDetect;
}

class faceDetect : public QWidget
{
    Q_OBJECT

public:
    explicit faceDetect(QWidget *parent = nullptr);
    ~faceDetect();

private:
    Ui::faceDetect *ui;

    Camera *camera;
    QImage saveImage;
    void layoutInit();

private slots:
    void setButtonText(bool);
    void showImage(const QImage&);
};

#endif // FACEDETECT_H
