#include "camera.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

Camera::Camera(QObject *parent) : QObject(parent)
{
    capture = new cv::VideoCapture();
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeOut()));
}

Camera::~Camera()
{
    delete capture;
    capture = NULL;
}

void Camera::timerTimeOut()
{
    /* 如果摄像头没有打开，停止定时器*/
    if (!capture->isOpened())
    {
        timer->stop();
        return;
    }
    static cv::Mat ColorImage;
    static cv::Mat GrayImage;
    *capture >> ColorImage;
    if (ColorImage.cols)
    {
        /* 将Mat图像转化为QImage图片*/
        emit readyImage(matToQImage(ColorImage));
    }


}

QImage Camera::matToQImage(const cv::Mat &img)
{
    /* USB摄像头和OV5640等都是RGB三通道，不考虑单/四通道摄像头 */
    if(img.type() == CV_8UC3) {

        /* 得到图像的的首地址 */
        const uchar *pimg = (const uchar*)img.data;

        /* 以img构造图片 */
        QImage qImage(pimg, img.cols, img.rows, img.step,
                      QImage::Format_RGB888);

        /* 在不改变实际图像数据的条件下，交换红蓝通道 */
        return qImage.rgbSwapped();
    }
    else if(img.type() == CV_8UC4)
       {

           const uchar *pSrc = (const uchar*)img.data;
           QImage qImage(pSrc, img.cols, img.rows, img.step, QImage::Format_ARGB32);
           return qImage.copy();
       }

    /* 返回QImage */

    return QImage();
}

bool Camera::cameraProcess(bool bl)
{
    if (bl)
    {
        timer->start(33);   //1s最多显示30帧
    } else
    {
        timer->stop();
        /* 关闭摄像头*/
        this->cameraStop();
    }
    return capture->isOpened();
}

void Camera::cameraStop()
{
    capture->release();
}

void Camera::selectCameraDevice(int index)
{
    /* 如果有其他摄像头打开了，先释放 */
    if (capture->isOpened()) {
        capture->release();
    }

    /* 打开摄像头设备 */
    capture->open(index);
}
