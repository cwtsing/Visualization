#include "widget_flight.h"
#include "QHeaderView"
FlightWidget::FlightWidget(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *mainLayout = new QGridLayout();

    QStringList labels;
    labels << "时间点:" << "起始时间:"<<"终止时间:"<<"间隙:" \
           << "时间点:" << "起始时间:"<<"终止时间:"<<"间隙:" \
           << "时间点:" << "起始时间:"<<"终止时间:"<<"间隙:" ;


    timeEditBox = new GeneralEditBox("", labels, 3, 4, this);
//    timeEditBox->setFixedHeight(Utils::windowSize().height() * 0.3);
    timeEditBox->setFixedHeight(Utils::windowSize().height() * 0.4);
    timeEditBox->setFixedWidth(Utils::windowSize().width()*0.8);

    tableWidget = new QTableWidget(4, 5);
    labels.clear();
    labels << "时间(s)" << "高度(m)" << "速度(m/s)" << "攻角(deg)" << "侧滑角(deg)";
    tableWidget->setHorizontalHeaderLabels(labels);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setFixedHeight(Utils::windowSize().height() * 0.4);

//    saveButton = new QPushButton(tr("保存"), this);
//    saveButton->setFixedSize(Utils::largeButtonSize());
//    loadButton = new QPushButton(tr("载入文件"), this);
//    loadButton->setFixedSize(Utils::largeButtonSize());

    QGroupBox *groupBox= new QGroupBox(tr("飞行数据"));
    QGridLayout *groupLayout=new QGridLayout();

    textEdit = new QTextEdit();
    groupLayout->addWidget(textEdit, 0, 0);
    groupBox->setLayout(groupLayout);

    mainLayout->addWidget(timeEditBox, 0, 0);
    mainLayout->addWidget(groupBox, 1, 0);
//    mainLayout->addWidget(saveButton, 3, 0);
//    mainLayout->addWidget(loadButton, 3, 1);

//    mainLayout->setRowStretch(0, 3);
    mainLayout->setRowStretch(2, 1);
    mainLayout->setColumnStretch(0, 7);
    mainLayout->setColumnStretch(1, 3);
//    mainLayout->setColumnStretch(2, 3);
//    mainLayout->setColumnStretch(3, 3);
    this->setLayout(mainLayout);
}

FlightWidget::~FlightWidget()
{

}

QString FlightWidget::getParameterData()
{
    return QString("flight");
}
