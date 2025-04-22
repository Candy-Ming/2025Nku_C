#include "StartScreen.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QInputDialog>

StartScreen::StartScreen(QWidget *parent) : QWidget(parent) {
    game = new mazeWidget();
    setupUI();
}

void StartScreen::setupUI() {
    setWindowTitle("迷宫游戏");
    setFixedSize(800, 600); // 固定窗口大小

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *title = new QLabel("迷宫游戏", this);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 36px; font-weight: bold;");

    QPushButton *startButton = new QPushButton("开始游戏", this);
    connect(startButton, &QPushButton::clicked, this, [this]() {
        game->setDifficulty(currentDifficulty);
        game->show();
        game->startGameAuto();  // 自动开始游戏
        this->hide();
    });

    QPushButton *rulesButton = new QPushButton("游戏规则", this);
    //rulesButton->setFixedSize(200, 50);
    connect(rulesButton, &QPushButton::clicked, this, &StartScreen::showRules);

    QPushButton *difficultyButton = new QPushButton("选择难度", this);
    //difficultyButton->setFixedSize(200, 50);
    connect(difficultyButton, &QPushButton::clicked, this, &StartScreen::chooseDifficulty);

    layout->addWidget(title);
    layout->addWidget(startButton);
    layout->addWidget(rulesButton);
    layout->addWidget(difficultyButton);
    layout->setAlignment(Qt::AlignCenter);

    setLayout(layout);
}

// 规则说明
void StartScreen::showRules() {
    QMessageBox::information(this, "游戏规则", "计时200秒，根据迷宫等级与经过关卡记分。\n操作方式：WASD 或 IJKL 控制方向。");
}

// 选择难度
void StartScreen::chooseDifficulty() {
    QStringList difficulties;
    difficulties << "小朋友难度 (5阶迷宫)"
                 << "简单难度 (10阶迷宫)"
                 << "普通难度 (20阶迷宫)"
                 << "困难难度 (40阶迷宫)";

    QString selectedDifficulty = QInputDialog::getItem(this, "选择难度", "请选择一个难度：", difficulties, 2, false);

    if (selectedDifficulty == "小朋友难度 (5阶迷宫)") {
        currentDifficulty = 5;
    } else if (selectedDifficulty == "简单难度 (10阶迷宫)") {
        currentDifficulty = 10;
    } else if (selectedDifficulty == "普通难度 (20阶迷宫)") {
        currentDifficulty = 20;
    } else if (selectedDifficulty == "困难难度 (40阶迷宫)") {
        currentDifficulty = 40;
    }
}
