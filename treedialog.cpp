#include "treedialog.h"
#include "ui_treedialog.h"
#include <QPropertyAnimation>
#include <QDebug>
TreeDialog::TreeDialog(int *weight,int num,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TreeDialog)
{
    ui->setupUi(this);
    treeScene = new TreeScene(weight,num);
    ui->graphicsView->setScene(treeScene);
    connect(this,SIGNAL(returnPressed()),this,SLOT(on_pushButton_clicked()));
}

TreeDialog::~TreeDialog()
{
    delete ui;
}
void TreeDialog::Next()
{

    treeScene->createTree();
}





void TreeDialog::on_pushButton_clicked()
{
    Next();
}

void TreeDialog::on_pushButton_2_clicked()
{
    this->close();
}
