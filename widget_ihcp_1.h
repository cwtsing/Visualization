#ifndef WIDGET_IHCP_1_H
#define WIDGET_IHCP_1_H

#include <QWidget>
#include <QDialog>
#include <QObject>
#include <QLabel>
#include <QTableWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include "common.h"
#include <QComboBox>

#include "my_usual_radiobox.h"

class Widget_ihcp_1 : public QWidget
{
    Q_OBJECT

public:
    Widget_ihcp_1(QWidget *parent = 0);
    ~Widget_ihcp_1();
    void init();
private:
    int materialLayNum;

    QLabel *fir1Label;
    QLabel *fir2Label;
    QLabel *fir3Label;
    QLabel *fir4Label;

    QLineEdit *fir1Text;
    QLineEdit *fir2Text;
    QLineEdit *fir3Text;
    QLineEdit *fir4Text;

    QLabel *sec1Label;
    QLabel *sec2Label;
    QLabel *sec3Label;
    QLabel *sec4Label;
    QLabel *sec5Label;
    QLineEdit *sec1Text;
    QLineEdit *sec2Text;
    QLineEdit *sec3Text;
    QLineEdit *sec4Text;
    QLineEdit *sec5Text;

    QLabel *thr1Label;
    QLabel *thr2Label;
    QLabel *thr3Label;
    QLabel *thr4Label;
    QLabel *thr5Label;
    QLabel *thr6Label;
    QLineEdit *thr1Text;
    QLineEdit *thr2Text;
    QLineEdit *thr3Text;
    QLineEdit *thr4Text;
    QLineEdit *thr5Text;
    QLineEdit *thr6Text;

    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QPushButton *button4;

    QComboBox *layerBox;

    QTableWidget *firTableWidget;

    MyUsualRadioBox *radioBox;

    QLabel *materialLabel;
    QPushButton *loadMaterialButton;


signals:

public slots:
    void changeTable(int index);
    void showLoadDialog();
    void showTemperDialog();
};

#endif // WIDGET_IHCP_1_H
