#include "banna.h"
#include "ui_banna.h"

banna::banna(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::banna)
{
    ui->setupUi(this);
    this->initValue();
}

banna::~banna()
{
    delete ui;
}

void banna::initValue()
{
    /* 设置一个定时器，实现轮播效果*/
    changeImageTimer = new QTimer();
    connect(changeImageTimer, SIGNAL(timerout()), this, SLOT(slot_changeImageTimer()));
    changeImageTimer->setInterval(BannaSpace::INTERVAL_DURTION);
    changeImageTimer->start();
    /* 为按钮组，添加按钮成员，作用：待定*/
    buttonGroup.addButton(ui->pushButtonFirst);
    buttonGroup.addButton(ui->pushButtonSecond);
    buttonGroup.addButton(ui->pushButtonThird);
    buttonGroup.addButton(ui->pushButtonFourth);
    buttonGroup.addButton(ui->pushButtonFifth);
    /* 每一个图片的数据结构赋值*/
    {
        BannaData bannaData;
        bannaData.pushButton = ui->pushButtonFirst;
        bannaData.currentImageLabel = ui->labelFirst;
        bannaData.nextImageLabel = ui->labelSecond;
        bannaData.preImageLabel = ui->labelFifth;
        bannaData.proAnimation = new QPropertyAnimation(ui->labelFirst,BannaSpace::ANIMATION_GEOMETRY);    //
        bannaDataList.append(bannaData);
    }
    {
        BannaData bannaData;
        bannaData.pushButton = ui->pushButtonSecond;
        bannaData.currentImageLabel = ui->labelSecond;
        bannaData.nextImageLabel = ui->labelThird;
        bannaData.preImageLabel = ui->labelFirst;
        bannaData.proAnimation = new QPropertyAnimation(ui->labelSecond, BannaSpace::ANIMATION_GEOMETRY);
        bannaDataList.append(bannaData);
    }


    {
        BannaData bannaData;
        bannaData.pushButton = ui->pushButtonThird;
        bannaData.currentImageLabel = ui->labelThird;
        bannaData.nextImageLabel = ui->labelFourth;
        bannaData.preImageLabel = ui->labelSecond;
        bannaData.proAnimation = new QPropertyAnimation(ui->labelThird, BannaSpace::ANIMATION_GEOMETRY);
        bannaDataList.append(bannaData);
    }


    {
        BannaData bannaData;
        bannaData.pushButton = ui->pushButtonFourth;
        bannaData.currentImageLabel = ui->labelFourth;
        bannaData.nextImageLabel = ui->labelFifth;
        bannaData.preImageLabel = ui->labelThird;
        bannaData.proAnimation = new QPropertyAnimation(ui->labelFourth, BannaSpace::ANIMATION_GEOMETRY);
        bannaDataList.append(bannaData);
    }


    {
        BannaData bannaData;
        bannaData.pushButton = ui->pushButtonFifth;
        bannaData.currentImageLabel = ui->labelFifth;
        bannaData.nextImageLabel = ui->labelFirst;
        bannaData.preImageLabel = ui->labelFourth;
        bannaData.proAnimation = new QPropertyAnimation(ui->labelFifth, BannaSpace::ANIMATION_GEOMETRY);
        bannaDataList.append(bannaData);
    }
    for (int i; i < bannaDataList.size(); i++)
    {
        /* 功能：未知*/
        bannaDataList.at(i).currentImageLabel->installEventFilter(this);
        bannaDataList.at(i).proAnimation->setDuration(BannaSpace::ANIMATION_DURTION);
        /* 设置从开始到结束的动画效果*/
        bannaDataList.at(i).proAnimation->setEasingCurve(QEasingCurve::BezierSpline);
        /* 功能：未知*/
        animationGroup.addAnimation(bannaDataList.at(i).proAnimation);
    }

    /* 设置图片路径，为轮播图添加图片*/
    QList<QString> listImagePath;
    listImagePath.append();

}

void banna::slot_changeImageTimer()
{
    /* 右移动画*/
}

void banna::setNextAnimation()
{

}
