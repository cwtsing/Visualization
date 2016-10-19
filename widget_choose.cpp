#include "widget_chooset.h"
#include <QFileDialog>
#include <QDebug>
#include <QLayout>
#include <QHeaderView>
WidgetChoose::WidgetChoose(QWidget *parent) :
    QWidget(parent)
{
    // init layout
    QGridLayout *mainLayout = new QGridLayout();
    QGroupBox *trajectoryGroupBox = new QGroupBox(tr("轨迹参数"), this);
    QGridLayout *trajectoryLayout = new QGridLayout();
    QGroupBox *heatecGroupBox = new QGroupBox(tr("Heatec计算设置"), this);
    QGridLayout *heatecLayout = new QGridLayout();
    QGroupBox *hcdGroupBox = new QGroupBox(tr("传热计算设置"), this);
    QGridLayout *hcdLayout = new QGridLayout();
    QGroupBox *chooseGroupBox = new QGroupBox(tr("轨迹遴选设置"), this);
    QGridLayout *chooseLayout = new QGridLayout();

    trajectoryGroupBox->setObjectName("topGroupBox");
    heatecGroupBox->setObjectName("topGroupBox");
    hcdGroupBox->setObjectName("topGroupBox");
    chooseGroupBox->setObjectName("topGroupBox");
    // init label and edit
    cruiseStratLabel = new QLabel(tr("巡航开始时刻(s):"));
    cruiseEndLabel = new QLabel(tr("巡航终止时刻(s):"));
    trajectoryStartLineLabel = new QLabel(tr("轨迹数据在文件中的起始行号:"));
    characMutationLabel = new QLabel(tr("分离引起的特征量突变:"));
    heatecMinMachNumLabel = new QLabel(tr("气动热计算的最小马赫数:"));
    heatecTimeStartLabel = new QLabel(tr("Heatec计算开始时刻:"));
    heatecTimeEndLabel = new QLabel(tr("Heatec计算终止时刻:"));
    heatecMinTimeStepLabel = new QLabel(tr("气动热计算输出最小时间步长:"));
    heatecStartLineLabel = new QLabel(tr("heatec计算结果在文件中的起始行号:"));
    hcdTimeStartLabel = new QLabel(tr("热传导计算开始时刻(s):"));
    hcdTimeEndLabel = new QLabel(tr("热传导计算终止时刻(s):"));
    chooseTimeStartLabel = new QLabel(tr("遴选开始时间(s):"));
    chooseTimeEndLabel = new QLabel(tr("遴选终止时间(s):"));
    chooseCoordinateLabel = new QLabel(tr("一维传热计算结果遴选坐标:"));

    cruiseStratEdit = new QLineEdit();
    cruiseEndEdit = new QLineEdit();
    trajectoryStartLineEdit = new QLineEdit();
    characMutationEdit = new QLineEdit();
    heatecMinMachNumEdit = new QLineEdit();
    heatecTimeStartEdit = new QLineEdit();
    heatecTimeEndEdit = new QLineEdit();
    heatecMinTimeStepEdit = new QLineEdit();
    heatecStartLineEdit = new QLineEdit();
    hcdTimeStartEdit = new QLineEdit();
    hcdTimeEndEdit = new QLineEdit();
    chooseTimeStartEdit = new QLineEdit();
    chooseTimeEndEdit = new QLineEdit();
    chooseCoordinateEdit = new QLineEdit();



    // init radioBox
    QStringList labels;
    labels << "m" << "km";
    heightUnitsBox = new MyUsualRadioBox(tr("轨迹文件中的高度单位"), labels);
    labels.clear();

    labels << "度" << "弧度";
    angleUnitsBox = new MyUsualRadioBox(tr("轨迹文件中的角度度单位"), labels);
    labels.clear();

    labels << "K" << "摄氏度";
    staticTmpUnitsBox = new MyUsualRadioBox(tr("轨迹文件中的静温单位"), labels);
    labels.clear();

    labels << "Pa" << "hPa" << "KPa";
    staticPressureUnitsBox = new MyUsualRadioBox(tr("轨迹文件中的静压单位"), labels);
    labels.clear();
    QHBoxLayout *radioLayout = new QHBoxLayout();
    radioLayout->addWidget(heightUnitsBox);
    radioLayout->addWidget(angleUnitsBox);
    radioLayout->addWidget(staticTmpUnitsBox);
    radioLayout->addWidget(staticPressureUnitsBox);

    labels << "轨迹数据" << "根据Ma和大气文件计算" << "根据Ma和轨迹大气静温计算";
    calSpeedMethodBox = new MyUsualRadioBox(tr("速度计算方式"), labels);
    labels.clear();

    labels << "不启动" << "单点计算";
    heatecStartMethodBox = new MyUsualRadioBox(tr("Heatec启动方式"), labels);
    labels.clear();

    labels << "否" << "是";
    heatecClearResultBox  = new MyUsualRadioBox(tr("Heatec计算前是否清除已有结果文件"), labels);
    hcdStartBox  = new MyUsualRadioBox(tr("是否启动Hcd1计算传热"), labels);

    hcdClearBox   = new MyUsualRadioBox(tr("传热计算前是否清除已有结果文件"), labels);

    // init table
    QGroupBox *attackAngleBox = new QGroupBox("有效攻角计算系数");
    QHBoxLayout *attackAngleLayout = new QHBoxLayout();
    attackAngleRatioTable = new QTableWidget(1, 4);
    attackAngleRatioTable->verticalHeader()->setVisible(false);
    QStringList headerLabels;
    headerLabels << tr("a1") << tr("a2") << tr("a3") << tr("a4");
    attackAngleRatioTable->setHorizontalHeaderLabels(headerLabels);
    attackAngleRatioTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    attackAngleRatioTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    attackAngleRatioTable->setFixedHeight(Utils::windowSize().height() * 0.1);
    attackAngleLayout->addWidget(attackAngleRatioTable);
    attackAngleBox->setLayout(attackAngleLayout);

    QGroupBox *trajectoryParaBox = new QGroupBox("轨迹文件中各参数所在列号");
    QHBoxLayout *trajectoryParaLayout = new QHBoxLayout();
    trajectoryParaColTable = new QTableWidget(1, 10);
    trajectoryParaColTable->verticalHeader()->setVisible(false);
    headerLabels.clear();
    headerLabels << tr("时间") << tr("高度") << tr("马赫数") << tr("攻角") << tr("侧滑角") \
                    << tr("舵偏角") << tr("速度") << tr("静温") << tr("静压") << tr("分离特征量");
    trajectoryParaColTable->setHorizontalHeaderLabels(headerLabels);
    trajectoryParaColTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    trajectoryParaColTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    trajectoryParaColTable->setFixedHeight(Utils::windowSize().height() * 0.1);
    trajectoryParaLayout->addWidget(trajectoryParaColTable);
    trajectoryParaBox->setLayout(trajectoryParaLayout);

    QGroupBox *heatecParaBox = new QGroupBox("heatec文件中各参数所在列号");
    QHBoxLayout *heatecParaLayout = new QHBoxLayout();
    heatecParaColTable = new QTableWidget(1, 4);
    heatecParaColTable->verticalHeader()->setVisible(false);
    headerLabels.clear();
    headerLabels << tr("时间") << tr("热流") << tr("恢复焓") << tr("平衡温度") ;
    heatecParaColTable->setHorizontalHeaderLabels(headerLabels);
    heatecParaColTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    heatecParaColTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    heatecParaColTable->setFixedHeight(Utils::windowSize().height() * 0.1);
    heatecParaLayout->addWidget(heatecParaColTable);
    heatecParaBox->setLayout(heatecParaLayout);


    // init button
    trajectoryDirectoryEdit = new QLineEdit();
    trajectoryDirectoryEdit->setObjectName("dirEdit");
    connect(trajectoryDirectoryEdit, &QLineEdit::textChanged, this, &WidgetChoose::changeAtmosphereAvailability);
    selectTrajectoryDirButton = new QPushButton(tr("选择轨迹数据目录"), this);
    selectTrajectoryDirButton->setObjectName("selectTrajectoryDirButton");
    connect(selectTrajectoryDirButton, &QPushButton::clicked, this, &WidgetChoose::showSelectedDirectory);

    atmosphereFileEdit = new QLineEdit();
    atmosphereFileEdit->setObjectName("dirEdit");
    selectAtmosphereButton = new QPushButton(tr("选择大气模型文件"), this);
    selectAtmosphereButton->setObjectName("selectAtmosphereButton");
    connect(selectAtmosphereButton, &QPushButton::clicked, this, &WidgetChoose::showSelectedDirectory);

    pointParaTemplateEdit = new QLineEdit();
    pointParaTemplateEdit->setObjectName("dirEdit");
    selectPointParaTemplateButton = new QPushButton(tr("选择单点参数文件"), this);
    selectPointParaTemplateButton->setObjectName("selectPointParaTemplateButton");
    connect(selectPointParaTemplateButton, &QPushButton::clicked, this, &WidgetChoose::showSelectedDirectory);

    createButton = new QPushButton(tr("生成计算文件"), this);
    createButton->setFixedSize(Utils::largeButtonSize());
    connect(createButton, &QPushButton::clicked, this, &WidgetChoose::saveParameterData);
    calButton = new QPushButton(tr("开始计算"), this);
    calButton->setFixedSize(Utils::largeButtonSize());

    // set layout
    QGroupBox *trajectoryNoneBorderBox = new QGroupBox();
    QGridLayout *trajectoryNoneBorderLayout = new QGridLayout();
    trajectoryNoneBorderLayout->addWidget(selectTrajectoryDirButton, 0, 0);
    trajectoryNoneBorderLayout->addWidget(trajectoryDirectoryEdit, 0, 1, 1, 3);
    trajectoryNoneBorderLayout->addWidget(selectAtmosphereButton, 1, 0);
    trajectoryNoneBorderLayout->addWidget(atmosphereFileEdit, 1, 1, 1, 3);
    trajectoryNoneBorderLayout->addWidget(cruiseStratLabel, 2, 0);
    trajectoryNoneBorderLayout->addWidget(cruiseStratEdit, 2, 1);
    trajectoryNoneBorderLayout->addWidget(cruiseEndLabel, 2, 2);
    trajectoryNoneBorderLayout->addWidget(cruiseEndEdit, 2, 3);
    trajectoryNoneBorderLayout->addWidget(trajectoryStartLineLabel, 2, 4);
    trajectoryNoneBorderLayout->addWidget(trajectoryStartLineEdit, 2, 5);
    trajectoryNoneBorderBox->setLayout(trajectoryNoneBorderLayout);
    trajectoryNoneBorderBox->setStyleSheet("QGroupBox{border:none}");
//    trajectoryNoneBorderBox->setFixedHeight(Utils::windowSize().height() * 0.17);
    trajectoryLayout->addWidget(trajectoryNoneBorderBox, 0, 0, 3, 6);
    trajectoryLayout->addWidget(trajectoryParaBox, 3, 0, 1, 6, Qt::AlignTop);
    trajectoryLayout->addLayout(radioLayout, 4, 0, 1, 6, Qt::AlignTop);
    trajectoryLayout->addWidget(calSpeedMethodBox, 5, 0, 1, 4);
    trajectoryLayout->addWidget(attackAngleBox, 6, 0, 1, 4, Qt::AlignTop);
    trajectoryGroupBox->setLayout(trajectoryLayout);


    heatecLayout->addWidget(heatecStartMethodBox, 0, 0, 1, 2);
    heatecLayout->addWidget(heatecClearResultBox, 1, 0, 1, 2);
    QGroupBox *heatecNoneBorderBox = new QGroupBox();
    QGridLayout *heatecNoneBorderLayout = new QGridLayout();
    heatecNoneBorderLayout->addWidget(heatecMinMachNumLabel, 2, 0);
    heatecNoneBorderLayout->addWidget(heatecMinMachNumEdit, 2, 1);
    heatecNoneBorderLayout->addWidget(heatecMinTimeStepLabel, 2, 2);
    heatecNoneBorderLayout->addWidget(heatecMinTimeStepEdit, 2, 3);
    heatecNoneBorderLayout->addWidget(heatecTimeStartLabel, 3, 0);
    heatecNoneBorderLayout->addWidget(heatecTimeStartEdit, 3, 1);
    heatecNoneBorderLayout->addWidget(heatecTimeEndLabel, 3, 2);
    heatecNoneBorderLayout->addWidget(heatecTimeEndEdit, 3, 3);
    heatecNoneBorderLayout->addWidget(selectPointParaTemplateButton, 4, 0, Qt::AlignLeft);
    heatecNoneBorderLayout->addWidget(pointParaTemplateEdit, 4, 1, 1, 3);
    heatecNoneBorderLayout->addWidget(heatecStartLineLabel, 5, 0);
    heatecNoneBorderLayout->addWidget(heatecStartLineEdit, 5, 1);
    heatecNoneBorderBox->setLayout(heatecNoneBorderLayout);
    heatecNoneBorderBox->setStyleSheet("QGroupBox{border:none}");
//    heatecNoneBorderBox->setFixedHeight(Utils::windowSize().height() * 0.2);
    heatecLayout->addWidget(heatecNoneBorderBox, 2, 0, 4, 4);
    heatecLayout->addWidget(heatecParaBox, 6, 0, 1, 4, Qt::AlignTop);
    heatecGroupBox->setLayout(heatecLayout);

    hcdLayout->addWidget(hcdStartBox, 0, 0);
    hcdLayout->addWidget(hcdTimeStartLabel, 0, 1);
    hcdLayout->addWidget(hcdTimeStartEdit, 0, 2);
    hcdLayout->addWidget(hcdTimeEndLabel, 0, 3);
    hcdLayout->addWidget(hcdTimeEndEdit, 0, 4);
    hcdLayout->addWidget(hcdClearBox, 1, 0);
    hcdGroupBox->setLayout(hcdLayout);

    chooseLayout->addWidget(chooseTimeStartLabel, 0, 0);
    chooseLayout->addWidget(chooseTimeStartEdit, 0, 1);
    chooseLayout->addWidget(chooseTimeEndLabel, 0, 2);
    chooseLayout->addWidget(chooseTimeEndEdit, 0, 3);
    chooseLayout->addWidget(chooseCoordinateLabel, 0, 4);
    chooseLayout->addWidget(chooseCoordinateEdit, 0, 5);
    chooseGroupBox->setLayout(chooseLayout);


    mainLayout->addWidget(trajectoryGroupBox, 0, 0, 2, 1);
    mainLayout->addWidget(heatecGroupBox, 0, 1, 1, 3);
    mainLayout->addWidget(hcdGroupBox, 2, 0);
    mainLayout->addWidget(chooseGroupBox, 1, 1, 1, 3);
    mainLayout->addWidget(createButton, 2, 2);
    mainLayout->addWidget(calButton, 2, 3);
    mainLayout->setColumnStretch(0, 3);
    mainLayout->setColumnStretch(1, 1);
    mainLayout->setColumnStretch(2, 1);
    mainLayout->setColumnStretch(3, 1);
    this->setLayout(mainLayout);
}

WidgetChoose::~WidgetChoose()
{

}

void WidgetChoose::showSelectedDirectory()
{
    QPushButton *button= qobject_cast<QPushButton*>(sender());
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setViewMode(QFileDialog::List);

    if (button->objectName() == "selectTrajectoryDirButton") {
        fileDialog->setFileMode(QFileDialog::Directory);
        if (fileDialog->exec() == QDialog::Accepted) {
            trajectoryDirectoryEdit->setText(fileDialog->selectedFiles()[0]);
        }
    } else if (button->objectName() == "selectAtmosphereButton") {
        if (fileDialog->exec() == QDialog::Accepted) {
            atmosphereFileEdit->setText(fileDialog->selectedFiles()[0]);
        }
    } else if (button->objectName() == "selectPointParaTemplateButton") {
        if (fileDialog->exec() == QDialog::Accepted) {
            pointParaTemplateEdit->setText(fileDialog->selectedFiles()[0]);
        }
    }

    fileDialog->close();
}

void WidgetChoose::changeAtmosphereAvailability(const QString dir)
{
    if (!dir.isEmpty()) {
       selectAtmosphereButton->setDisabled(true);
       atmosphereFileEdit->setText("");
       atmosphereFileEdit->setDisabled(true);
    } else {
        selectAtmosphereButton->setDisabled(false);
        atmosphereFileEdit->setDisabled(false);
    }
}

void WidgetChoose::saveParameterData()
{
    QString paraData;
    paraData += cruiseStratEdit->text() + " " + cruiseEndEdit->text() + "\n";
    paraData += trajectoryStartLineEdit->text() + "\n";

    paraData += "时间  高度  马赫数   攻角   侧滑角   舵偏角   速度   静温   静压   分离特征量(质量或推力)\n";
    for (int i = 0;i < trajectoryParaColTable->columnCount();i++) {
        paraData += trajectoryParaColTable->item(1, i)->text() + " ";
    }
    paraData += "\n";

    paraData += QString::number(heightUnitsBox->radioIndex() + 1) + "\n";
    paraData += QString::number(angleUnitsBox->radioIndex() + 1) + "\n";
    paraData += QString::number(staticTmpUnitsBox->radioIndex() + 1) + "\n";
    paraData += QString::number(staticPressureUnitsBox->radioIndex() + 1) + "\n";


}
