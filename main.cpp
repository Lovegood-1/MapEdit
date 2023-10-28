/**
 * @brief    唯一入口文件
 * @details 
 * @mainpage 下一个文件: MapEditTool.h
 * @date 2023-10-24
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
