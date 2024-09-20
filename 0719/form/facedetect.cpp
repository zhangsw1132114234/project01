#include "facedetect.h"
#include "ui_facedetect.h"

faceDetect::faceDetect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::faceDetect)
{
    ui->setupUi(this);
}

faceDetect::~faceDetect()
{
    delete ui;
}
