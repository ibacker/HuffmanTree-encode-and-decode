#ifndef TREESCENE_H
#define TREESCENE_H
#include <QGraphicsScene>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include "minheap.h"
#include "nodeitem.h"
class TreeScene : public QGraphicsScene
{
private:
    QVector<NodeItem *> vec;
    int num;
    int unVis;
    NodeItem *root;
public:
    TreeScene(int *weight,int num);
    NodeItem *findMin();
    void createTree();
    void move(NodeItem *first,NodeItem *second,NodeItem *parent);
    void moveTree(NodeItem *item,qreal x1,qreal y1,qreal x2,qreal y2,QParallelAnimationGroup *group);
    QPropertyAnimation *setNodeAnimation(NodeItem *item,qreal x1,qreal y1,qreal x2,qreal y2);
    QPropertyAnimation *setLineAnimation(TreeLine *item,qreal x1,qreal y1,qreal x2,qreal y2);
    void adjust(NodeItem *item);
};

#endif // TREESCENE_H
