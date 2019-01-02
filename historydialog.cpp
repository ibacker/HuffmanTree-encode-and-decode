#include "historydialog.h"
#include "ui_historydialog.h"
#include<QMessageBox>
#include<QDebug>
#include<QFile>
#include<iostream>
HistoryDialog::HistoryDialog(History_Tree* pp, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoryDialog)
{
    this->node =pp;
    ui->setupUi(this);
    init();
}

HistoryDialog::~HistoryDialog()
{
    delete ui;
}

void HistoryDialog::init(){
    //QStringList list;

    for(int i=0;i<5;i++){
        ui->comboBox->addItem(node[i].name);
    }
}
void HistoryDialog::on_comboBox_currentIndexChanged(const QString &name)
{
    for(int i=0;i<5;i++){
        if(name==node[i].name)
        ui->textEdit->setText(node[i].encode);
    }
}

void HistoryDialog::choose(){

   QString temp= ui->comboBox->currentText();
   QFile f("./choose.txt");
   if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
   {
       std::cout << "Open failed." << std::endl;
   }
   QTextStream txtOutput(&f);
   txtOutput<<temp;
   f.close();
   reject();
}

void HistoryDialog::on_Button_choose_clicked()
{
    choose();
}
