#ifndef TREEDIALOG_H
#define TREEDIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include "nodeitem.h"
#include "treescene.h"

namespace Ui {
class TreeDialog;
}

class TreeDialog : public QDialog
{
    Q_OBJECT

public:
    void Next();
    explicit TreeDialog(int *weight,int num,QWidget *parent = 0);
    ~TreeDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::TreeDialog *ui;
    TreeScene *treeScene;
};

#endif // TREEDIALOG_H
