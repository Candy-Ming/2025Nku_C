/********************************************************************************
** Form generated from reading UI file 'mazewidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAZEWIDGET_H
#define UI_MAZEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mazeWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QLabel *label;
    QProgressBar *progressBar;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *plaque;
    QPushButton *start_btn;
    QPushButton *stop_ptn;
    QPushButton *end_btn;
    QPushButton *rule_btn;
    QPushButton *setting_btn;
    QPushButton *solve_btn;
    QSpacerItem *verticalSpacer_2;
    QLabel *plaque_time;
    QLabel *time_value;
    QLabel *plaque_grade;
    QLabel *grade_value;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *mazeWidget)
    {
        if (mazeWidget->objectName().isEmpty())
            mazeWidget->setObjectName("mazeWidget");
        mazeWidget->resize(831, 678);
        QFont font;
        font.setPointSize(14);
        mazeWidget->setFont(font);
        horizontalLayout = new QHBoxLayout(mazeWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        frame = new QFrame(mazeWidget);
        frame->setObjectName("frame");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 701, 621));
        label->setPixmap(QPixmap(QString::fromUtf8("../../1/\350\203\214\346\231\257.jpg")));
        label->setScaledContents(true);
        label->setWordWrap(false);

        verticalLayout_2->addWidget(frame);

        progressBar = new QProgressBar(mazeWidget);
        progressBar->setObjectName("progressBar");
        progressBar->setValue(24);
        progressBar->setTextVisible(false);

        verticalLayout_2->addWidget(progressBar);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        plaque = new QLabel(mazeWidget);
        plaque->setObjectName("plaque");
        plaque->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(plaque);

        start_btn = new QPushButton(mazeWidget);
        start_btn->setObjectName("start_btn");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Microsoft YaHei")});
        font1.setPointSize(14);
        start_btn->setFont(font1);

        verticalLayout->addWidget(start_btn);

        stop_ptn = new QPushButton(mazeWidget);
        stop_ptn->setObjectName("stop_ptn");
        stop_ptn->setEnabled(false);

        verticalLayout->addWidget(stop_ptn);

        end_btn = new QPushButton(mazeWidget);
        end_btn->setObjectName("end_btn");
        end_btn->setEnabled(false);

        verticalLayout->addWidget(end_btn);

        rule_btn = new QPushButton(mazeWidget);
        rule_btn->setObjectName("rule_btn");

        verticalLayout->addWidget(rule_btn);

        setting_btn = new QPushButton(mazeWidget);
        setting_btn->setObjectName("setting_btn");

        verticalLayout->addWidget(setting_btn);

        solve_btn = new QPushButton(mazeWidget);
        solve_btn->setObjectName("solve_btn");

        verticalLayout->addWidget(solve_btn);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        plaque_time = new QLabel(mazeWidget);
        plaque_time->setObjectName("plaque_time");
        plaque_time->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(plaque_time);

        time_value = new QLabel(mazeWidget);
        time_value->setObjectName("time_value");
        time_value->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(time_value);

        plaque_grade = new QLabel(mazeWidget);
        plaque_grade->setObjectName("plaque_grade");
        plaque_grade->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(plaque_grade);

        grade_value = new QLabel(mazeWidget);
        grade_value->setObjectName("grade_value");
        grade_value->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(grade_value);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(mazeWidget);

        QMetaObject::connectSlotsByName(mazeWidget);
    } // setupUi

    void retranslateUi(QWidget *mazeWidget)
    {
        mazeWidget->setWindowTitle(QCoreApplication::translate("mazeWidget", "mazeWidget", nullptr));
        label->setText(QString());
        plaque->setText(QCoreApplication::translate("mazeWidget", "\350\277\267\345\256\253\346\270\270\346\210\217", nullptr));
        start_btn->setText(QCoreApplication::translate("mazeWidget", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        stop_ptn->setText(QCoreApplication::translate("mazeWidget", "\346\232\202\345\201\234", nullptr));
        end_btn->setText(QCoreApplication::translate("mazeWidget", "\347\273\210\346\255\242\346\270\270\346\210\217", nullptr));
        rule_btn->setText(QCoreApplication::translate("mazeWidget", "\350\247\204\345\210\231", nullptr));
        setting_btn->setText(QCoreApplication::translate("mazeWidget", "\350\256\276\347\275\256", nullptr));
        solve_btn->setText(QCoreApplication::translate("mazeWidget", "\350\247\243\345\206\263", nullptr));
        plaque_time->setText(QCoreApplication::translate("mazeWidget", "\346\227\266\351\227\264\357\274\232", nullptr));
        time_value->setText(QCoreApplication::translate("mazeWidget", "0", nullptr));
        plaque_grade->setText(QCoreApplication::translate("mazeWidget", "\345\210\206\346\225\260\357\274\232", nullptr));
        grade_value->setText(QCoreApplication::translate("mazeWidget", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mazeWidget: public Ui_mazeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAZEWIDGET_H
