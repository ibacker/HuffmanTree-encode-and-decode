#ifndef HISTORY_H
#define HISTORY_H

#include <QDialog>
#include<QString>
class History_Tree { //HuffmanTree的私有类，编码类
public:
    History_Tree(){encode=name="";}
    ~History_Tree() {}
    QString encode;
    QString name;
   // static int curr;
};
namespace Ui {
class HistoryDialog;
}

class HistoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryDialog(History_Tree* ,QWidget *parent = nullptr);
    ~HistoryDialog();
public:
    void init();
public:
    History_Tree *node;
private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void choose();
    void on_Button_choose_clicked();

private:
    Ui::HistoryDialog *ui;
};

//int History_Tree::curr = 0;
#endif // HISTORY_H
