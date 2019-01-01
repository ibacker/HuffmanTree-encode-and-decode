#ifndef NODEVIEW_H
#define NODEVIEW_H
#include <QGraphicsItem>
#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QGraphicsLineItem>
#include <QGraphicsSceneContextMenuEvent>
#include <iostream>
#include "treeline.h"
using namespace std;

class NodeItem : public QGraphicsObject
{
private:
    QPointF point;
    QColor brushColor;
    bool Visited;
    bool isLeft;
protected:
    QRectF boundingRect() const;
    void keyPressEvent(QKeyEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
    QString text;
    NodeItem *leftNode;
    NodeItem *rightNode;
    TreeLine *leftLine;
    TreeLine *rightLine;
    NodeItem(QString text,NodeItem *leftNode=NULL,NodeItem *rightNode = NULL);
    NodeItem(){}
    bool isVisited(){return Visited;}
    void setVisit(bool v){ Visited = v;}
    bool isLeftChile(){return isLeft;}
    void setRight(){isLeft = false;}
    void setColor(const QColor &color){brushColor = color;}
    void setPosition(qreal ax, qreal ay);
    QPointF getPosition(){return point;}
    bool isCollided();
    void collideMove();
};

#endif // NODEVIEW_H
