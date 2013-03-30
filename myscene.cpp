#include "myscene.h"

myscene::myscene()
{
    QPixmap pix("/Users/john/ns-3/newcanvas1/ns3logo2.png","png");
    m_background = addPixmap(pix);

}
