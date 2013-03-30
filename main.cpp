#include <QApplication>
#include <QGraphicsView>
#include "myview.h"
#include "myscene.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  myscene s;
  myview v;
  v.setScene(&s);



  v.showMaximized();
  v.show();
  return a.exec();
}
