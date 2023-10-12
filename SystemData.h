#ifndef SYSTEMDATA_H
#define SYSTEMDATA_H

#include "Graph.h"

#include <QPen>
#include <QBrush>
class CSystemData
{
public:
	static CSystemData* GetSystemData();

	inline void			 SetRoadNodeBrush(const QBrush& brush) { m_RoadNodeBrush = brush; }
	inline void			 SetBuildingNodeBrush(const QBrush& brush) { m_BuildingNodeBrush = brush; }
	inline void			 SetRadiusThreahold(const double& dThreshold) { m_dRadiusThreshold = dThreshold; }
	inline void			 SetEdgePen(const QPen& pen) { m_EdgePen = pen; }
	inline void			 SetConnectPen(const QPen& pen) { m_ConnectPen = pen; }
	inline void			 SetEditAreaPen(const QPen& pen) { m_EditAreaPen = pen; }
	inline CGraph*		 GetGraph() { return &m_Graph; };
	inline const QPen&	 GetConnectPen() const { return m_ConnectPen; }
	inline const QPen&   GetEdgePen() const { return m_EdgePen; }
	inline const QPen&   GetEditAreaPen() const { return m_EditAreaPen; }
	inline const QBrush& GetRoadNodeBrush() const { return m_RoadNodeBrush; }
	inline const QBrush& GetBuildingNodeBrush() const { return m_BuildingNodeBrush; }
	inline const double& GetRadiusThreshold() const { return m_dRadiusThreshold; }

public:
	CSystemData();
	~CSystemData();



private:
	static CSystemData g_SystemData;
 	CGraph			   m_Graph;
	QBrush			   m_RoadNodeBrush;
	QBrush             m_BuildingNodeBrush;
	QPen			   m_EdgePen;
	QPen			   m_ConnectPen;
	QPen			   m_EditAreaPen;
	double			   m_dRadiusThreshold;
};


#endif // !SYSTEMDATA_H
