#include "SystemData.h"
 
// ����һ����̬����
CSystemData CSystemData::g_SystemData;

CSystemData* CSystemData::GetSystemData()
{
	return &g_SystemData;
}

 

 

CSystemData::CSystemData()
{
	m_RoadNodeBrush.setColor(QColor(0, 0, 225));
	m_RoadNodeBrush.setStyle(Qt::BrushStyle::SolidPattern);

	m_BuildingNodeBrush.setColor(QColor(225, 0, 0));
	m_BuildingNodeBrush.setStyle(Qt::BrushStyle::SolidPattern);

	m_EdgePen.setColor(QColor(0, 255, 0));
	m_EdgePen.setStyle(Qt::PenStyle::SolidLine);
	m_EdgePen.setWidth(2);

	m_ConnectPen.setColor(QColor(0, 0, 0));
	m_ConnectPen.setStyle(Qt::PenStyle::SolidLine);

	m_EditAreaPen.setColor(QColor(255, 215, 0));
	m_EditAreaPen.setStyle(Qt::PenStyle::SolidLine);
	m_EditAreaPen.setWidth(2);

	m_dRadiusThreshold = CHOSE_POINT_RADIUS;


}

CSystemData::~CSystemData()
{

}