/*
����Ŀ��Ψһ����� 
���ܣ�����Ӧ�ã��������� CMapEditTool��CMapEditTool ʵ�����������м��㡢��ʾ�Ĺ���
��һ�������ࣺ
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
