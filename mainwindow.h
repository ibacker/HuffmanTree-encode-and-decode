#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"1.h"
#include"historydialog.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
     HuffmanTree treee;
     History_Tree *history_node=new History_Tree[5];
    // History_Tree l;
//    static int curr=0;
   //  HistoryDialog *hptr;
private slots:
    int OnBtrOK();
    int decode();
    int OnReturPressed();
    bool boo();
    int OnReturnPressed_decode();
    int chart();
    int history();
    int OnBtrOK_choose();
private:
    Ui::MainWindow *ui;
    int *weight=nullptr;
    int num;
    int wc;

      HistoryDialog *lop=nullptr;
};

#endif // MAINWINDOW_H
