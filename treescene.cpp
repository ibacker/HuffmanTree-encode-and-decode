#include "treescene.h"
#include "minheap.cpp"
#include <QTime>
#include <QCoreApplication>
TreeScene::TreeScene(int *weight,int num)
{
  this->num = num;
  unVis = 0;
  int n = -num*90;
  for(int i=0;i<num;i++)
  {
      NodeItem *item = new  NodeItem(QString::number(weight[i]));
      vec.append(item);
      item->setPosition(n+90*i,90);
      addItem(item);

  }
}
NodeItem* TreeScene::findMin()
{
    NodeItem *item;
    int i;
    for(i=0;i<vec.size();i++)
    {
        if(!vec.at(i)->isVisited())
        {
            item = vec.at(i);
            break;
        }
    }
    if(i>=vec.size())return NULL;
    for(i=0;i<vec.size();i++)
    {
        int a = vec.at(i)->text.toInt();
        int b = item->text.toInt();
        if(a<b && !vec.at(i)->isVisited()) item = vec.at(i);
    }
    item->setVisit(true);
    return item;
}
void sleep1(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
void TreeScene::createTree()
{
    if(unVis>=num-1)return;
    unVis++;
    NodeItem *first = findMin();
    NodeItem *second = findMin();
    QString num1 = QString::number(first->text.toInt()+second->text.toInt());
    NodeItem *parent = new NodeItem(num1,first,second);
    parent->setPosition(first->getPosition().rx(),first->getPosition().ry()-40);
    second->setRight();
    parent->setColor(Qt::green);
    addItem(parent);
    move(first,second,parent);
    vec.append(parent);
    if(unVis==num-1)
    {
       sleep1(2090);
       cout<<"222"<<endl;
       adjust(parent);
    }

}

void TreeScene::move(NodeItem *first,NodeItem *second,NodeItem *parent)
{

    qreal x1 = first->getPosition().rx(), y1=first->getPosition().ry();
    qreal x2 = second->getPosition().x(), y2=second->getPosition().ry();
    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    QPropertyAnimation *animation=setNodeAnimation(parent,x1,y1-40,x1,y1);
    moveTree(first,x1,y1,x1-30,y1+51.9,group);
    moveTree(second,x2,y2,x1+30,y1+51.9,group);
    group->addAnimation(animation);
    group->start(QAbstractAnimation::DeleteWhenStopped);
    TreeLine *left = new TreeLine(QLineF(x1+15,y1+25,x1-15+5,y1+66.9-5));
    TreeLine *right = new TreeLine(QLineF(x1+15,y1+25,x1+45-5,y1+66.9-5));
    parent->leftLine = left;
    parent->rightLine = right;
    addItem(left);
    addItem(right);
}
void TreeScene::moveTree(NodeItem *item,qreal x1,qreal y1,qreal x2,qreal y2,QParallelAnimationGroup *group)
{
   QPropertyAnimation *animation = setNodeAnimation(item,x1,y1,x2,y2);
   group->addAnimation(animation);
   if(item->leftNode!=NULL && item->rightNode !=NULL)
   {
      // QPropertyAnimation *animation1 = setLineAnimation(item->leftLine,x2+15,y2+25,x2-15+5,y2+66.9-5);
      // QPropertyAnimation *animation2 = setLineAnimation(item->rightLine,x2+15,y2+25,x2+40,y2+66.9-5);
      // group->addAnimation(animation1);
      // group->addAnimation(animation2);
       item->leftLine->setLine(QLineF(x2+15,y2+25,x2-15+5,y2+66.9-5));
       item->rightLine->setLine(QLineF(x2+15,y2+25,x2+40,y2+66.9-5));
       item->leftLine->update();
       item->rightLine->update();
       moveTree(item->leftNode,x1-30,y1+51.9,x2-30,y2+51.9,group);
       moveTree(item->rightNode,x1+30,y1+51.9,x2+30,y2+51.9,group);
   }
}
QPropertyAnimation *TreeScene::setNodeAnimation(NodeItem *item,qreal x1,qreal y1,qreal x2,qreal y2)
{
    QPropertyAnimation *animation= new QPropertyAnimation(item,"pos");
    animation->setDuration(2000);
    animation->setStartValue(QPointF(x1,y1));
    animation->setEndValue(QPointF(x2,y2));
    return animation;
}
QPropertyAnimation *TreeScene::setLineAnimation(TreeLine *item,qreal x1,qreal y1,qreal x2,qreal y2)
{
    QPropertyAnimation *animation= new QPropertyAnimation(item,"pos");
    animation->setDuration(2000);
    cout<<"22222222"<<endl;
    animation->setStartValue(item->line());
    animation->setEndValue(QLineF(x1,y1,x2,y2));
    return animation;
}
void TreeScene::adjust(NodeItem *item)
{
    if(item->isCollided())item->collideMove();
    if(item->leftNode!=NULL && item->rightNode !=NULL)
    {
        adjust(item->leftNode);
        adjust(item->rightNode);
    }
}
