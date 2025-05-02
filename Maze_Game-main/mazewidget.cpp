#include "mazewidget.h"
#include "ui_mazewidget.h"

mazeWidget::mazeWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::mazeWidget), map(new maze(20))
    , painting_switch(false), timing_switch(false)
    , keybord_switch(false), stop_switch(false), grade(0), time(0)
    , currentFrameIndex(0), direction(1) {  // 默认向下

    ui->setupUi(this);
    setWindowTitle("迷宫游戏"); // 设置窗口标题
    setFixedSize(800, 600); // 设置固定大小
    hide(); // 启动时不显示，由 StartScreen 负责控制显示

    ui->progressBar->setVisible(false);                 //初始隐藏进度条
    ui->end_btn->setEnabled(false);                     //设置终止按钮禁用
    ui->stop_ptn->setEnabled(false);                    //设置暂停按钮禁用
    ui->grade_value->setText("  ");                     //设置分数值显示为空
    ui->time_value->setText("  ");                      //设置时间值显示为空

    map->makemap();                                     //生成地图

    timer = new QTimer(this);                           //初始化游戏计时器
    connect(timer, &QTimer::timeout, this, &mazeWidget::time_update);   //链接时间更新信号与槽

    animationTimer = new QTimer(this);                  //初始化动画计时器
    animationTimer->setInterval(200);                   //设置动画速度 (200ms)
    connect(animationTimer, &QTimer::timeout, this, &mazeWidget::dogAnimationUpdate);

    ui->plaque_time->setText("  ");
    ui->plaque_grade->setText("  ");
    ui->label->setVisible(true);
    ui->solve_btn->setEnabled(false);

    // 加载狗的动画
    loadDogAnimations();
}

void mazeWidget::loadDogAnimations() {
    // 加载向上走的动画帧
    QPixmap up1(":/sprites/dog_up1.png");
    QPixmap up2(":/sprites/dog_up2.png");
    if (up1.isNull() || up2.isNull()) {
        qDebug() << "❌ 狗向上动画帧加载失败！";
    } else {
        dogUpFrames.append(up1);
        dogUpFrames.append(up2);
    }

    // 加载向下走的动画帧
    QPixmap down1(":/sprites/dog_down1.png");
    QPixmap down2(":/sprites/dog_down2.png");
    if (down1.isNull() || down2.isNull()) {
        qDebug() << "❌ 狗向下动画帧加载失败！";
    } else {
        dogDownFrames.append(down1);
        dogDownFrames.append(down2);
    }

    // 加载向左走的动画帧
    QPixmap left1(":/sprites/dog_left1.png");
    QPixmap left2(":/sprites/dog_left2.png");
    if (left1.isNull() || left2.isNull()) {
        qDebug() << "❌ 狗向左动画帧加载失败！";
    } else {
        dogLeftFrames.append(left1);
        dogLeftFrames.append(left2);
    }

    // 加载向右走的动画帧
    QPixmap right1(":/sprites/dog_right1.png");
    QPixmap right2(":/sprites/dog_right2.png");
    if (right1.isNull() || right2.isNull()) {
        qDebug() << "❌ 狗向右动画帧加载失败！";
    } else {
        dogRightFrames.append(right1);
        dogRightFrames.append(right2);
    }

    // 设置初始动画帧
    if (!dogDownFrames.isEmpty()) {
        currentDogFrame = dogDownFrames.first();
    }
}

void mazeWidget::dogAnimationUpdate() {
    // 更新当前动画帧
    currentFrameIndex = (currentFrameIndex + 1) % 2; // 在0和1之间循环

    // 根据方向选择对应的动画帧
    switch (direction) {
    case 0: // 上
        if (!dogUpFrames.isEmpty()) {
            currentDogFrame = dogUpFrames[currentFrameIndex];
        }
        break;
    case 1: // 下
        if (!dogDownFrames.isEmpty()) {
            currentDogFrame = dogDownFrames[currentFrameIndex];
        }
        break;
    case 2: // 左
        if (!dogLeftFrames.isEmpty()) {
            currentDogFrame = dogLeftFrames[currentFrameIndex];
        }
        break;
    case 3: // 右
        if (!dogRightFrames.isEmpty()) {
            currentDogFrame = dogRightFrames[currentFrameIndex];
        }
        break;
    }

    // 重画界面以显示新的动画帧
    repaint();
}

mazeWidget::~mazeWidget(){
    delete ui;
    delete map;
    delete timer;
    delete animationTimer;
}

void mazeWidget::setDifficulty(int difficulty) {
    if (map) {
        delete map;  // 释放旧迷宫
    }
    map = new maze(difficulty); // 重新创建迷宫
    map->makemap();
    repaint();
}



/*void mazeWidget::paintEvent(QPaintEvent*) {
    if (!painting_switch) return;

    QPainter painter(this);

    // 设置黑色背景
    painter.fillRect(rect(), Qt::black);

    // 加载图案资源
    QPixmap brick(":/tiles/brick.png");
    QPixmap paw(":/assets/paw.png");
    QPixmap flag(":/assets/flag.png");

    int side = map->getside();
    int perblock = (std::min(ui->frame->width(), ui->frame->height()) - 20) / side;
    int start_x = ui->frame->x() + (ui->frame->width() - side * perblock) / 2;
    int start_y = ui->frame->y() + (ui->frame->height() - side * perblock) / 2;

    for (int i = 0; i < side; ++i) {
        for (int j = 0; j < side; ++j) {
            QRect block(start_x + i * perblock, start_y + j * perblock, perblock, perblock);
            int val = map->getmap()[i][j];

            //  优先判断是否是玩家当前所在位置（即起点）
            if (i == map->p_x && j == map->p_y) {
                if (!currentDogFrame.isNull()) {
                    painter.drawPixmap(block, currentDogFrame.scaled(perblock, perblock, Qt::KeepAspectRatio));
                } else {
                    painter.fillRect(block, Qt::red);
                }
                continue;
            }

            //  最外圈统一绘制为砖块墙（除非是起点）
            if (i == 0 || j == 0 || i == side - 1 || j == side - 1) {
                if (!brick.isNull())
                    painter.drawPixmap(block, brick.scaled(perblock, perblock));
                else
                    painter.fillRect(block, Qt::darkGray);
                continue;
            }

            if (val == 7) {
                // 小狗走过的路径
                if (!paw.isNull())
                    painter.drawPixmap(block, paw.scaled(perblock, perblock));
                else
                    painter.fillRect(block, Qt::yellow);
            } else if (val == 6) {
                // 终点（小红旗）
                if (!flag.isNull())
                    painter.drawPixmap(block, flag.scaled(perblock, perblock));
                else
                    painter.fillRect(block, Qt::green);
            } else if (val == 3 || val == 4) {
                painter.fillRect(block, Qt::white);  // 可走路径
            } else {
                // 墙体砖块
                if (!brick.isNull())
                    painter.drawPixmap(block, brick.scaled(perblock, perblock));
                else
                    painter.fillRect(block, Qt::gray);
            }
        }
    }
}*/

/*void mazeWidget::paintEvent(QPaintEvent*) {
    if (!painting_switch) return;

    QPainter painter(this);

    // 设置绿草背景
    QPixmap background(":/assets/grass.png"); // 你上传的绿草背景图
    if (!background.isNull()) {
        painter.drawPixmap(rect(), background);
    } else {
        painter.fillRect(rect(), Qt::black); // 备用背景
        qDebug() << "❌ grass.png 加载失败！";
    }

    // 加载砖块图、小狗动画帧、爪印图、终点红旗图
    QPixmap brick(":/tiles/brick.png");
    QPixmap paw(":/assets/paw.png");
    QPixmap flag(":/assets/flag.png");

    int perblock = (std::min(ui->frame->width(), ui->frame->height()) - 20) / map->getside();
    int start_x = ui->frame->x() + (ui->frame->width() - map->getside() * perblock) / 2;
    int start_y = ui->frame->y() + (ui->frame->height() - map->getside() * perblock) / 2;

    for (int i = 0; i < map->getlevel() * 2 + 1; i++) {
        for (int j = 0; j < map->getlevel() * 2 + 1; j++) {
            QRect block(start_x + i * perblock, start_y + j * perblock, perblock, perblock);
            int val = map->getmap()[i][j];

            // 角色位置
            if (i == map->p_x && j == map->p_y) {
                if (!currentDogFrame.isNull()) {
                    QPixmap scaled = currentDogFrame.scaled(perblock, perblock, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    painter.drawPixmap(block, scaled);
                } else {
                    painter.fillRect(block, Qt::red);
                }
                continue; // 不再继续判断其他图层
            }

            // 砖块墙体（含边框与障碍）
            if (val == 0 || val == 1 || val == 2) {
                if (!brick.isNull())
                    painter.drawPixmap(block, brick.scaled(perblock, perblock));
                else
                    painter.fillRect(block, Qt::darkGray);
            }
            // 小狗走过的路径
            else if (val == 7) {
                if (!paw.isNull())
                    painter.drawPixmap(block, paw.scaled(perblock, perblock));
                else
                    painter.fillRect(block, Qt::yellow);
            }
            // 终点旗帜
            else if (val == 6) {
                if (!flag.isNull())
                    painter.drawPixmap(block, flag.scaled(perblock, perblock));
                else
                    painter.fillRect(block, Qt::green);
            }
            // 可走路径
            else if (val == 3 || val == 4) {
                painter.fillRect(block, Qt::white);
            }
        }
    }
}*/

void mazeWidget::paintEvent(QPaintEvent*) {
    if (!painting_switch) return;

    QPainter painter(this);

    // 加载背景图
    QPixmap grass(":/assets/grass.png");
    if (!grass.isNull()) {
        painter.drawPixmap(rect(), grass.scaled(size()));
    } else {
        painter.fillRect(rect(), Qt::black);
    }

    QPixmap brick(":/tiles/brick.png");
    QPixmap paw(":/assets/paw.png");
    QPixmap flag(":/assets/flag.png");

    int perblock = (std::min(ui->frame->width(), ui->frame->height()) - 20) / map->getside();
    int start_x = ui->frame->x() + (ui->frame->width() - map->getside() * perblock) / 2;
    int start_y = ui->frame->y() + (ui->frame->height() - map->getside() * perblock) / 2;

    for (int i = 0; i < map->getlevel() * 2 + 1; i++) {
        for (int j = 0; j < map->getlevel() * 2 + 1; j++) {
            QRect block(start_x + i * perblock, start_y + j * perblock, perblock, perblock);
            int val = map->getmap()[i][j];

            if (i == map->p_x && j == map->p_y) {
                // 小狗当前所在格子
                if (!currentDogFrame.isNull()) {
                    QPixmap scaledDog = currentDogFrame.scaled(perblock, perblock, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    painter.drawPixmap(block, scaledDog);
                } else {
                    painter.fillRect(block, Qt::red);
                }
            } else if (val == 7) {
                // 爪子足迹
                if (!paw.isNull())
                    painter.drawPixmap(block, paw.scaled(perblock, perblock, Qt::KeepAspectRatio));
                else
                    painter.fillRect(block, Qt::yellow);
            } else if (val == 6) {
                // 终点红旗
                if (!flag.isNull())
                    painter.drawPixmap(block, flag.scaled(perblock, perblock, Qt::KeepAspectRatio));
                else
                    painter.fillRect(block, Qt::green);
            } else if (val == 3 || val == 4) {
                // 白色路径
                painter.fillRect(block, Qt::white);
            } else {
                // 墙体砖块
                if (!brick.isNull())
                    painter.drawPixmap(block, brick.scaled(perblock, perblock));
                else
                    painter.fillRect(block, Qt::darkGray);
            }
        }
    }
}


void mazeWidget::keyPressEvent(QKeyEvent* event) {
    if (!keybord_switch) return;

    int x = map->p_x;
    int y = map->p_y;

    bool moved = false;

    // 键盘移动逻辑：
    if (event->key() == Qt::Key_I || event->key() == Qt::Key_W) {
        // 向上移动
        if ((*map)[x][y - 1] == 3 || (*map)[x][y - 1] == 4 || (*map)[x][y - 1] == 5 || (*map)[x][y - 1] == 6 || (*map)[x][y - 1] == 7) {
            map->p_y--;
            direction = 0; // 设置方向为上
            moved = true;
        }
    } else if (event->key() == Qt::Key_K || event->key() == Qt::Key_S) {
        // 向下移动
        if ((*map)[x][y + 1] == 3 || (*map)[x][y + 1] == 4 || (*map)[x][y + 1] == 5 || (*map)[x][y + 1] == 6 || (*map)[x][y + 1] == 7) {
            map->p_y++;
            direction = 1; // 设置方向为下
            moved = true;
        }
    } else if (event->key() == Qt::Key_J || event->key() == Qt::Key_A) {
        // 向左移动
        if ((*map)[x - 1][y] == 3 || (*map)[x - 1][y] == 4 || (*map)[x - 1][y] == 5 || (*map)[x - 1][y] == 6 || (*map)[x - 1][y] == 7) {
            map->p_x--;
            direction = 2; // 设置方向为左
            moved = true;
        }
    } else if (event->key() == Qt::Key_L || event->key() == Qt::Key_D) {
        // 向右移动
        if ((*map)[x + 1][y] == 3 || (*map)[x + 1][y] == 4 || (*map)[x + 1][y] == 5 || (*map)[x + 1][y] == 6 || (*map)[x + 1][y] == 7) {
            map->p_x++;
            direction = 3; // 设置方向为右
            moved = true;
        }
    }

    // 如果移动了，更新动画
    if (moved) {
        // 经过路径
        if ((*map)[map->p_x][map->p_y] != 5 && (*map)[map->p_x][map->p_y] != 6) {
            (*map)[map->p_x][map->p_y] = 7;
        }

        // 到达终点
        if ((*map)[map->p_x][map->p_y] == 6) {
            map->makemap();
            grade += pow(map->getlevel(), 2);
            ui->grade_value->setText(QString::number(grade));
        }

        // 更新动画帧并重绘
        dogAnimationUpdate();
    }
}

void mazeWidget::time_update() {
    if(time != 0) {
        //计时中
        time--;
        ui->time_value->setText(QString::number(time));
        ui->progressBar->setValue(time / 2);
    } else {
        timer->stop();                          //停止计时器
        animationTimer->stop();                 //停止动画计时器
        ui->progressBar->setVisible(false);     //隐藏进度条
        keybord_switch = false;                 //设置键盘响应、
        painting_switch = false;                //绘图响应、
        timing_switch = false;                  //计时响应为关闭状态
        repaint();                              //清除画布
        ui->start_btn->setEnabled(true);        //|
        ui->time_value->setText(" ");           //|
        ui->grade_value->setText(" ");          //|
        ui->stop_ptn->setEnabled(false);        //|设置各按钮与标签状态
        ui->end_btn->setEnabled(false);         //|
        ui->setting_btn->setEnabled(true);      //|
        //提示
        QMessageBox outgrade(QMessageBox::NoIcon, "恭喜", "您得分:" + QString::number(grade), QMessageBox::Ok);
        outgrade.exec();
        //分数重置
        grade = 0;
    }
}

void mazeWidget::resetGame() {
    // 重置游戏状态
    painting_switch = false;
    timing_switch = false;
    keybord_switch = false;
    stop_switch = false;
    grade = 0;
    time = 0;

    animationTimer->stop();   // 停止动画
    map->makemap();           // 重新生成迷宫

    ui->progressBar->setVisible(false);
    ui->end_btn->setEnabled(false);
    ui->stop_ptn->setEnabled(false);
    ui->grade_value->setText(" ");
    ui->time_value->setText(" ");
    ui->start_btn->setEnabled(true);
    ui->setting_btn->setEnabled(true);

    repaint(); // 重新绘制界面
}

void mazeWidget::on_start_btn_clicked() {
    ui->label->setVisible(false);
    ui->solve_btn->setEnabled(true);
    painting_switch = true;
    timing_switch = true;
    keybord_switch = true;
    time = 200;
    timer->start(1000);           // 启动游戏计时器
    animationTimer->start();      // 启动动画计时器
    ui->progressBar->setVisible(true);
    ui->progressBar->setValue(100);
    repaint();
    ui->time_value->setText(QString::number(time));
    ui->grade_value->setText(QString::number(grade));
    ui->start_btn->setEnabled(false);
    ui->stop_ptn->setEnabled(true);
    ui->end_btn->setEnabled(true);
    ui->setting_btn->setEnabled(false);
    ui->plaque_time->setText("时间");
    ui->plaque_grade->setText("分数");
}

void mazeWidget::on_stop_ptn_clicked() {
    if(stop_switch) {
        timing_switch = false;
        keybord_switch = false;
        timer->stop();
        animationTimer->stop();   // 暂停动画
        ui->stop_ptn->setText("继续");
        stop_switch = false;
    } else {
        timing_switch = true;
        keybord_switch = true;
        timer->start();
        animationTimer->start();  // 继续动画
        ui->stop_ptn->setText("暂停");
        stop_switch = true;
    }
}

void mazeWidget::on_end_btn_clicked() {
    timing_switch = false;
    painting_switch = false;
    keybord_switch = false;
    stop_switch = false;
    timer->stop();
    animationTimer->stop();       // 停止动画
    time = 0;
    grade = 0;
    ui->plaque_time->setText("  ");
    ui->plaque_grade->setText("  ");
    ui->progressBar->setVisible(false);
    ui->grade_value->setText(" ");
    ui->time_value->setText(" ");
    ui->stop_ptn->setText("暂停");
    ui->stop_ptn->setEnabled(false);
    ui->end_btn->setEnabled(false);
    ui->start_btn->setEnabled(true);
    ui->setting_btn->setEnabled(true);
    map->rebuildmap();
    ui->label->setVisible(true);
    ui->solve_btn->setEnabled(false);
    repaint();
}

void mazeWidget::on_rule_btn_clicked() {
    QMessageBox rule(QMessageBox::NoIcon, "规则", "计时200秒，根据迷宫等级与经过关卡记分。\n操作方式：WASD或者IJKL控制方向。", QMessageBox::Ok);
    rule.exec();
}

void mazeWidget::on_setting_btn_clicked() {
    QStringList difficultys;
    difficultys << tr("小朋友难度(5阶迷宫)") << tr("简单难度(10阶迷宫)") << tr("普通难度(20阶迷宫)") << tr("困难难度(40阶迷宫)");
    QString difficulty = QInputDialog::getItem(this, tr("选择难度"),
                                               tr("请选择一个条目"), difficultys, 0, false);
    if(difficulty == tr("小朋友难度(5阶迷宫)")) {
        delete map;
        map = new maze(5);
        map->makemap();
    } else if(difficulty == tr("简单难度(10阶迷宫)")) {
        delete map;
        map = new maze(10);
        map->makemap();
    } else if(difficulty == tr("普通难度(20阶迷宫)")) {
        delete map;
        map = new maze(20);
        map->makemap();
    } else if(difficulty == tr("困难难度(40阶迷宫)")) {
        delete map;
        map = new maze(40);
        map->makemap();
    }
}

void mazeWidget::on_solve_btn_clicked() {
    ui->solve_btn->setEnabled(false);
    map->solve();
    repaint();
    //停留10秒
    for(long long i=0;i<10000000000;i++);

    map->makemap();
    repaint();
    grade += pow(map->getlevel(), 2);
    ui->grade_value->setText(QString::number(grade));
    ui->solve_btn->setEnabled(true);
}


void mazeWidget::startGameAuto() {
    ui->label->setVisible(false);
    ui->solve_btn->setEnabled(true);
    painting_switch = true;
    timing_switch = true;
    keybord_switch = true;
    time = 200;
    timer->start(1000);
    animationTimer->start();      // 启动动画计时器
    ui->progressBar->setVisible(true);
    ui->progressBar->setValue(100);
    repaint();
    ui->time_value->setText(QString::number(time));
    ui->grade_value->setText(QString::number(grade));
    ui->start_btn->setEnabled(false);
    ui->stop_ptn->setEnabled(true);  //  启用暂停按钮
    ui->end_btn->setEnabled(true);
    ui->setting_btn->setEnabled(false);
    ui->label->setVisible(false);
    ui->plaque_time->setText("时间");
    ui->plaque_grade->setText("分数");
}
