#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QGuiApplication>
#include <QScreen>
#include <QHBoxLayout>
#include <QListWidget>
#include <QStackedWidget>
#include <QLabel>
#include <QListWidgetItem>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWidget *widget;
    /* 水平布局 */
    QHBoxLayout *hBoxLayout;
    /* 列表视图 */
    QListWidget *listWidget;
    /* 堆栈窗口部件 */
    QStackedWidget *stackedWidget;
    /* 3个标签 */
    QLabel *label[3];


    void windows_init();
};
#endif // MAINWINDOW_H
