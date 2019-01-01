#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"1.h"
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

private slots:
    int OnBtrOK();
    int decode();
    int OnReturPressed();
    bool boo();
    int OnReturnPressed_decode();
    int chart();
private:
    Ui::MainWindow *ui;
    int *weight=NULL;
    int num;
};

#endif // MAINWINDOW_H
