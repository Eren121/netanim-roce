#ifndef MYSCENE_H
#define MYSCENE_H

#include "animnode.h"
#include "resizeablepixmap.h"
#include "resizeableitem.h"
#include "timevalue.h"
#include "animpacket.h"
#include <QGraphicsScene>
#include <QPushButton>


#define ANIMATORSCENE_USERAREA_WIDTH 1024
#define ANIMATORSCENE_USERAREA_HEIGHT 1024





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
    void setUserAreaWidth(qreal w);
    void setUserAreaHeight(qreal h);
    void prepareTimeValueData();
    AnimPacket * getTestPacket(qreal firstBitTx, qreal propDelay, qreal bitRate);
    void displayPacket(qreal t);
public slots:
    void testSlot();
private:
    qreal m_userAreadWidth;
    qreal m_userAreaHeight;
    TimeValue<AnimPacket *> m_testTimeValue;
};

#endif // MYSCENE_H
