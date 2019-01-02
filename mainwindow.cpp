#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QString>
#include<qstring.h>
#include<string.h>
#include<QTime>
#include<QFile>
#include<QTextStream>
#include"treedialog.h"
#include"historydialog.h"
int curr=0;
void sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    wc=0;
   //History_Tree* history_node = new History_Tree[5];
    ui->setupUi(this);
    ui->progressBar->setValue(0);
   // ui->Button_encode->setEnabled(true);
    //connect(ui->lineEdit_input,SIGNAL(clicked),this,SLOT(boo()));
    connect(ui->Button_encode,SIGNAL(clicked()),this,SLOT(OnBtrOK())); //Button to encode
    connect(ui->lineEdit_input,SIGNAL(returnPressed()),this,SLOT(OnReturPressed()));  //press return to call OnBtrOK
    connect(ui->lineEdit_binary,SIGNAL(returnPressed()),this,SLOT(OnReturnPressed_decode()));  //press return to call decode

    //connect(ui->lineEdit_input,SIGNAL(returnPressed()),this,SLOT(OnReturPressed()));

    connect(ui->Button_decode,SIGNAL(clicked()),this,SLOT(decode()));
   connect(ui->Button_chart,SIGNAL(clicked()),this,SLOT(chart()));
   connect(ui->Button_history,SIGNAL(clicked()),this,SLOT(history()));
    QRegExp regExp("[10]*$");//limit the input is binary value onl
    ui->lineEdit_binary->setValidator(new QRegExpValidator(regExp,this));

//   hptr=new HistoryDialog(nullptr,this);
//  connect(hptr,SIGNAL(__accepted()),this,SLOT(OnBtrOK()));

}

MainWindow::~MainWindow()
{
    //tree.~HuffmanTree();
    delete ui;
}
bool MainWindow::boo(){
    return true;
}

int MainWindow::OnBtrOK()
{

    QString text=ui->lineEdit_input->text();

     ui->progressBar->setValue(20);sleep(200);
  //  if (boo()) {ui->Button_encode->setEnabled(true);treee.init();}
//    QString str;
    int len = text.length();
    HuffmanTree tree;
    char*  ch=nullptr;
    QByteArray ba = text.toLatin1(); // must
    ch=ba.data();

    for(int i=0;i<len;i++)
    tree.insert(ch[i]);
    tree.CreateHuffmanTree();
    tree.CreateHuffmanCode();
    tree.writeFile();
//    char* code = tree.codeArray->ptr;
    char *a=new char[len];
    for(int j=0;j<len;j++){
        a=tree.codeArray[j].ptr;
    }

     ui->progressBar->setValue(67);sleep(100);
    QFile f("./code.txt");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cout << "Open failed." << std::endl;
    }
    QTextStream txtInput(&f);
    QString ss;
    while(!txtInput.atEnd())
    {
        ss += txtInput.readLine();
        ss +="\n";
    }
    f.close();

//    str = QString(QLatin1String(code));

    if(text == nullptr)
       { QMessageBox::information(this,"ERROR","NO INPUT");
        ui->input_Text_encode->setPlainText("");
        ui->output_decode->setPlainText("");
        }
    else
        ui->input_Text_encode->setPlainText(ss);
//    History_Tree ptr[1];
        history_node[wc%5].name = text;
        history_node[wc%5].encode=ss;
//        history_node = ptr;
//    l.name=text;
//    l.encode=ss;
//    curr++;
    wc++;

     ui->progressBar->setValue(100);
     sleep(1000);
     ui->progressBar->setValue(0);


//treee.codeArray=tree.codeArray;
treee=tree;
//treee.~HuffmanTree();
    return 0;
}

int MainWindow::decode(){
if(ui->input_Text_encode->toPlainText()=="")
   {QMessageBox::information(this,"ERROR","NO INPUT");return 0;}
    HuffmanTree tree= treee;
    QString binary=ui->lineEdit_binary->text();

     ui->progressBar->setValue(31); sleep(300);
    if(binary==nullptr)
        {QMessageBox::information(this,"ERROR","NO INPUT");
        ui->output_decode->setPlainText("");
        ui->progressBar->setValue(0); return 0;}
    char *binarycode;

    QByteArray abc = binary.toLatin1(); // must
    binarycode=abc.data();
  ui->progressBar->setValue(78); sleep(100);
    //tree.decode(binarycode);
int check = tree.decode_char(binarycode);
    QFile ff("./decode.txt");
    if(!ff.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cout << "Open failed." << std::endl;
    }
    QTextStream txtInputt(&ff);
    QString out=txtInputt.readAll();
//       while(!txtInputt.atEnd())
//       {
//           out += txtInputt.readLine();

//       }
    ff.close();

    if(check ==-1)
    ui->output_decode->setPlainText(out);
else
       { string strt=to_string(check);
        QMessageBox::information(this,"ERROR","ERROR in "+QString::number(check)+"th");
        ui->output_decode->setPlainText("");
        }
 ui->progressBar->setValue(100);
 sleep(1000);
  ui->progressBar->setValue(0);
    return 0;
}
int MainWindow::chart(){
    if(ui->input_Text_encode->toPlainText()==""){
        QMessageBox::information(this,"Error Message","No ENCODED CHARACTERS");
        return 0;
    }

   TreeDialog *log = new TreeDialog(treee.getWei(),treee.getLen());
   log->show();
    return 0;
}

int MainWindow::OnReturPressed(){
    OnBtrOK();
    return 0;
}
int MainWindow::OnReturnPressed_decode(){
    decode();
    return 0;
}
//int MainWindow::history(){
//    QString temp="";
//    QFile f("./choose.txt");
//    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//        std::cout << "Open failed." << std::endl;
//    }else{
//    QTextStream txtInput(&f);
//    temp = txtInput.readAll();}
//    f.close();
//    if(temp == ""){
//        HistoryDialog *lp = new HistoryDialog(this->history_node);
//        lp->show();
//    }
//    else{
//        ui->lineEdit_input->setText(temp);
//        OnBtrOK_choose();
//        QFile ff("./choose.txt");
//        if(!ff.open(QIODevice::WriteOnly | QIODevice::Text))
//        {
//            std::cout << "Open failed." << std::endl;
//        }else{
//        QTextStream txtoutput(&f);
//        txtoutput<<"";}
//        f.close();
//    }



//    return 0;

//}
int MainWindow::history(){
    QString temp="";
    QFile f("./choose.txt");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cout << "Open failed." << std::endl;
    }else{
    QTextStream txtInput(&f);
    temp = txtInput.readAll();}
    f.close();
    if(temp == ""|| temp==ui->lineEdit_input->text()){
        HistoryDialog *lp = new HistoryDialog(this->history_node);
        lp->show();
    }
    else{
        ui->lineEdit_input->setText(temp);
        OnBtrOK_choose();
        QFile ff("./choose.txt");
        if(!ff.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            std::cout << "Open failed." << std::endl;
        }else{
        QTextStream txtoutput(&f);
        txtoutput<<"";}
        f.close();
    }



    return 0;

}
int MainWindow::OnBtrOK_choose()
{

    QString text=ui->lineEdit_input->text();


  //  if (boo()) {ui->Button_encode->setEnabled(true);treee.init();}
//    QString str;
    int len = text.length();
    HuffmanTree tree;
    char*  ch=nullptr;
    QByteArray ba = text.toLatin1(); // must
    ch=ba.data();

    for(int i=0;i<len;i++)
    tree.insert(ch[i]);
    tree.CreateHuffmanTree();
    tree.CreateHuffmanCode();
    tree.writeFile();
//    char* code = tree.codeArray->ptr;
    char *a=new char[len];
    for(int j=0;j<len;j++){
        a=tree.codeArray[j].ptr;
    }

    QFile f("./code.txt");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cout << "Open failed." << std::endl;
    }
    QTextStream txtInput(&f);
    QString ss;
    while(!txtInput.atEnd())
    {
        ss += txtInput.readLine();
        ss +="\n";
    }
    f.close();

    if(text == nullptr)
       { QMessageBox::information(this,"ERROR","NO INPUT");
        ui->input_Text_encode->setPlainText("");
        ui->output_decode->setPlainText("");
        }
    else
        ui->input_Text_encode->setPlainText(ss);


//treee.codeArray=tree.codeArray;
treee=tree;
//treee.~HuffmanTree();
    return 0;
}

