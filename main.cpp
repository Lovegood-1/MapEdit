/*
本项目的唯一主入口 
功能：启动应用，开启窗口 CMapEditTool。CMapEditTool 实例包含了所有计算、显示的功能
下一个功能类：
    CMapEditTool
*/

 
#include "MapEditTool.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CMapEditTool w;
    w.show();
    return a.exec();
}
