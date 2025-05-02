#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H

#include <QWidget>
#include <QMessageBox>      //Qt信息窗口头文件
#include <QPainter>         //Qt绘图头文件
#include <QDebug>           //QtDebug头文件
#include <QKeyEvent>        //Qt按键事件头文件
#include <QTimer>           //Qt计时器头文件
#include <QInputDialog>     //Qt输入对话框头文件
#include <QPixmap>          //Qt图像文件
#include "maze.h"           //迷宫类头文件

QT_BEGIN_NAMESPACE
namespace Ui {
class mazeWidget;
}
QT_END_NAMESPACE
class mazeWidget : public QWidget {
    Q_OBJECT
public:
    mazeWidget(QWidget* parent = nullptr);
    ~mazeWidget();
public:
    void setDifficulty(int difficulty);

protected:
    void paintEvent(QPaintEvent*);        //绘图事件
    void keyPressEvent(QKeyEvent*);       //按键按下事件

private slots:
    void on_start_btn_clicked();    //|
    void on_stop_ptn_clicked();     //|
    void on_end_btn_clicked();      //|
    void on_rule_btn_clicked();     //|各按钮点击槽函数
    void on_setting_btn_clicked();  //|
    void time_update();             //时间更新槽函数
    void on_solve_btn_clicked();
    void dogAnimationUpdate();      //狗动画更新槽函数

public:
    void startGameAuto();           // 自动开始游戏
    void resetGame();               // 重新初始化游戏状态

private:
    Ui::mazeWidget* ui;             //ui对象
    maze* map;                      //迷宫对象

    bool painting_switch;           //绘图开关
    bool timing_switch;             //计时开关
    bool keybord_switch;            //键盘响应开关
    bool stop_switch;               //暂停按钮状态

    int grade;                      //分数
    int time;                       //时间
    QTimer* timer;                  //游戏计时器
    QTimer* animationTimer;         //动画计时器

    // 狗的动画相关变量
    QVector<QPixmap> dogUpFrames;    //向上走的动画帧
    QVector<QPixmap> dogDownFrames;  //向下走的动画帧
    QVector<QPixmap> dogLeftFrames;  //向左走的动画帧
    QVector<QPixmap> dogRightFrames; //向右走的动画帧
    QPixmap currentDogFrame;         //当前显示的动画帧
    int currentFrameIndex;           //当前帧索引
    int direction;                   //当前方向 (0=上, 1=下, 2=左, 3=右)

    void loadDogAnimations();        //加载狗的动画
};
#endif // MAZEWIDGET_H
