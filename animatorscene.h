#ifndef MYSCENE_H
#define MYSCENE_H

#include "animnode.h"
#include "resizeablepixmap.h"
#include "resizeableitem.h"
#include "timevalue.h"
#include "animpacket.h"
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QLabel>


namespace netanim
{

#define ANIMATORSCENE_USERAREA_WIDTH 250
#define ANIMATORSCENE_USERAREA_HEIGHT 250





class AnimatorScene : public QGraphicsScene
{
Q_OBJECT
public:
    static AnimatorScene * getInstance();
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
    AnimPacket * getTestPacket(uint32_t fromNodeId, uint32_t toNodeId, qreal firstBitTx, qreal propDelay, qreal bitRate);
    void displayPacket(qreal t);

public slots:
    void testSlot();
private:
    qreal m_userAreadWidth;
    qreal m_userAreaHeight;
    TimeValue<AnimPacket *> m_testTimeValue;
    QLabel * m_mousePositionLabel;
    QGraphicsProxyWidget * m_mousePositionProxyWidget;
};

} // namespace netanim

#endif // MYSCENE_H
