#include "widget_hcd.h"
#include "dialog_material_lib.h"
#include "dialog_table.h"

#include <QLayout>
#include <QHeaderView>
#include <QGroupBox>

WidgetHcd::WidgetHcd(QWidget *parent) :
    QWidget(parent)
{
    init();
}

WidgetHcd::~WidgetHcd()
{

}

void WidgetHcd::init()
{
    QGridLayout *mainLayout = new QGridLayout();


    // rightLayout
    QGroupBox *materialGroupBox = new QGroupBox(tr("材料库"));
    materialGroupBox->setObjectName("topGroupBox");
    QGridLayout *materialLayout = new QGridLayout();
    materialLabel = new QLabel(tr("材料库："));
    loadMaterialButton = new QPushButton(tr("载入文件"));
    connect(loadMaterialButton, &QPushButton::clicked, this, &WidgetHcd::showLoadDialog);
    saveMeterialBUtton = new QPushButton(tr("保存"));

    layerLabel = new QLabel(tr("层数:"));
    layerBox = new QComboBox();
    QStringList layerLabels;
    layerLabels << "1" << "2" << "3" << "4" << "5";
    layerBox->addItems(layerLabels);
    layerBox->setCurrentIndex(4);
    connect(layerBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeTable(int)));

    materialGraph = new QGraphicsView();
    materialTable = new QTableWidget(5,2);
//    materialTable->verticalHeader()->setVisible(false);
    QStringList headerLabels;
    headerLabels << "材料" << "厚度";
    materialTable->setHorizontalHeaderLabels(headerLabels);
    headerLabels.clear();
    headerLabels << "①(最外)" << "②" << "③" << "④" << "⑤(最内)";
    materialTable->setVerticalHeaderLabels(headerLabels);
    materialTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    materialTable->setRowCount(5);
    fillMetalTable();

    QGroupBox *materialNoneBorderBox = new QGroupBox();
    QGridLayout *materialNoneBorderLayout = new QGridLayout();
    materialNoneBorderLayout->addWidget(materialLabel, 0, 0);
    materialNoneBorderLayout->addWidget(loadMaterialButton, 0, 1);
    materialNoneBorderLayout->addWidget(saveMeterialBUtton, 0 , 2);
    materialNoneBorderLayout->addWidget(layerLabel, 1, 0);
    materialNoneBorderLayout->addWidget(layerBox, 1, 1);
    materialNoneBorderBox->setLayout(materialNoneBorderLayout);
    materialNoneBorderBox->setStyleSheet("QGroupBox{border:none}");
    materialNoneBorderBox->setFixedHeight(Utils::windowSize().height() * 0.15);
    materialLayout->addWidget(materialNoneBorderBox, 0, 0, 2, 3);
    materialLayout->addWidget(materialGraph, 2, 0, 1, 2,Qt::AlignTop);
    materialLayout->addWidget(materialTable, 2, 2, 1, 2,Qt::AlignTop);
    materialLayout->setColumnStretch(1, 1);
    materialLayout->setColumnStretch(2, 1);
    materialLayout->setColumnStretch(3, 2);

    materialGroupBox->setLayout(materialLayout);

    // leftUp layout
    QGroupBox *initialGroupBox = new QGroupBox(tr("初始参数设置"));
    initialGroupBox->setObjectName("topGroupBox");
    QGridLayout *initialGroupLayout = new QGridLayout();

    QStringList labels;
    labels << "初始温度(℃):" << "初始时刻(s):" << "终止时刻(s):" << "时间步长："
           << "最大迭代次数" << "计算结果结果保存间隔" << "监控点结果时间间隔："
           << "监控点1坐标：" << "监控点2坐标：" << "监控点3坐标："
           << "监控点4坐标：" << "监控点5坐标：";
    hcdEditBox = new GeneralEditBox("", labels, 12, 1, this);


    coordinateGraph = new QGraphicsView();
//    coordinateGraph->setFixedHeight(Utils::windowSize().height() * 0.5);



    initialGroupLayout->addWidget(hcdEditBox, 0, 0, 1, 2);
    initialGroupLayout->addWidget(coordinateGraph, 0, 2, 1, 3);

    initialGroupBox->setLayout(initialGroupLayout);
//    initialGroupBox->setFixedHeight(Utils::windowSize().height() * 0.7);

    // leftDown layout
    QGroupBox *borderGroupBox = new QGroupBox(tr("边界参数设置"));
    borderGroupBox->setObjectName("topGroupBox");
    QGridLayout *borderGroupLayout = new QGridLayout();

    borderTable = new QTableWidget(2,5);
    QStringList colLabels;
    colLabels << "边界条件" << "输入值" << "是否开启辐射" << "冷壁温度(K)" << "设置输入";
    borderTable->setHorizontalHeaderLabels(colLabels);
    borderTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    borderTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QStringList rowLabels;
    rowLabels << "外" << "内";
    borderTable->setVerticalHeaderLabels(rowLabels);
    borderTable->setFixedHeight(Utils::windowSize().height() * 0.16);

    boundaryConditionInsideBox = new QComboBox();
    boundaryConditionOutsideBox = new QComboBox();
    labels.clear();
    labels << "TW" << "TW-UDF" << "FLUX" << "FLUX-QGHR" << "FLUX-UDF" << "HTF" << "HTF-UDF";
    boundaryConditionInsideBox->addItems(labels);
    boundaryConditionOutsideBox->addItems(labels);
    labels.clear();
    labels << "是" << "否";
    isRadiationInsideRadio = new MyUsualRadioBox("", labels);
    isRadiationInsideRadio->setFixedHeight(isRadiationInsideRadio->sizeHint().height());
    isRadiationOutsideRadio = new MyUsualRadioBox("", labels);
    isRadiationOutsideRadio->setFixedHeight(isRadiationInsideRadio->sizeHint().height());

    settingInputInsedeButton = new QPushButton(tr("设置输入"));
//    settingInputInsedeButton->setStyleSheet("margin:10px;");
    connect(settingInputInsedeButton, &QPushButton::clicked, this, &WidgetHcd::showSettingInputDialog);
    settingInputOutsideButton = new QPushButton(tr("设置输入"));
    connect(settingInputOutsideButton, &QPushButton::clicked, this, &WidgetHcd::showSettingInputDialog);

    borderTable->setCellWidget(0, 0, boundaryConditionInsideBox);
    borderTable->setCellWidget(1, 0, boundaryConditionOutsideBox);
    borderTable->setCellWidget(0, 2, isRadiationInsideRadio);
    borderTable->setCellWidget(1, 2, isRadiationOutsideRadio);
    borderTable->setCellWidget(0, 4, settingInputInsedeButton);
    borderTable->setCellWidget(1, 4, settingInputOutsideButton);

    borderGroupLayout->addWidget(borderTable, 0, 0);
    borderGroupBox->setLayout(borderGroupLayout);
    borderGroupBox->setFixedHeight(Utils::windowSize().height() * 0.23);

    createButton = new QPushButton(tr("生成计算文件"), this);
    createButton->setFixedSize(Utils::largeButtonSize());
    connect(createButton, &QPushButton::clicked, this, &WidgetHcd::saveParameterData);
    calButton = new QPushButton(tr("开始计算"), this);
    calButton->setFixedSize(Utils::largeButtonSize());

    mainLayout->addWidget(materialGroupBox, 0, 1, 1, 2,Qt::AlignTop);
    mainLayout->addWidget(initialGroupBox, 0, 0);
    mainLayout->addWidget(borderGroupBox, 1, 0);
    mainLayout->addWidget(createButton, 1, 1);
    mainLayout->addWidget(calButton, 1, 2);
    mainLayout->setRowStretch(0, 3);
    mainLayout->setRowStretch(1, 1);
    mainLayout->setColumnStretch(0, 6);
    mainLayout->setColumnStretch(1, 1);
    mainLayout->setColumnStretch(2, 1);
//    mainLayout->setColumnStretch(3, 1);

    this->setLayout(mainLayout);
}

void WidgetHcd::fillMetalTable()
{
    QStringList labels;
    QList<MaterialLib::Material> material = MaterialLib::getInstance()->getMaterialNameList();

    for (QList<MaterialLib::Material>::iterator it = material.begin();it != material.end();it++){
        labels <<  (*it).materialName;
    }
    for (int i = 0;i < materialTable->rowCount();i++) {
        QComboBox *metalBox = new QComboBox();
        metalBox->addItems(labels);
        materialTable->setCellWidget(i, 0, metalBox);
    }
}

void WidgetHcd::changeTable(int index)
{
    for (int i = 0;i < materialTable->rowCount();i++) {
        for (int j = 0;j < materialTable->columnCount();j++) {
            bool isEnabled = i <= index ? true : false;
            QColor color = i <= index ? QColor("#FFFFFF") : QColor("#CCCCCC");
            Qt::ItemFlags flags = i <= index ? Qt::ItemIsEditable | Qt::ItemIsEnabled|Qt::ItemIsSelectable : Qt::NoItemFlags;
            if (j == 0) {
                materialTable->cellWidget(i, j)->setEnabled(isEnabled);
            } else {
                QTableWidgetItem *item = materialTable->itemAt(i , j);

                if (!item) {
                    item = new QTableWidgetItem();

                    materialTable->setItem( i, j, item);
                }
                item->setBackgroundColor(color);
                item->setFlags(flags);
            }
        }
    }
}

void WidgetHcd::showLoadDialog()
{
    MateriaLibDialog *dialog = new MateriaLibDialog(this);

    dialog->exec();
    fillMetalTable();

}

void WidgetHcd::showSettingInputDialog()
{
    QStringList headerLabels;
    headerLabels << tr("时刻(s)") << tr("冷壁热流(w/m2)") << tr("恢复焓(j/kg)");
    TableDialog *dialog = new TableDialog(tr("边界条件设置输入"), headerLabels, this);
    dialog->show();
}

void WidgetHcd::saveParameterData()
{
    QString paraData;

    paraData += "   不同材料层厚度                材料名";
    for (int i = 0;i <= layerBox->currentIndex();i++) {
        QComboBox *comboBox = static_cast<QComboBox*>(materialTable->cellWidget(i, 0));
        QString materialName = comboBox->currentText();
        float height = materialTable->item(i, 1)->text().toFloat();
        paraData += "MaterialHeight = " + QString::number(height) + "MaterialName = " + materialName + "\n";
    }

    paraData += "--坐标位置--   --边界条件--    --是否开启辐射散热功能--  "
                "--气动热冷壁热流及恢复焓文件名称--    --气动热计算的冷壁温度（单位：K）--";
    paraData += "";

}
