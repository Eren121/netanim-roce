#ifndef MYSCENE_H
#define MYSCENE_H

#include "animnode.h"
#include "resizeablepixmap.h"
#include "resizeableitem.h"

#include <QGraphicsScene>
#include <QPushButton>




void QDEBUG(QPointF p, QString prefix = "");
void QDEBUG(QString str);




class AnimatorScene : public QGraphicsScene
{
Q_OBJECT
public:
    AnimatorScene();
    ResizeablePixmap * m_background;
    //ResizeablePixmap * m_pItem;
    AnimNode * m_pItem;
    QPushButton * m_testButton;
    void addPix();
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
public slots:
    void testSlot();
};

#endif // MYSCENE_H
