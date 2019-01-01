#ifndef TREELINE_H
#define TREELINE_H
#include <QObject>
#include <QGraphicsLineItem>
class TreeLine : public QObject,public QGraphicsLineItem
{
private:
public:
    TreeLine(QLineF line1):QObject(0),QGraphicsLineItem(line1){}
    TreeLine();

};

#endif // TREELINE_H
