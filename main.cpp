#include <QApplication>
#include <QGraphicsView>
#include "myview.h"
#include "animatorscene.h"
#include "log.h"
#include "netanim.h"

using namespace ns3;
using namespace netanim;

int main(int argc, char *argv[])
{
  ns3::LogComponentEnable("AnimatorScene", ns3::LOG_LEVEL_ALL);
  ns3::LogComponentEnable("AnimatorView", ns3::LOG_LEVEL_ALL);
  ns3::LogComponentEnable("AnimNode", ns3::LOG_LEVEL_ALL);
  ns3::LogComponentEnable("AnimPacket", ns3::LOG_LEVEL_ALL);
  ns3::LogComponentEnable("AnimatorMode", ns3::LOG_LEVEL_ALL);
  ns3::LogComponentEnable("ResizeableItem", ns3::LOG_LEVEL_ALL);


  QApplication app(argc, argv);
  app.setApplicationName("NetAnim");
  NetAnim netAnim;
  return app.exec();


}
