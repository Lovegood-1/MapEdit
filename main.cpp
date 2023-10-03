#include "MapEditTool.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CMapEditTool w;
    w.show();
    return a.exec();
}
