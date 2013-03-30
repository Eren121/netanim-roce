#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class myscene : public QGraphicsScene
{
public:
    myscene();
    QGraphicsPixmapItem * m_background;
};

#endif // MYSCENE_H
