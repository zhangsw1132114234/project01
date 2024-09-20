#ifndef BANNA_H
#define BANNA_H

#include <QWidget>
#include <QTimer>
#include <QButtonGroup>
#include <QPushButton>
#include <QLabel>
#include <QPropertyAnimation>
#include <QByteArray>
#include <QParallelAnimationGroup>
namespace Ui {
class banna;
}

namespace BannaSpace {
const int INTERVAL_DURTION = 3000;
const QByteArray ANIMATION_GEOMETRY = "gemotry";
const int ANIMATION_DURTION = 200;
const QString FIRST_IMAGE_PATH = ":/images/banna_pic/banna/1.jpg";
const QString SECOND_IMAGE_PATH = ":/images/banna_pic/banna/2.jpg";
const QString THIRD_IMAGE_PATH = ":/images/banna_pic/banna/3.jpg";
const QString FOURTH_IMAGE_PATH = ":/images/banna_pic/banna/4.jpg";
const QString FIFTH_IMAGE_PATH = ":/images/banna_pic/banna/5.jpg";


}

typedef struct BannaData
{
    QPushButton *pushButton;    //按钮
    QLabel *currentImageLabel;  //图片label
    QLabel *nextImageLabel;     //下一个图片
    QLabel *preImageLabel;      //上一个图片
    QPropertyAnimation *proAnimation;   //动画
}BannaData;

class banna : public QWidget
{
    Q_OBJECT

public:
    explicit banna(QWidget *parent = nullptr);
    ~banna();

private:
    Ui::banna *ui;
    QTimer *changeImageTimer = nullptr;
    QButtonGroup buttonGroup;
    QList<BannaData> bannaDataList;
    QParallelAnimationGroup animationGroup;

    void initValue();
    void setNextAnimation();


private slots:
    void slot_changeImageTimer();
};

#endif // BANNA_H
