#include "widget_ihcp_2.h"

#include <QWidget>
#include <QLabel>
#include <QGridLayout>

Widget_ihcp_2::Widget_ihcp_2(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *mainLayout = new QGridLayout(this);

    QStringList labels;
    labels << "内壁环境温度(K)" << "内壁对流换热系数"<<"外壁环境温度(K)"<<"外壁面辐射发射率"<<"内壁对流换热系数"<<"内壁环境辐射发射率"<<"外壁对流换热系数"<<"外壁环境辐射发射率";
    QString title = "";
    editBox = new GeneralEditBox(title, labels, 2, 4, this);
    editBox->setFixedHeight(Utils::windowSize().height() * 0.2);

    labels.clear();
    labels << "材料层数"<< "材料初始温度(K)"<< "迭代时间步"<< "某点坐标"<< "时间点";
    editBox2 = new GeneralEditBox(title, labels, 5, 1, this);
    editBox2->setFixedHeight(Utils::windowSize().height() * 0.25);



    labels.clear();
    labels << "内壁对流(仅选中时计算)" << "采用热壁热流计算(恢复焓为0)" << "采用冷壁热流和恢复焓计算";
    radioBox1 = new MyUsualRadioBox(title, labels, MyUsualRadioBox::Horizontal, this);

    labels.clear();
    labels << "采用热壁热流计算" << "采用...";
    title = "外壁热流(推荐)";
    radioBox2 = new MyUsualRadioBox(title, labels, MyUsualRadioBox::Horizontal,this);




    mainLayout->addWidget(editBox, 0, 0, 1, 2);
    mainLayout->addWidget(radioBox1, 1, 1);
    mainLayout->addWidget(radioBox2, 1, 0);
    mainLayout->addWidget(editBox2, 2, 0);
    mainLayout->setColumnStretch(0, 2);
    mainLayout->setColumnStretch(1, 5);
    mainLayout->setColumnStretch(2, 2);
    mainLayout->setRowStretch(3, 1);



    this->setLayout(mainLayout);
}

Widget_ihcp_2::~Widget_ihcp_2()
{

}

