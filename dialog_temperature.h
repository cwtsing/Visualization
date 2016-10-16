#ifndef DIALOG_TEMPERATURE_H
#define DIALOG_TEMPERATURE_H
#include <QDialog>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

class Dialog_temperature : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_temperature(int editNum, QWidget *parent = 0);
    ~Dialog_temperature();
    void init(int editNum);

private:
    QStringList labels;
    QPushButton *saveButton;

public slots:
    void saveFile();
};

#endif // DIALOG_TEMPERATURE_H
