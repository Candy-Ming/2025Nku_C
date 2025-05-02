#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QWidget>
#include <QPaintEvent>
#include <QPixmap>
#include "mazeWidget.h"

class StartScreen : public QWidget {
    Q_OBJECT

public:
    explicit StartScreen(QWidget *parent = nullptr);

signals:
    void startGame(int difficulty); // 传递难度给 mazeWidget

private slots:
    void showRules();  // 显示规则
    void chooseDifficulty(); // 选择难度

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int currentDifficulty = 20; // 默认 20 阶迷宫
    void setupUI();

    mazeWidget *game;
    QPixmap backgroundImage; // 背景图片
};

#endif // STARTSCREEN_H
