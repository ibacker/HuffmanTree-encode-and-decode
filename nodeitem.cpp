#include "nodeitem.h"
#include <QGraphicsEffect>
#include <QGraphicsBlurEffect>
#include <QGraphicsColorizeEffect>
#include <typeinfo>
NodeItem::NodeItem(QString text,NodeItem *leftNode,NodeItem *rightNode)
{
   isLeft = true;
   point.setX(0);
   point.setY(0);
   Visited = false;
   this->text = text;
   brushColor = Qt::red;
   this->leftNode = leftNode;
   this->rightNode = rightNode;
   leftLine = NULL;
   rightLine = NULL;
   setFlag(QGraphicsItem::ItemIsFocusable);
   setFlag(QGraphicsItem::ItemIsMovable);
   setAcceptHoverEvents(true);
}
QRectF NodeItem::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(0-adjust,0-adjust,30+adjust,30+adjust);
}
void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(hasFocus())
    {
        painter->setPen(QPen(QColor(255,255,255,200)));
    }else
    {
        painter->setPen(QPen(QColor(100,100,100,100)));
    }
    painter->setBrush(brushColor);
    QRectF rect(0,0,30,30);
    painter->drawEllipse(rect);
    painter->setPen(Qt::black);
    painter->drawText(rect,Qt::AlignCenter,text);
}
void NodeItem::keyPressEvent(QKeyEvent *event)
{

   if(event->key()==Qt::Key_Down) moveBy(0,10);
   switch (event->key())
   {
   case Qt::Key_1:{
       QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect;
       blurEffect->setBlurHints(QGraphicsBlurEffect::QualityHint);
       blurEffect->setBlurRadius(8);
       setGraphicsEffect(blurEffect);
       break;}
   case Qt::Key_2:{
       QGraphicsColorizeEffect *colorzeEffect = new QGraphicsColorizeEffect;
       colorzeEffect->setColor(Qt::white);
       colorzeEffect->setStrength(0.6);
       setGraphicsEffect(colorzeEffect);
       break;}
    case Qt::Key_3:{
       QGraphicsDropShadowEffect *drop = new QGraphicsDropShadowEffect;
       drop->setColor(QColor(63,63,63,100));
       drop->setOffset(10);
       setGraphicsEffect(drop);
       break;}
    case Qt::Key_4:{
       QGraphicsOpacityEffect *opact = new QGraphicsOpacityEffect;
       opact->setOpacity(0.4);
       setGraphicsEffect(opact);
       break;}
    case Qt::Key_5:{
       graphicsEffect()->setEnabled(false);
       break;}
   }

}

void NodeItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::OpenHandCursor);
    setToolTip("I Am A Node");
}
void NodeItem::setPosition(qreal ax, qreal ay)
{
    point.setX(ax);
    point.setY(ay);
    setPos(ax,ay);

}
bool NodeItem::isCollided()
{
     QList<QGraphicsItem *> list = collidingItems();
     for(int i=0;i< list.size();i++)
     {
         if(typeid(*list.at(i))==typeid(NodeItem))
         {
             return true;
         }
     }
     return false;
}
void NodeItem::collideMove()
{
    if(isLeft) moveBy(-15,0);
    else moveBy(15,0);
}
