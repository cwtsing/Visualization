#include "widget_ihcp_1.h"
#include "material_lib.h"
#include "dialog_material_lib.h"
#include "dialog_temperature.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include "material_lib.h"
#include <QComboBox>
Widget_ihcp_1::Widget_ihcp_1(QWidget *parent) :
    QWidget(parent)
{
    init();
}
Widget_ihcp_1::~Widget_ihcp_1()
{

}

void Widget_ihcp_1::init()
{
    materialLayNum = 5;
    //init all Qmembers
    fir1Label = new QLabel(tr("材料层数"));
    fir2Label = new QLabel(tr("初温（K）"));
    fir3Label = new QLabel(tr("环境温度外（K）"));
    fir4Label = new QLabel(tr("环境温度内（K）"));
    fir1Text = new QLineEdit();
    fir2Text = new QLineEdit();
    fir3Text = new QLineEdit();
    fir4Text = new QLineEdit();


    sec1Label = new QLabel(tr("测点与外壁距离（m）"));
    sec2Label = new QLabel(tr("外边面辐射发射率"));
    sec3Label = new QLabel(tr("从头计算还是接着算：0从头，1接着算"));

    sec4Label = new QLabel(tr("内表面辐射发射率"));
    sec5Label = new QLabel(tr("内表面对流系数"));
    sec1Text = new QLineEdit();
    sec2Text = new QLineEdit();
    sec3Text = new QLineEdit();
    sec4Text = new QLineEdit();
    sec5Text = new QLineEdit();

    thr1Label = new QLabel(tr("辨识时的优化参数"));
    thr2Label = new QLabel(tr("控制时间步长系数S"));
    thr3Label = new QLabel(tr("批处理文件数"));
    thr4Label = new QLabel(tr("控制收敛与否的温度"));
    thr5Label = new QLabel(tr("控制方差大小的系数"));
    thr6Label = new QLabel(tr("测点温度时间间隔"));
    thr1Text = new QLineEdit();
    thr2Text = new QLineEdit();
    thr3Text = new QLineEdit();
    thr4Text = new QLineEdit();
    thr5Text = new QLineEdit();
    thr6Text = new QLineEdit();

    layerBox = new QComboBox();
    QStringList layerLabels;
    layerLabels << "1" << "2" << "3" << "4" << "5";
    layerBox->addItems(layerLabels);
    layerBox->setCurrentIndex(4);
    connect(layerBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeTable(int)));

    button1 = new QPushButton(tr("输入测点温度"), this);
    connect(button1, &QPushButton::clicked, this, &Widget_ihcp_1::showTemperDialog);
    button1->setFixedSize(Utils::largeButtonSize() * 0.5);
    button2 = new QPushButton(tr("修改物性"), this);
    button2->setFixedSize(Utils::largeButtonSize() * 0.5);
    button3 = new QPushButton(tr("温度结果RES"), this);
    button3->setFixedSize(Utils::largeButtonSize() * 0.5);
    button4 = new QPushButton(tr("热流结果RES"), this);
    button4->setFixedSize(Utils::largeButtonSize() * 0.5);


    materialLabel = new QLabel(tr("材料库："));
    loadMaterialButton = new QPushButton(tr("载入文件"));
    connect(loadMaterialButton, &QPushButton::clicked, this, &Widget_ihcp_1::showLoadDialog);
    QHBoxLayout *materialLayout = new QHBoxLayout();
    materialLayout->addWidget(materialLabel);
    materialLayout->addWidget(loadMaterialButton);
    materialLayout->addStretch(1);

    QGroupBox *tableBox = new QGroupBox("");
    QVBoxLayout *tableLayout = new QVBoxLayout();
    firTableWidget = new QTableWidget(3, 5);
    firTableWidget->setRowCount(3);
    firTableWidget->setColumnCount(5);
    firTableWidget->setWindowTitle(tr("从内到外"));
    QStringList labels;
    labels << "第一层" << "第二层" << "第三层" << "第四层" << "第五层(最外层)";
    firTableWidget->setHorizontalHeaderLabels(labels);
    labels.clear();
    labels << "材料" << "每层材料网格数量" << "材料的厚度（m）" ;
    firTableWidget->setVerticalHeaderLabels(labels);
    firTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    firTableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableLayout->addLayout(materialLayout,0);

    tableLayout->addWidget(firTableWidget,1,Qt::AlignTop);

    tableBox->setLayout(tableLayout);
    firTableWidget->setFixedHeight(Utils::windowSize().height() * 0.3);

    for (int i = 0;i < 5;i++) {
        QStringList labels;
        QStringList metalList = MaterialLib::getInstance()->getMaterial();

        for (QStringList::iterator it = metalList.begin();it != metalList.end();it++){
            QString current = *it;
            labels << current;
        }
        for (int i = 0;i < firTableWidget->columnCount();i++) {
            QComboBox *metalBox = new QComboBox();
            metalBox->addItems(labels);
            firTableWidget->setCellWidget(0, i, metalBox);
        }
    }

    labels.clear();
    labels << "换热边界BC" << "定温边界BC";
    radioBox = new MyUsualRadioBox(tr("选择内表面边界类型"), labels);

    //Layout setting
    QGridLayout *mainLayout = new QGridLayout;
    QGridLayout *firLayout = new QGridLayout;
    QGridLayout *secLayout = new QGridLayout;
    QGridLayout *thrLayout = new QGridLayout;
    QHBoxLayout *buttonsLayout = new QHBoxLayout;

    QGroupBox *firBox = new QGroupBox();
    firLayout->addWidget(fir1Label, 0, 0);
    firLayout->addWidget(layerBox, 0, 1);
    firLayout->addWidget(fir2Label, 1, 0);
    firLayout->addWidget(fir2Text, 1, 1);
    firLayout->addWidget(fir3Label, 2, 0);
    firLayout->addWidget(fir3Text, 2, 1);
    firLayout->addWidget(fir4Label, 3, 0);
    firLayout->addWidget(fir4Text, 3, 1);
    firBox->setLayout(firLayout);
//    firLayout->addWidget(radioBox);

    QGroupBox *secBox = new QGroupBox();
    secLayout->addWidget(sec1Label, 0, 0);
    secLayout->addWidget(sec1Text, 0, 1);
    secLayout->addWidget(sec2Label, 0, 2);
    secLayout->addWidget(sec2Text, 0, 3);
    secLayout->addWidget(sec3Label, 0, 4);
    secLayout->addWidget(sec3Text, 0, 5);
    secLayout->addWidget(sec4Label, 1, 0);
    secLayout->addWidget(sec4Text, 1, 1);
    secLayout->addWidget(sec5Label, 1, 2);
    secLayout->addWidget(sec5Text, 1, 3);
    secBox->setLayout(secLayout);
    secBox->setFixedHeight(Utils::windowSize().height() * 0.2);

    QGroupBox *thrBox = new QGroupBox();
    thrLayout->addWidget(thr1Label, 0, 0);
    thrLayout->addWidget(thr1Text, 0, 1);
    thrLayout->addWidget(thr2Label, 0, 2);
    thrLayout->addWidget(thr2Text, 0, 3);
    thrLayout->addWidget(thr3Label, 0, 4);
    thrLayout->addWidget(thr3Text, 0, 5);
    thrLayout->addWidget(thr4Label, 1, 0);
    thrLayout->addWidget(thr4Text, 1, 1);
    thrLayout->addWidget(thr5Label, 1, 2);
    thrLayout->addWidget(thr5Text, 1, 3);
    thrLayout->addWidget(thr6Label, 1, 4);
    thrLayout->addWidget(thr6Text, 1, 5);
    thrBox->setLayout(thrLayout);
    thrBox->setFixedHeight(Utils::windowSize().height() * 0.15);

    buttonsLayout->addWidget(button1);
    buttonsLayout->addWidget(button2);
    buttonsLayout->addWidget(button3);
    buttonsLayout->addWidget(button4);

    mainLayout->addWidget(firBox, 0, 0, 1, 2);
    mainLayout->addWidget(radioBox, 1, 0, 1, 2);
    mainLayout->addWidget(secBox, 0, 2, 1, 3);
    mainLayout->addWidget(tableBox, 1, 2, 3, 3,Qt::AlignTop);
    mainLayout->addWidget(thrBox, 4, 2, 1, 3);
//    mainLayout->addLayout(buttonsLayout, 4, 0);
    mainLayout->addWidget(button1, 2, 0);
    mainLayout->addWidget(button2, 2, 1);
    mainLayout->addWidget(button3, 3, 0);
    mainLayout->addWidget(button4, 3, 1);

//    mainLayout->setColumnStretch(0, 1);
//    mainLayout->setColumnStretch(1, 1);
    mainLayout->setRowStretch(5, 1);

    this->setLayout(mainLayout);

}

void Widget_ihcp_1::changeTable(int index)
{
    materialLayNum = index + 1;
    for (int i = 0;i < firTableWidget->rowCount();i++) {
        for (int j = 0;j < firTableWidget->columnCount();j++) {
            bool isEnabled = j <= index ? true : false;
            QColor color = j <= index ? QColor("#FFFFFF") : QColor("#CCCCCC");
            Qt::ItemFlags flags = j <= index ? Qt::ItemIsEditable | Qt::ItemIsEnabled|Qt::ItemIsSelectable : Qt::NoItemFlags;
            if (i == 0) {
                firTableWidget->cellWidget(i, j)->setEnabled(isEnabled);
            } else {
                QTableWidgetItem *item = firTableWidget->itemAt(i , j);

                if (!item) {
                    item = new QTableWidgetItem();

                    firTableWidget->setItem( i, j, item);
                }
                item->setBackgroundColor(color);
                item->setFlags(flags);
            }
        }
    }
}

void Widget_ihcp_1::showLoadDialog()
{
    MateriaLibDialog *dialog = new MateriaLibDialog(this);
    dialog->show();
}

void Widget_ihcp_1::showTemperDialog()
{
    Dialog_temperature *dialog = new Dialog_temperature(materialLayNum);
    dialog->show();
}
