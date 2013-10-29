#ifndef MODE_H
#define MODE_H
#include <stdint.h>
#include <QWidget>

class Mode: public QWidget
{
public:
    virtual void setFocus(bool focus) = 0;
};
#endif // MODE_H
