#ifndef MYSCENE_H
#define MYSCENE_H

#include "animnode.h"
#include "animlink.h"
#include "resizeablepixmap.h"
#include "resizeableitem.h"
#include "timevalue.h"
#include "animpacket.h"
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QLabel>
#include <QVector>


namespace netanim
{

#define ANIMATORSCENE_USERAREA_WIDTH 250
#define ANIMATORSCENE_USERAREA_HEIGHT 250


class AnimInterfaceText : public QGraphicsTextItem
{
public:
    typedef enum textMode {
        NONE,
        IPV4,
        MAC,
        BOTH
    } TextMode_t;

    AnimInterfaceText(QString description, bool leftAligned=false);
    ~AnimInterfaceText();
    enum { Type = ANIMINTERFACE_TEXT_TYPE };
    int type () const
    {
        return Type;
    }
    QPainterPath shape() const;
    bool setLine(QLineF l);
    QGraphicsLineItem * getLine();
    void setMode(bool showIpv4, bool showMac);
    QString getText() const;
    void setLeftAligned(bool leftAligned);

private:
    bool m_leftAligned;
    QGraphicsLineItem * m_line;
    TextMode_t m_mode;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};



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
    void addPacket (AnimPacket * p);
    void addNode (AnimNode * animNode);
    void addLink (AnimLink * animLink);
    void addWirelessCircle (AnimWirelessCircles * w);
    void purgeAnimatedPackets();
    void showAnimatedPackets(bool show);
    void purgeAnimatedNodes();
    void purgeAnimatedLinks();
    void setShowInterfaceTexts(bool showIp, bool showMac);
    void addGrid();
    void resetGrid();
    QRectF getBoundaryRect();
    void setGridLinesCount(int nGridLines);



public slots:
    void testSlot();
private:
    typedef QVector <AnimInterfaceText *>          AnimInterfaceTextVector_t;
    typedef QVector <QGraphicsLineItem *>          LineItemVector_t;
    typedef QVector <QGraphicsSimpleTextItem*>     GridCoordinatesVector_t;

    qreal m_userAreadWidth;
    qreal m_userAreaHeight;
    TimeValue<AnimPacket *> m_testTimeValue;
    QLabel * m_mousePositionLabel;
    QGraphicsProxyWidget * m_mousePositionProxyWidget;
    QVector <AnimPacket *> m_animatedPackets;
    QVector <AnimWirelessCircles *> m_animatedWirelessCircles;
    QVector <AnimLink *> m_animatedLinks;
    QVector<AnimNode *> m_animatedNodes;
    bool            m_showIpInterfaceTexts;
    bool            m_showMacInterfaceTexts;
    AnimInterfaceTextVector_t    m_interfaceATexts;
    AnimInterfaceTextVector_t    m_interfaceBTexts;
    qreal m_leftTop;
    qreal m_rightTop;
    QList <QGraphicsItem *> getInterfaceTextCollisionList(AnimInterfaceText * text);
    qreal           m_gridStep;
    bool            m_showGrid;
    int             m_nGridLines;
    LineItemVector_t             m_gridLines;
    GridCoordinatesVector_t      m_gridCoordinates;
    QRectF m_boundaryRect;


    void repositionInterfaceText(AnimInterfaceText * textItem);
    void resetInterfaceTexts();
    void removeInterfaceTextCollision();
    void resetInterfaceTextTop();

    void markGridCoordinates();
    void initGridCoordinates();
    QVector <QGraphicsSimpleTextItem *> getGridCoordinatesItems();
    void setMousePositionLabel(QPointF pos);
    void showMousePositionLabel(bool show);







};

} // namespace netanim

#endif // MYSCENE_H
