#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "banna.h"
#include "facedetect.h"
/* 新建一个窗口结构体*/
struct WidgetItemData
{
    QString title;
    /* 定义了一个返回QWidget指针类型的函数指针*/
    typedef QWidget *(*CreateInstanceFunc)();
    CreateInstanceFunc createInstance;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    /* 实现主窗口*/
    widget = new QWidget(this);
    QList <QScreen *> list_screen = QGuiApplication::screens();
//#if __arm__
//    this->resize(list_screen.at(0)->geometry().width(),
//                 list_screen.at(0)->geometry().height());
//#else
    this->setGeometry(0, 0, 1024, 600);
//#endif
    this->setObjectName("project");
    widget->resize(this->size());


    this->windows_init();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::windows_init()
{
    /* 垂直布局实例化*/
    hBoxLayout = new QHBoxLayout();
    /* 堆栈部件实例化*/
    stackedWidget = new QStackedWidget();
    /* 列表实例化*/
    listWidget = new QListWidget();
    listWidget->setStyleSheet("background-color: black;");

    WidgetItemData items[] = {
        {"轮播图", []() -> QWidget * { return new banna; } },
        //{"OpenCV测试", []() -> QWidget * { return new opencv; } },
        {"摄像头人脸识别", []() -> QWidget * { return new faceDetect; } },
        //{"imx6ull板级设备", []() -> QWidget * { return new imx6ullTest; } },
        //{"音频播放器", []() -> QWidget * { return new MusicPlay; } },
        //{"视频播放器", []() -> QWidget * { return new VideoPlayer; } },
        //{"MQTT_CLIENT", []() -> QWidget * { return new mqtt_client; } },
        {"FFMPEG_TEST待完成", nullptr },
    };

    for (auto & itemData : items)
    {
        /* 创建listitem，并加入到listwidget中*/
        QListWidgetItem *item = new QListWidgetItem(itemData.title);
        item->setTextColor(Qt::white);
        item->setTextAlignment(Qt::AlignCenter);
        item->setSizeHint(QSize(100, 60));
        listWidget->addItem(item);

        if (itemData.createInstance)
        {
            stackedWidget->addWidget(itemData.createInstance());
        }
    }

    /* 将焦点设置为第一个项目*/
    if(listWidget->count() > 0)
    {
        QListWidgetItem* item1 = listWidget->item(0);
        listWidget->setCurrentItem(item1);
        listWidget->setItemSelected(item1, true);
        item1->setSelected(true);
        listWidget->setFocus();
    }

    /* 设置列表最大宽度*/
    hBoxLayout->setContentsMargins(0, 0, 0, 0);
    hBoxLayout->setSpacing(0);
    stackedWidget->setContentsMargins(0, 0, 0, 0);
    stackedWidget->setStyleSheet("QStackedWidget { margin: 0; padding: 0; border: none; }");
    listWidget->setMaximumWidth(200);
    /* 添加到水平布局 */
    hBoxLayout->addWidget(listWidget);
    hBoxLayout->addWidget(stackedWidget);

    /* 将widget的布局设置成hboxLayout */
    widget->setLayout(hBoxLayout);

    /* 利用listWidget的信号函数currentRowChanged()与
     * 槽函数setCurrentIndex(),进行信号与槽连接
    */
    connect(listWidget, SIGNAL(currentRowChanged(int)),
                stackedWidget, SLOT(setCurrentIndex(int)));

}
