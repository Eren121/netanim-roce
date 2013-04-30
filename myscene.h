#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPushButton>

class myscene : public QGraphicsScene
{
Q_OBJECT
public:
    myscene();
    QGraphicsPixmapItem * m_background;
    QPushButton * m_testButton;
public slots:
    void testSlot();
};

#endif // MYSCENE_H
