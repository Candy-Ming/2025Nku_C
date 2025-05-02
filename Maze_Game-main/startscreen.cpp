#include "StartScreen.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QInputDialog>
#include <QPainter>

StartScreen::StartScreen(QWidget *parent) : QWidget(parent) {
    game = new mazeWidget();
    setupUI();

    // 加载背景图
    backgroundImage.load(":/assets/background.png");
    if (backgroundImage.isNull()) {
        qDebug() << "无法加载开始界面背景图片!";
    }
}

void StartScreen::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap bg(":/assets/background.png");
    // 绘制背景图
    if (!backgroundImage.isNull()) {
        painter.drawPixmap(0, 0, width(), height(), backgroundImage);
    } else {
        // 如果背景图加载失败，则使用渐变背景
        QLinearGradient gradient(0, 0, width(), height());
        gradient.setColorAt(0, QColor(70, 70, 150));
        gradient.setColorAt(1, QColor(20, 20, 50));
        painter.fillRect(rect(), gradient);
    }
}

void StartScreen::setupUI() {
    setWindowTitle("迷宫游戏");
    setFixedSize(800, 600); // 固定窗口大小

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *title = new QLabel("迷宫游戏", this);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 48px; font-weight: bold; color: white; background-color: rgba(0, 0, 0, 100);");

    QPushButton *startButton = new QPushButton("开始游戏", this);
    startButton->setStyleSheet("font-size: 24px; padding: 10px; background-color: rgba(50, 150, 50, 200); color: white; border-radius: 10px;");
    connect(startButton, &QPushButton::clicked, this, [this]() {
        game->setDifficulty(currentDifficulty);
        game->show();
        game->startGameAuto();  // 自动开始游戏
        this->hide();
    });

    QPushButton *rulesButton = new QPushButton("游戏规则", this);
    rulesButton->setStyleSheet("font-size: 24px; padding: 10px; background-color: rgba(50, 50, 150, 200); color: white; border-radius: 10px;");
    connect(rulesButton, &QPushButton::clicked, this, &StartScreen::showRules);

    QPushButton *difficultyButton = new QPushButton("选择难度", this);
    difficultyButton->setStyleSheet("font-size: 24px; padding: 10px; background-color: rgba(150, 50, 50, 200); color: white; border-radius: 10px;");
    connect(difficultyButton, &QPushButton::clicked, this, &StartScreen::chooseDifficulty);

    layout->addStretch();
    layout->addWidget(title);
    layout->addSpacing(30);
    layout->addWidget(startButton);
    layout->addWidget(rulesButton);
    layout->addWidget(difficultyButton);
    layout->addStretch();
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
