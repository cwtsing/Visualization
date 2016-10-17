#ifndef DIALOG_MATERIAL_LIB_H
#define DIALOG_MATERIAL_LIB_H

#include <QDialog>
#include <QWidget>
#include <QTreeWidgetItem>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include "mywidget/my_treewidget_item.h"
#include "db/material_lib.h"
#include "mywidget/my_treewidget_item.h"

class MateriaLibDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MateriaLibDialog(QWidget *parent = 0);
    ~MateriaLibDialog();

private:
    void init();
    void addTreeWidgetItem(int index, int type, int id, const QString& name);
    void contextMenuEvent(QContextMenuEvent *event);

    QLabel *densityLabel;
    QLabel *emissivityLabel;
    QLineEdit *densityEdit;
    QLineEdit *emissivityEdit;
    QTreeWidget *treeWidget;
    QTreeWidgetItem *group_metal;
    QTreeWidgetItem *group_nonmetal;
    QPushButton *saveMaterialButton;
    QTableWidget *tmpLambdaTable;
    QTableWidget *tmpCpTable;

    QMenu *addMenu;
    QMenu *delMenu;
    QAction *addAction;
    QAction *delAction;
signals:
    void dataChanged();
public slots:
    void treeItemClicked(QTreeWidgetItem* item);
    void treeItemChange(QTreeWidgetItem* item);
    void saveMaterialLibData();
private slots:
    void onAddMenuTriggered(QAction *action);
    void onDelMenuTriggered(QAction *action);
};

#endif //DIALOG_MATERIAL_LIB_H
