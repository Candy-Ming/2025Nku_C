#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QPainter>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <QInputDialog>
#include <QPixmap>
#include <QLabel>
#include <QMovie>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "maze.h"

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
    void setDifficulty(int difficulty);  // 设置迷宫难度
    void startGameAuto();               // 自动开始游戏
    void resetGame();                   // 重置游戏状态

protected:
    void paintEvent(QPaintEvent*) override;   // 绘图事件
    void keyPressEvent(QKeyEvent*) override;  // 按键事件

private slots:
    void on_start_btn_clicked();       // 开始按钮点击
    void on_stop_ptn_clicked();        // 暂停按钮点击
    void on_end_btn_clicked();         // 终止按钮点击
    void on_rule_btn_clicked();        // 规则按钮点击
    void on_setting_btn_clicked();     // 设置按钮点击
    void on_solve_btn_clicked();       // 求解按钮点击
    void time_update();                // 计时器更新
    void dogAnimationUpdate();         // 动画帧更新

private:
    Ui::mazeWidget* ui;
    maze* map;

    // 状态控制
    bool painting_switch;      // 是否绘制迷宫
    bool timing_switch;        // 是否计时
    bool keybord_switch;       // 是否响应键盘
    bool stop_switch;          // 暂停状态标记
    bool solving_mode;         // 是否正在求解（避免庆祝动画触发）

    // 分数和时间
    int grade;
    int time;

    // 计时器
    QTimer* timer;             // 游戏倒计时
    QTimer* animationTimer;    // 动画播放计时

    // 小狗动画
    QVector<QPixmap> dogUpFrames;
    QVector<QPixmap> dogDownFrames;
    QVector<QPixmap> dogLeftFrames;
    QVector<QPixmap> dogRightFrames;
    QPixmap currentDogFrame;
    int currentFrameIndex;
    int direction; // 0=上, 1=下, 2=左, 3=右

    void loadDogAnimations();  // 加载小狗帧动画

    // 音乐播放
    QMediaPlayer* musicPlayer;
    QAudioOutput* audioOutput;

    // 胜利动画
    void showVictoryAnimation();
};

#endif // MAZEWIDGET_H
