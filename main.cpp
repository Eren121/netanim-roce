#include <QApplication>
#include <QGraphicsView>
#include "myview.h"
#include "animatorscene.h"
#include "log.h"

using namespace ns3;

int main(int argc, char *argv[])
{
  ns3::LogComponentEnable("AnimatorScene", ns3::LOG_LEVEL_ALL);
  ns3::LogComponentEnable("MyView", ns3::LOG_LEVEL_ALL);
  ns3::LogComponentEnable("AnimNode", ns3::LOG_LEVEL_ALL);
  QApplication a(argc, argv);
  AnimatorScene s;
  myview v;
  v.setScene(&s);

  //qDebug(QString::number(sizeof(int)).toAscii().data());
  //qDebug(QString::number(sizeof(int*)).toAscii().data());


  v.setGeometry(0, 0, 500, 500);
  //v.showMaximized();
  v.showMinimized();
  v.show();
  return a.exec();
}
