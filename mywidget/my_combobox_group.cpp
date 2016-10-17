#include "mywidget/my_combobox_group.h"
#include <QLayout>
comboBoxGroupBox::comboBoxGroupBox(const QString &groupTitle, QWidget *parent) :
    QGroupBox(groupTitle, parent)
{

}

void comboBoxGroupBox::init(const QStringList &comboLabels, const QStringList &contentLabels)
{
    QHBoxLayout *transformLayout = new QHBoxLayout();

    comboBox = new QComboBox();

    comboBox->addItems(comboLabels);
    comboBox->setCurrentIndex(0);
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeTransform(int)));

    comboBoxLabel = new QLabel(contentLabels[0]);
    firstLabel = new QLabel(contentLabels[1]);
    secondLabel = new QLabel(contentLabels[2]);
    firstEdit = new QLineEdit();
    secondEdit = new QLineEdit();
    button = new QPushButton(tr("载入"));
    button->setVisible(false);

    transformLayout->addWidget(comboBoxLabel);
    transformLayout->addWidget(comboBox);
    transformLayout->addWidget(firstLabel);
    transformLayout->addWidget(firstEdit);
    transformLayout->addWidget(secondLabel);
    transformLayout->addWidget(secondEdit);
    transformLayout->addWidget(button);
    transformLayout->addStretch();
    transformLayout->setSpacing(10);

    this->setLayout(transformLayout);
    this->setFixedHeight(Utils::windowSize().height() * 0.1);
}

comboBoxGroupBox::~comboBoxGroupBox()
{

}

void comboBoxGroupBox::setTransformIndex(int index)
{
    comboBox->setCurrentIndex(index);
}

int comboBoxGroupBox::transformIndex()
{
    return comboBox->currentIndex();
}

void comboBoxGroupBox::enable()
{
    comboBox->setEnabled(true);
    firstLabel->setVisible(true);
    firstEdit->setVisible(true);
}

void comboBoxGroupBox::disable()
{
    comboBox->setDisabled(true);
    firstLabel->setVisible(false);
    firstEdit->setVisible(false);

}
TransformBox::TransformBox(const QString &groupTitle, QWidget *parent) :
    comboBoxGroupBox(groupTitle, parent)
{
    QStringList transformLables;
    transformLables << "层流到湍流的时间控制" << "湍流到层流的时间控制" << "当地Rel判断" << \
                       "当地动量厚度Rel" << "基于参数" << "参数ρ转换程序计算" << \
                       "程序通过Me取转换雷诺数ReTR" << "REQ" << "指定湍流程度";
    QStringList contentLables;
    contentLables << "转捩准则:" << "转换开始时间:" << "完成时间:";
    init(transformLables, contentLables);
}


void TransformBox::changeTransform(int index)
{
    switch (index) {
    case 0:
    case 1:
        firstLabel->setText(tr("转换开始时间:"));
        secondLabel->setVisible(true);
        secondLabel->setText(tr("完成时间:"));
        secondEdit->setVisible(true);
        break;
    case 2:
    case 3:
    case 4:
        firstLabel->setText(tr("转换起始:"));
        secondLabel->setVisible(true);
        secondLabel->setText(tr("完全湍流:"));
        secondEdit->setVisible(true);
        break;
    case 5:
    case 6:
        firstLabel->setText(tr("Ratio:"));
        secondLabel->setVisible(false);
        secondEdit->setVisible(false);
        break;
    case 7:
        firstLabel->setText(tr("转换起始:"));
        secondLabel->setVisible(true);
        secondLabel->setText(tr("湍流值:"));
        secondEdit->setVisible(true);
        break;
    case 8:
        firstLabel->setText(tr("湍流程度:"));
        secondLabel->setVisible(false);
        secondEdit->setVisible(false);
    default:
        break;
    }
}

AmplificationFactorBox::AmplificationFactorBox(const QString &groupTitle, QWidget *parent) :
    comboBoxGroupBox(groupTitle, parent)
{
    QStringList amplificationLables;
    amplificationLables << "层湍流" << "按时间" << "Ma";
    QStringList contentLables;
    contentLables << "热流放大系数:" << "层流:" << "湍流:";
    init(amplificationLables, contentLables);
}



void AmplificationFactorBox::changeTransform(int index)
{
    if (index == 0) {
        firstLabel->setText(tr("层流:"));
        secondLabel->setVisible(true);
        secondEdit->setVisible(true);
        button->setVisible(false);
    } else if (index == 1 || index == 2) {
        firstLabel->setText(tr("维数:"));
        secondLabel->setVisible(false);
        secondEdit->setVisible(false);
        button->setVisible(true);
    }
}
