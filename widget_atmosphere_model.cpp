#include "widget_atmosphere_model.h"
#include "dialog_table.h"
#include <QDebug>
#include <QHeaderView>
AtmosphereModelWidget::AtmosphereModelWidget(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *mainLayout = new QGridLayout();
    QStringList radioLabels;
    radioLabels << "1. 1962年u.s. standard大气参数表" << "2. 风洞流场参数"
                << "3. 输入大气参数"
                << "4. 1963年patrick air force base大气参数表"
                << "5. 1971年vandenberg reference大气参数表"
                << "6. 1973年vandenberg hot day大气参数表"
                << "7. 1973年vandenberg cold day大气参数表"
                << "8. 1971年kennedy hot day大气参数表"
                << "9. 1971年kennedy cold day大气参数表"
                << "10. 1976年u.s. standard大气参数表";
    atmosphereRadioBox = new MyUsualRadioBox("", radioLabels, MyUsualRadioBox::Vertical);
    atmosphereRadioBox->setRadioIndex(0);

    loadWindButton = new QPushButton(tr("载入风动参数"));
    loadWindButton->setObjectName("loadWindButton");
    loadWindButton->setEnabled(false);
    loadAtmosphereButton = new QPushButton(tr("载入大气参数"));
    loadAtmosphereButton->setObjectName("loadAtmosphereButton");
    loadAtmosphereButton->setEnabled(false);
    connect(loadWindButton, &QPushButton::clicked, this, &AtmosphereModelWidget::showLoadDialog);
    connect(loadAtmosphereButton, &QPushButton::clicked, this, &AtmosphereModelWidget::showLoadDialog);

    atmosphereRadioBox->insertWidgetWithButtonIndex(1, loadWindButton);
//    atmosphereRadioBox->insertWithButtonIndexEnd(1);
    atmosphereRadioBox->insertWidgetWithButtonIndex(2, loadAtmosphereButton);
//    atmosphereRadioBox->insertWithButtonIndexEnd(2);
    connect(atmosphereRadioBox, &MyUsualRadioBox::radioToggle, this, &AtmosphereModelWidget::changeButtonEnable);


    inputTable = new QTableWidget(5, 3);
    inputTable->verticalHeader()->setVisible(false);
    inputTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);;
    inputTable->setVisible(false);
    mainLayout->addWidget(atmosphereRadioBox, 0, 0);
    mainLayout->addWidget(inputTable, 0, 1, Qt::AlignTop);

    mainLayout->setColumnStretch(0, 7);
    mainLayout->setColumnStretch(1, 5);
    mainLayout->setRowStretch(0, 7);
    mainLayout->setRowStretch(1, 1);
    this->setLayout(mainLayout);
}

AtmosphereModelWidget::~AtmosphereModelWidget()
{

}

void AtmosphereModelWidget::showLoadDialog()
{
    QPushButton *button= qobject_cast<QPushButton*>(sender());
    QStringList headerLabels;

    if (button->objectName() == "loadWindButton") {
        headerLabels << "时间(s)" << "静温(k)" << "静压(Pa)";
        TableDialog *dialog = new TableDialog("载入风洞", headerLabels);
        dialog->show();
    } else if (button->objectName() == "loadAtmosphereButton") {
        headerLabels << "高度(m)" << "静温(k)" << "静压(Pa)";
        TableDialog *dialog = new TableDialog("载入大气模型", headerLabels);
        dialog->show();
    }
}

void AtmosphereModelWidget::changeButtonEnable(int index)
{
    QStringList headerLabels;
    switch (index) {
    case 1:
        headerLabels << "时间(s)" << "静温(k)" << "静压(Pa)";
        inputTable->setHorizontalHeaderLabels(headerLabels);
        inputTable->setVisible(true);
        loadWindButton->setEnabled(true);
        loadAtmosphereButton->setEnabled(false);
        break;
    case 2:
        headerLabels << "高度(m)" << "静温(k)" << "静压(Pa)";
        inputTable->setHorizontalHeaderLabels(headerLabels);
        loadWindButton->setEnabled(false);
        loadAtmosphereButton->setEnabled(true);
        break;
    default:
        inputTable->setVisible(false);
        loadWindButton->setEnabled(false);
        loadAtmosphereButton->setEnabled(false);
        break;
    }
}

QString AtmosphereModelWidget::getParameterData()
{
    return QString("atmos");
}
