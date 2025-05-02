#include "mazewidget.h"
#include "ui_mazewidget.h"

#include <QMovie>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>

mazeWidget::mazeWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::mazeWidget), map(new maze(20))
    , painting_switch(false), timing_switch(false), keybord_switch(false), stop_switch(false)
    , grade(0), time(0), currentFrameIndex(0), direction(1), solving_mode(false)
{
    ui->setupUi(this);
    setWindowTitle("迷宫游戏");
    setFixedSize(800, 600);
    hide();

    ui->progressBar->setVisible(false);
    ui->end_btn->setEnabled(false);
    ui->stop_ptn->setEnabled(false);
    ui->grade_value->setText(" ");
    ui->time_value->setText(" ");

    map->makemap();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &mazeWidget::time_update);

    animationTimer = new QTimer(this);
    animationTimer->setInterval(200);
    connect(animationTimer, &QTimer::timeout, this, &mazeWidget::dogAnimationUpdate);

    loadDogAnimations();

    // 背景音乐
    musicPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    musicPlayer->setAudioOutput(audioOutput);
    musicPlayer->setSource(QUrl("qrc:/assets/bgm.mp3"));
    audioOutput->setVolume(50);
    musicPlayer->setLoops(QMediaPlayer::Infinite);
    musicPlayer->play();
}

mazeWidget::~mazeWidget() {
    delete ui;
    delete map;
    delete timer;
    delete animationTimer;
}

void mazeWidget::loadDogAnimations() {
    dogUpFrames << QPixmap(":/sprites/dog_up1.png") << QPixmap(":/sprites/dog_up2.png");
    dogDownFrames << QPixmap(":/sprites/dog_down1.png") << QPixmap(":/sprites/dog_down2.png");
    dogLeftFrames << QPixmap(":/sprites/dog_left1.png") << QPixmap(":/sprites/dog_left2.png");
    dogRightFrames << QPixmap(":/sprites/dog_right1.png") << QPixmap(":/sprites/dog_right2.png");
    currentDogFrame = dogDownFrames.first();
}

void mazeWidget::dogAnimationUpdate() {
    currentFrameIndex = (currentFrameIndex + 1) % 2;
    switch (direction) {
    case 0: currentDogFrame = dogUpFrames[currentFrameIndex]; break;
    case 1: currentDogFrame = dogDownFrames[currentFrameIndex]; break;
    case 2: currentDogFrame = dogLeftFrames[currentFrameIndex]; break;
    case 3: currentDogFrame = dogRightFrames[currentFrameIndex]; break;
    }
    repaint();
}

void mazeWidget::paintEvent(QPaintEvent*) {
    if (!painting_switch) return;

    QPainter painter(this);
    QPixmap grass(":/assets/grass.png");
    painter.drawPixmap(rect(), grass.scaled(size()));

    QPixmap brick(":/tiles/brick.png");
    QPixmap paw(":/assets/paw.png");
    QPixmap flag(":/assets/flag.png");

    int perblock = (std::min(ui->frame->width(), ui->frame->height()) - 20) / map->getside();
    int start_x = ui->frame->x() + (ui->frame->width() - map->getside() * perblock) / 2;
    int start_y = ui->frame->y() + (ui->frame->height() - map->getside() * perblock) / 2;

    for (int i = 0; i < map->getlevel() * 2 + 1; ++i) {
        for (int j = 0; j < map->getlevel() * 2 + 1; ++j) {
            QRect block(start_x + i * perblock, start_y + j * perblock, perblock, perblock);
            int val = map->getmap()[i][j];

            if (i == map->p_x && j == map->p_y) {
                QPixmap scaled = currentDogFrame.scaled(perblock, perblock, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                painter.drawPixmap(block, scaled);
            } else if (val == 7) {
                if (!paw.isNull()) painter.drawPixmap(block, paw.scaled(perblock, perblock, Qt::KeepAspectRatio));
            } else if (val == 6) {
                if (!flag.isNull()) painter.drawPixmap(block, flag.scaled(perblock, perblock, Qt::KeepAspectRatio));
            } else if (val == 3 || val == 4) {
                painter.fillRect(block, Qt::white);
            } else {
                if (!brick.isNull()) painter.drawPixmap(block, brick.scaled(perblock, perblock));
            }
        }
    }
}

void mazeWidget::keyPressEvent(QKeyEvent* event) {
    if (!keybord_switch) return;

    int x = map->p_x, y = map->p_y;
    bool moved = false;

    if (event->key() == Qt::Key_W || event->key() == Qt::Key_I) {
        if ((*map)[x][y - 1] >= 3) { map->p_y--; direction = 0; moved = true; }
    } else if (event->key() == Qt::Key_S || event->key() == Qt::Key_K) {
        if ((*map)[x][y + 1] >= 3) { map->p_y++; direction = 1; moved = true; }
    } else if (event->key() == Qt::Key_A || event->key() == Qt::Key_J) {
        if ((*map)[x - 1][y] >= 3) { map->p_x--; direction = 2; moved = true; }
    } else if (event->key() == Qt::Key_D || event->key() == Qt::Key_L) {
        if ((*map)[x + 1][y] >= 3) { map->p_x++; direction = 3; moved = true; }
    }

    if (moved) {
        if ((*map)[map->p_x][map->p_y] != 5 && (*map)[map->p_x][map->p_y] != 6)
            (*map)[map->p_x][map->p_y] = 7;

        if ((*map)[map->p_x][map->p_y] == 6 && !solving_mode) {
            showVictoryAnimation();
            map->makemap();
            grade += pow(map->getlevel(), 2);
            ui->grade_value->setText(QString::number(grade));
        }

        dogAnimationUpdate();
    }
}


void mazeWidget::showVictoryAnimation() {
    // 创建遮罩层（半透明黑色背景）
    QWidget* overlay = new QWidget(this);
    overlay->setGeometry(0, 0, width(), height());
    overlay->setStyleSheet("background-color: rgba(0, 0, 0, 150);");
    overlay->setAttribute(Qt::WA_DeleteOnClose);
    overlay->show();

    // 创建 QLabel 展示 GIF
    QLabel* label = new QLabel(overlay);
    QMovie* movie = new QMovie(":/assets/celebrate.gif");

    // 设置动画缩放适配整个窗口
    movie->setScaledSize(size());
    label->setMovie(movie);
    label->setGeometry(0, 0, width(), height());
    label->setAlignment(Qt::AlignCenter);
    label->show();

    movie->start();

    // 播放结束后自动关闭遮罩层和动画
    QTimer::singleShot(2000, overlay, &QWidget::close);
}


void mazeWidget::setDifficulty(int d) {
    delete map;
    map = new maze(d);
    map->makemap();
    repaint();
}

void mazeWidget::resetGame() {
    painting_switch = false;
    timing_switch = false;
    keybord_switch = false;
    stop_switch = false;
    grade = 0;
    time = 0;
    animationTimer->stop();
    map->makemap();
    ui->progressBar->setVisible(false);
    ui->end_btn->setEnabled(false);
    ui->stop_ptn->setEnabled(false);
    ui->grade_value->setText(" ");
    ui->time_value->setText(" ");
    ui->start_btn->setEnabled(true);
    ui->setting_btn->setEnabled(true);
    repaint();
}

void mazeWidget::time_update() {
    if (time > 0) {
        time--;
        ui->time_value->setText(QString::number(time));
        ui->progressBar->setValue(time / 2);
    } else {
        timer->stop();
        animationTimer->stop();
        painting_switch = false;
        keybord_switch = false;
        timing_switch = false;
        ui->stop_ptn->setEnabled(false);
        ui->end_btn->setEnabled(false);
        ui->start_btn->setEnabled(true);
        ui->setting_btn->setEnabled(true);
        ui->progressBar->setVisible(false);
        ui->time_value->setText(" ");
        ui->grade_value->setText(" ");
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("🎉 游戏结束 🎉");
        msgBox.setText("您的最终得分：<b><span style='font-size:28px; color:#008000;'>" + QString::number(grade) + "</span></b>");
        msgBox.setStyleSheet("QLabel{min-width: 300px; min-height: 100px; font-size: 20px;}"
                             "QPushButton{width:80px; height:30px; font-size:16px;}");
        msgBox.exec();

        grade = 0;
    }
}

void mazeWidget::on_start_btn_clicked() {
    startGameAuto();
}

void mazeWidget::on_stop_ptn_clicked() {
    if (stop_switch) {
        keybord_switch = false;
        timing_switch = false;
        timer->stop();
        animationTimer->stop();
        ui->stop_ptn->setText("继续");
        stop_switch = false;
    } else {
        keybord_switch = true;
        timing_switch = true;
        timer->start();
        animationTimer->start();
        ui->stop_ptn->setText("暂停");
        stop_switch = true;
    }
}

void mazeWidget::on_end_btn_clicked() {
    timer->stop();
    animationTimer->stop();
    painting_switch = false;
    keybord_switch = false;
    timing_switch = false;
    stop_switch = false;
    time = 0;
    grade = 0;
    ui->progressBar->setVisible(false);
    ui->time_value->setText(" ");
    ui->grade_value->setText(" ");
    ui->stop_ptn->setEnabled(false);
    ui->end_btn->setEnabled(false);
    ui->start_btn->setEnabled(true);
    ui->setting_btn->setEnabled(true);
    ui->stop_ptn->setText("暂停");
    map->rebuildmap();
    repaint();
}

void mazeWidget::on_rule_btn_clicked() {
    QMessageBox::information(this, "游戏规则", "使用WASD/IJKL移动，计时200秒，完成越多得分越高。");
}

void mazeWidget::on_setting_btn_clicked() {
    QStringList levels = { "5阶迷宫", "10阶迷宫", "20阶迷宫", "40阶迷宫" };
    QString sel = QInputDialog::getItem(this, "选择难度", "请选择迷宫等级：", levels, 2, false);
    int level = 20;
    if (sel.startsWith("5")) level = 5;
    else if (sel.startsWith("10")) level = 10;
    else if (sel.startsWith("40")) level = 40;
    setDifficulty(level);
}

void mazeWidget::on_solve_btn_clicked() {
    solving_mode = true;                      // 进入自动求解模式（不加分）
    map->solve();                             // 显示路径
    repaint();

    // 5 秒后清除路径，重新生成地图（不加分）
    QTimer::singleShot(5000, this, [=]() {
        solving_mode = false;                 // 退出自动求解模式
        map->makemap();                       // 重新生成迷宫
        repaint();
        ui->solve_btn->setEnabled(true);      // 重新启用解决按钮
    });

    ui->solve_btn->setEnabled(false);         // 禁用按钮防止重复点击
}


void mazeWidget::startGameAuto() {
    ui->label->setVisible(false);
    painting_switch = true;
    keybord_switch = true;
    timing_switch = true;
    time = 200;
    timer->start(1000);
    animationTimer->start();
    ui->start_btn->setEnabled(false);
    ui->stop_ptn->setEnabled(true);
    ui->end_btn->setEnabled(true);
    ui->solve_btn->setEnabled(true);
    ui->setting_btn->setEnabled(false);
    ui->progressBar->setVisible(true);
    ui->progressBar->setValue(100);
    ui->time_value->setText(QString::number(time));
    ui->grade_value->setText(QString::number(grade));
    ui->plaque_time->setText("时间");
    ui->plaque_grade->setText("分数");
}
