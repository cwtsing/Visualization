#include "dialog_temperature.h"
#include <QGridLayout>


Dialog_temperature::Dialog_temperature(int editNum, QWidget *parent) :
    QDialog(parent)
{
    init(editNum);
}
Dialog_temperature::~Dialog_temperature()
{

}

void Dialog_temperature::init(int editNum)
{



    labels << "第一层温度" << "第二层温度" << "第三层温度" << "第四层温度" << "第五层温度";
    saveButton = new QPushButton(tr("保存温度到文件"), this);

    //set layout
    QGridLayout *editLayout = new QGridLayout();
    for(int i = 0; i < editNum; i++)
    {
        QLabel *label = new QLabel(labels.at(i), this);
        label->setObjectName("label_" + QString::number(i));
        QTextEdit *edit = new QTextEdit(this);
        edit->setObjectName("edit_" + QString::number(i));
        editLayout->addWidget(label, 0, i);
        editLayout->addWidget(edit, 1, i);
    }
    editLayout->addWidget(saveButton, 2, 0);
    this->setLayout(editLayout);
}

void Dialog_temperature::saveFile()
{

}
