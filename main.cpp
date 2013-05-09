#include <QApplication>
#include <QGraphicsView>
#include "myview.h"
#include "myscene.h"
#include "log.h"


int main(int argc, char *argv[])
{
  ns3::LogComponentEnable("MyScene", ns3::LOG_LEVEL_ALL);
  QApplication a(argc, argv);
  myscene s;
  myview v;
  v.setScene(&s);



  v.showMaximized();
  v.show();
  return a.exec();
}
