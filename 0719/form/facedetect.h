#ifndef FACEDETECT_H
#define FACEDETECT_H

#include <QWidget>

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
};

#endif // FACEDETECT_H
