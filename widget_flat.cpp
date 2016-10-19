#include "widget_flat.h"
#include <QGridLayout>
#include <QHeaderView>
#include <QSpacerItem>
FlatWidget::FlatWidget(QWidget *parent) :
    QWidget(parent)
{
    QString title;
    QStringList labels;
    title = "公式选择";
    labels << "eclert参考焓" << "eckert/spending" << "boeing";
    radioBox = new MyUsualRadioBox(title, labels, MyUsualRadioBox::Horizontal, this);
    radioBox->setObjectName("formulaRadio");
    connect(radioBox, &MyUsualRadioBox::radioToggle, this, &FlatWidget::changeWidgetByRadioBox);

    title = "壁面温度";
    labels.clear();
    labels << "用前一时刻" << "定温壁" ;
    radioBox2 = new MyUsualRadioBox(title, labels, MyUsualRadioBox::Horizontal, this);
    radioBox2->setRadioIndex(1);
    wallTemperatureEdit = new QLineEdit();
    radioBox2->insertWidgetWithButtonIndex(1, wallTemperatureEdit);
    radioBox2->setObjectName("temperatureRadio");
    connect(radioBox2, &MyUsualRadioBox::radioToggle, this, &FlatWidget::changeWidgetByRadioBox);

    title = "是否修正湍流开始位置";
    labels.clear();
    labels << "不修正" << "修正";
    radioBox3 = new MyUsualRadioBox(title, labels, MyUsualRadioBox::Horizontal, this);
    distanceEdit = new QLineEdit();
    distanceEdit->setEnabled(false);
    radioBox3->insertWidgetWithButtonIndex(1, distanceEdit);
    radioBox3->setRadioIndex(0);
    radioBox3->setObjectName("correctRadio");

    connect(radioBox3, &MyUsualRadioBox::radioToggle, this, &FlatWidget::changeWidgetByRadioBox);

    labels.clear();
    labels  << "迎风" << "背风";
    calPosRadio = new MyUsualRadioBox(tr("计算位置"), labels );

    title = "曼格勒因子";
    labels.clear();
    labels << "尖楔" << "尖锥";
    radioBox4 = new MyUsualRadioBox(title, labels, MyUsualRadioBox::Horizontal, this);

    labels.clear();
    labels << "是" << "否";
    thinRadio = new MyUsualRadioBox("是否稀薄", labels, MyUsualRadioBox::Horizontal,this);
    thinRadio->setRadioIndex(1);
    thinRadio->disable();

    title = "";
    labels.clear();
    labels << "路径长度(m):" << "发射率:";
    editBox = new GeneralEditBox(title, labels, 1, 2, this);
    editBox->setFixedHeight(Utils::windowSize().height() * 0.1);

    labels.clear();
    labels << "流动" << "压力(Pa)" << "角度(deg)";

    QGroupBox *tableBox = new QGroupBox("");
    QGridLayout *tableLayout = new QGridLayout();
    tableWidget = new QTableWidget;
    tableWidget->setRowCount(3);
    tableWidget->setColumnCount(4);
    tableWidget->setVerticalHeaderLabels(labels);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    combomBox2 = new QComboBox();
    combomBox2->addItem(tr("楔"));
    combomBox2->addItem(tr("锥"));
    combomBox2->addItem(tr("修正牛顿"));
    combomBox2->addItem(tr("普迈"));
    combomBox2->addItem(tr("输入Mc,Cp关系"));
    for(int i = 0; i < 4; i++)
    {
        combomBox1 = new QComboBox();
        combomBox1->addItem(tr("楔"));
        combomBox1->addItem(tr("锥"));
        tableWidget->setCellWidget(0, i, combomBox1);
    }
    for(int j = 0; j < 4; j++)
    {
        combomBox2 = new QComboBox();
        combomBox2->addItem(tr("楔"));
        combomBox2->addItem(tr("锥"));
        combomBox2->addItem(tr("修正牛顿"));
        combomBox2->addItem(tr("普迈"));
        combomBox2->addItem(tr("输入Mc,Cp关系"));
        tableWidget->setCellWidget(1, j, combomBox2);
    }

    materialLayer = new QComboBox();
    materialLayer->addItem(tr("1"));
    materialLayer->addItem(tr("2"));
    materialLayer->addItem(tr("3"));
    materialLayer->addItem(tr("4"));
    materialLayer->setCurrentIndex(3);

    materialLabel = new QLabel(tr("选择段数："));
    connect(materialLayer, SIGNAL(currentIndexChanged(int)), this, SLOT(changeTable(int)));

    tableLayout->addWidget(materialLabel,0, 0);
    tableLayout->addWidget(materialLayer,0, 1);
    tableLayout->addWidget(tableWidget,1, 0, 1, 4,Qt::AlignTop);
    tableBox->setLayout(tableLayout);
    tableWidget->setFixedHeight(Utils::windowSize().height() * 0.17);

    amplificationBox = new AmplificationFactorBox();
    transformRadioBox =  new TransformBox();

//    QSpacerItem *spaceItem = new QSpacerItem(Utils::windowSize().width() * 0.15 , 1);
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(radioBox, 0, 0, 1, 3);
    mainLayout->addWidget(editBox, 1, 0, 1, 3);
//    mainLayout->addWidget(materialLabel, 2, 0);
//    mainLayout->addWidget(materialLayer, 2, 1);
    mainLayout->addWidget(tableBox, 3, 0, 1, 3,Qt::AlignTop);
    mainLayout->addWidget(amplificationBox, 4, 0, 1, 4);
    mainLayout->addWidget(radioBox3, 5, 1, 1, 2);
    mainLayout->addWidget(radioBox4, 5, 0);
    mainLayout->addWidget(calPosRadio,4,4);
    mainLayout->addWidget(thinRadio, 5, 4);
    mainLayout->addWidget(radioBox2, 5, 3);
    mainLayout->addWidget(transformRadioBox, 6, 0, 1, 4);
//    mainLayout->addItem(spaceItem, 4,3);
    mainLayout->setRowStretch(7, 1);
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(1, 1);
    mainLayout->setColumnStretch(2, 1);
    mainLayout->setColumnStretch(3, 3);
    mainLayout->setColumnStretch(4, 1);
    mainLayout->setColumnStretch(5, 1);
    mainLayout->setSpacing(Utils::windowSize().width() * 0.01);
    this->setLayout(mainLayout);
}

FlatWidget::~FlatWidget()
{

}


void FlatWidget::changeWidgetByRadioBox(int index)
{
    MyUsualRadioBox *radioBox = qobject_cast<MyUsualRadioBox*>(sender());

    if (radioBox->objectName() == "formulaRadio") {
        if (index == 0 || index == 2) {
            thinRadio->setRadioIndex(-1);
            thinRadio->disable();
        } else {
            thinRadio->setRadioIndex(1);
            thinRadio->enable();
        }
    }  else if (radioBox->objectName() == "temperatureRadio") {
        if (index == 0) {
            wallTemperatureEdit->setText("");
            wallTemperatureEdit->setDisabled(true);
        } else {
            wallTemperatureEdit->setEnabled(true);
        }
    } else if (radioBox->objectName() == "correctRadio") {
            if (index == 0) {
                distanceEdit->setText("");
                distanceEdit->setDisabled(true);
            } else {
                distanceEdit->setEnabled(true);
            }
        }
}

void FlatWidget::changeTable(int index)
{
    for (int i = 0;i < tableWidget->rowCount();i++) {
        for (int j = 0;j < tableWidget->columnCount();j++) {
            bool isEnabled = j <= index ? true : false;
            QColor color = j <= index ? QColor("#FFFFFF") : QColor("#CCCCCC");
            Qt::ItemFlags flags = j <= index ? Qt::ItemIsEditable | Qt::ItemIsEnabled|Qt::ItemIsSelectable : Qt::NoItemFlags;
            if (i == 0 || i==1) {
                tableWidget->cellWidget(i, j)->setEnabled(isEnabled);
            } else {
                QTableWidgetItem *item = tableWidget->itemAt(i , j);

                if (!item) {
                    item = new QTableWidgetItem();

                    tableWidget->setItem( i, j, item);
                }
                item->setBackgroundColor(color);
                item->setFlags(flags);
            }
        }
    }
}

QString FlatWidget::getParameterData()
{
    return QString("atmos");
}
