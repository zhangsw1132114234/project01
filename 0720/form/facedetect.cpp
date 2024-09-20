#include "facedetect.h"
#include "ui_facedetect.h"


faceDetect::faceDetect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::faceDetect)
{
    ui->setupUi(this);

    /* 布局初始化*/
    layoutInit();

}

faceDetect::~faceDetect()
{
    delete ui;
}


void faceDetect::layoutInit()
{
    QList<QScreen *> list_screen = QGuiApplication::screens();
    ui->displayLabel->setScaledContents(true);

    ui->takePic->setText("拍照");
    ui->takePic->setEnabled(false);
    ui->start->setText("开始");
    ui->start->setCheckable(true);

    /* 摄像头*/
    camera = new Camera(this);
    connect(ui->start, SIGNAL(clicked(bool)), camera, SLOT(cameraProcess(bool)));
    connect(ui->start, SIGNAL(clicked(bool)), this, SLOT(setButtonText(bool)));
    connect(camera, SIGNAL(readyImage(QImage)), this, SLOT(showImage(QImage)));

}

void faceDetect::setButtonText(bool bl)
{
    if (bl)
    {
        /* 选择输入设备*/
        camera->selectCameraDevice(ui->comboBox->currentIndex());
        ui->start->setText("关闭");
    }else
    {
        ui->takePic->setEnabled(false);
        ui->start->setText("开始");
    }
}

void faceDetect::showImage(const QImage & image)
{
    ui->displayLabel->setPixmap(QPixmap::fromImage(image));
    saveImage = image;
    /* 判断图像是否为空，空则设置拍照按钮不可用 */
    if (!saveImage.isNull())
        ui->takePic->setEnabled(true);
    else
        ui->takePic->setEnabled(false);
}
