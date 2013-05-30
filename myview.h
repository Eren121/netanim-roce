#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>
#include <QGraphicsItem>



class myview : public QGraphicsView
{
    Q_OBJECT
public:
    explicit myview(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    
signals:
    
public slots:
    
};

#endif // MYVIEW_H
