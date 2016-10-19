#include "widget_mulpoint.h"
#include <QGridLayout>
#include <QLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QHeaderView>

MulPointWidget::MulPointWidget(QWidget *parent) :
    QWidget(parent)
{
    init();
}

void MulPointWidget::init()
{
    //init all Qmembers
    QGridLayout *mainLayout = new QGridLayout();

    geometryLabel = new QLabel(tr("几何结构:"));
    calNumLabel = new QLabel(tr("计算段数:"));
    frontRadiusLabel = new QLabel(tr("前缘半径(m):"));
    geometryFileButton = new QPushButton(tr("打开文件:"));

    calNumBox = new QComboBox();
    QStringList labels;
    labels << "1" << "2" << "3" << "4";
    calNumBox->addItems(labels);
    calNumBox->setCurrentIndex(3);
    connect(calNumBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeTable(int)));

    frontRadiusEdit = new QLineEdit(this);

    transformRadioBox = new TransformBox();
    amplificationBox = new AmplificationFactorBox();
    resultGraph = new QGraphicsView();
    //setting all qradiobox
    QStringList radioLabels;
    radioLabels << "二维圆柱" << "三维球头";
    frontStructRadio = new MyUsualRadioBox(tr("前缘结构"), radioLabels);
    radioLabels.clear();
    radioLabels << "迎风" << "背风";
    calPosRadio = new MyUsualRadioBox(tr("计算位置"), radioLabels);
    radioLabels.clear();
    radioLabels << "eebert参考系" << "eebert-spending";
    thermalFlowCalRadio = new MyUsualRadioBox(tr("热流计算方法"), radioLabels);
    radioLabels.clear();
    radioLabels << "尖楔" << "尖锥";
    luoTransFactorRadio = new MyUsualRadioBox(tr("罗格勒变换因子"), radioLabels);
    radioLabels.clear();
    radioLabels << "是" << "否";
    ifUsingFlowRadio = new MyUsualRadioBox(tr("是否使用湍流开始位置"), radioLabels);
    radioLabels.clear();
    radioLabels << tr("前一时刻") << tr("定壁温");
    temperatureRadio = new MyUsualRadioBox(tr("壁温"), radioLabels);
    temperatureRadio->setRadioIndex(1);
    temperatureRadio->setObjectName("temperatureRadio");
    wallTemperatureEdit = new QLineEdit();
    temperatureRadio->insertWidgetWithButtonIndex(1, wallTemperatureEdit);
    connect(temperatureRadio, &MyUsualRadioBox::radioToggle, this, &MulPointWidget::changeWidgetByRadioBox);

    QGroupBox *tableBox = new QGroupBox("");
    QHBoxLayout *tableLayout = new QHBoxLayout();
    tableSettingWidget = new QTableWidget(this);
    tableSettingWidget->setRowCount(4);
    tableSettingWidget->setColumnCount(5);
    QStringList tableHeader;
    tableHeader << "长度(m)" << "角度(deg)" << "计算点数" << "流动设置" << "压力设置";
    tableSettingWidget->setHorizontalHeaderLabels(tableHeader);
    tableSettingWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableSettingWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableLayout->addWidget(tableSettingWidget,0,Qt::AlignTop);
    tableBox->setLayout(tableLayout);
    tableSettingWidget->setFixedHeight(Utils::windowSize().height() * 0.3);

    for(int i = 0; i < 4; i++) {
        QComboBox *combomBox = new QComboBox();
        combomBox->addItem(tr("楔"));
        combomBox->addItem(tr("锥"));
        tableSettingWidget->setCellWidget(i, 3, combomBox);
    }
    for(int i = 0; i < 4; i++) {
        QComboBox * combomBox = new QComboBox();
        combomBox->addItem(tr("楔"));
        combomBox->addItem(tr("锥"));
        combomBox->addItem(tr("修正牛顿"));
        tableSettingWidget->setCellWidget(i, 4, combomBox);
    }

    QGroupBox *group = new QGroupBox();
    QGridLayout *groupLayout = new QGridLayout();
    groupLayout->addWidget(geometryLabel, 0, 0);
    groupLayout->addWidget(geometryFileButton, 0 ,1);
    groupLayout->addWidget(calNumLabel, 0, 2);
    groupLayout->addWidget(calNumBox, 0, 3);
    groupLayout->addWidget(frontStructRadio, 1, 0, 1, 2);
    groupLayout->addWidget(frontRadiusLabel, 1, 2);
    groupLayout->addWidget(frontRadiusEdit, 1, 3);
    group->setLayout(groupLayout);
    group->setFixedHeight(Utils::windowSize().height() * 0.2);

    //setting layout

    mainLayout->addWidget(group, 0, 0, 1, 2);
    mainLayout->addWidget(tableBox, 1, 0, 1, 3, Qt::AlignTop);
    mainLayout->addWidget(amplificationBox, 2, 0, 1, 3);
    mainLayout->addWidget(resultGraph, 1, 3, 2, 2);
    mainLayout->addWidget(calPosRadio, 3, 0);
    mainLayout->addWidget(thermalFlowCalRadio, 3, 1);
    mainLayout->addWidget(luoTransFactorRadio, 3, 2);
    mainLayout->addWidget(temperatureRadio, 3, 3);
    mainLayout->addWidget(transformRadioBox, 4, 0, 1, 4);
    mainLayout->setRowStretch(5, 1);
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(1, 1);
    mainLayout->setColumnStretch(2, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->setColumnStretch(4, 1);
//    mainLayout->setSpacing(Utils::windowSize().width() * 0.01);
    this->setLayout(mainLayout);


}

MulPointWidget::~MulPointWidget()
{

}

void MulPointWidget::changeTable(int index)
{
    for (int i = 0;i < tableSettingWidget->rowCount();i++) {
        for (int j = 0;j < tableSettingWidget->columnCount();j++) {
            bool isEnabled = i <= index ? true : false;
            QColor color = i <= index ? QColor("#FFFFFF") : QColor("#CCCCCC");
            Qt::ItemFlags flags = i <= index ? Qt::ItemIsEditable | Qt::ItemIsEnabled|Qt::ItemIsSelectable : Qt::NoItemFlags;
            if (j == 3 || j == 4) {
                tableSettingWidget->cellWidget(i, j)->setEnabled(isEnabled);
            } else if (i != 0) {
                QTableWidgetItem *item = tableSettingWidget->itemAt(i , j);

                if (!item) {
                    item = new QTableWidgetItem();

                    tableSettingWidget->setItem( i, j, item);
                }
                item->setBackgroundColor(color);
                item->setFlags(flags);
            }
        }
    }
}

void MulPointWidget::changeWidgetByRadioBox(int index)
{
    MyUsualRadioBox *radioBox = qobject_cast<MyUsualRadioBox*>(sender());

    if (radioBox->objectName() == "temperatureRadio") {
        if (index == 0) {
            wallTemperatureEdit->setText("");
            wallTemperatureEdit->setDisabled(true);
        } else {
            wallTemperatureEdit->setEnabled(true);
        }
    }
}

QString MulPointWidget::getParameterData()
{
    return QString("atmos");
}
