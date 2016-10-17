#include "widget_cal_cylinder.h"
#include <QLayout>
#include <QGroupBox>
#include <QSpacerItem>
#include <QFrame>
CalCylinderWidget::CalCylinderWidget(QWidget *parent) :
    QWidget(parent)
{
    init();
}

CalCylinderWidget::~CalCylinderWidget()
{

}

void CalCylinderWidget::init()
{
    // init radioBoxs
    QStringList radioLabels;
    radioLabels <<  tr("BeckHh/Gallgher公式") <<  tr("Cato/Johnson") <<  tr("Boeing");
    formulaRadio = new MyUsualRadioBox(tr("公式选择"), radioLabels);
    formulaRadio->setObjectName("formulaRadio");
    connect(formulaRadio, &MyUsualRadioBox::radioToggle, this, &CalCylinderWidget::changeWidgetByRadioBox);

    radioLabels.clear();
    radioLabels <<  tr("是") <<  tr("否");
    thinRadio = new MyUsualRadioBox(tr("是否稀薄"), radioLabels);
    thinRadio->setRadioIndex(1);

    radioLabels.clear();
    radioLabels <<  tr("程序自动计算") <<  tr("给定数值");
    lewisRadio = new MyUsualRadioBox(tr("Lewis数计算方法"), radioLabels);
    lewisRadio->setObjectName("lewisRadio");
    lewisEdit = new QLineEdit();
    lewisEdit->setEnabled(false);

    lewisRadio->insertWidgetWithButtonIndex(1, lewisEdit);
    connect(lewisRadio, &MyUsualRadioBox::radioToggle, this, &CalCylinderWidget::changeWidgetByRadioBox);

    radioLabels.clear();
    radioLabels <<  tr("不考虑舵面反角") <<  tr("考虑(水平舵)") <<  tr("考虑(下垂直)") <<  tr("考虑(上垂直)");
    rudderRadio = new MyUsualRadioBox(tr("是否考虑舵面反角"), radioLabels);


    radioLabels.clear();
    radioLabels <<  tr("在子午面") <<  tr("非子午面(水平)") <<  tr("非子午面(垂直)");
    planeRadio = new MyUsualRadioBox(tr("是否在子午面"), radioLabels);
    planeRadio->setVisible(false);

    radioLabels.clear();
    radioLabels << "迎风" << "背风";
    calPosRadio = new MyUsualRadioBox(tr("计算位置"), radioLabels);

    radioLabels.clear();
    radioLabels << tr("前一时刻") << tr("定壁温");
    temperatureRadio = new MyUsualRadioBox(tr("壁温"), radioLabels);
    temperatureRadio->setRadioIndex(1);
    temperatureRadio->setObjectName("temperatureRadio");
    wallTemperatureEdit = new QLineEdit();
    temperatureRadio->insertWidgetWithButtonIndex(1, wallTemperatureEdit);
    connect(temperatureRadio, &MyUsualRadioBox::radioToggle, this, &CalCylinderWidget::changeWidgetByRadioBox);

    amplificationBox = new AmplificationFactorBox();
    transformRadioBox = new TransformBox();
    QStringList labels;
    labels << "半径(m):" << "后掠角:";
    editBox = new GeneralEditBox("", labels, 1, 2, this);
    editBox->setFixedHeight(Utils::windowSize().height() * 0.1);
//    QSpacerItem *spaceItem = new QSpacerItem(Utils::windowSize().width() * 0.2 , 1);

    // mainLayout
    QGridLayout *mainLayout = new QGridLayout();

    mainLayout->addWidget(formulaRadio, 0, 0);
    mainLayout->addWidget(amplificationBox, 1, 0, 1, 2);
    mainLayout->addWidget(editBox, 2, 0);
    mainLayout->addWidget(calPosRadio, 2, 1);
    mainLayout->addWidget(temperatureRadio, 2, 2);
    mainLayout->addWidget(rudderRadio, 3, 0);
    mainLayout->addWidget(planeRadio, 3, 0);
    mainLayout->addWidget(lewisRadio, 3, 2);
    mainLayout->addWidget(thinRadio, 3, 1);
    mainLayout->addWidget(transformRadioBox, 4, 0, 1, 3, Qt::AlignTop);
//    mainLayout->addItem(spaceItem, 3, 3);
    mainLayout->setRowStretch(5, 1);
    mainLayout->setColumnStretch(0, 3);
    mainLayout->setColumnStretch(1, 1);
    mainLayout->setColumnStretch(2, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->setSpacing(Utils::windowSize().width() * 0.01);

    this->setLayout(mainLayout);
}

void CalCylinderWidget::changeWidgetByRadioBox(int index)
{
    MyUsualRadioBox *radioBox = qobject_cast<MyUsualRadioBox*>(sender());

    if (radioBox->objectName() == "formulaRadio") {
        if (index == 0) {
            rudderRadio->setVisible(true);
            planeRadio->setVisible(false);
            thinRadio->setRadioIndex(-1);
            thinRadio->disable();
        } else {
            rudderRadio->setVisible(false);
            planeRadio->setVisible(true);
            thinRadio->setRadioIndex(1);
            thinRadio->enable();
        }
    } else if (radioBox->objectName() == "lewisRadio") {
        if (index == 0) {
            lewisEdit->setText("");
            lewisEdit->setDisabled(true);
        } else {
            lewisEdit->setEnabled(true);
        }
    }
}

QString CalCylinderWidget::getParameterData()
{
    return QString("atmos");
}
