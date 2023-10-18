#ifndef SYSTEMDATA_H
#define SYSTEMDATA_H

#include "Graph.h"

#include <QPen>
#include <QBrush>
#include <QFont>
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
	inline void			 SetShowNodeId(const bool& bShow) { m_bShowNodeId = bShow; }
	inline void			 SetNodeIdFont(const QFont& font) { m_NodeIdFont = font; }
	inline void			 SetNodeIdPen(const QPen& pen) { m_NodeIdPen = pen; }
	inline CGraph*		 GetGraph() { return &m_Graph; };
	inline const bool    GetShowNodeId()const { return m_bShowNodeId; }
	inline const QPen&	 GetConnectPen() const { return m_ConnectPen; }
	inline const QPen&   GetEdgePen() const { return m_EdgePen; }
	inline const QPen&   GetEditAreaPen() const { return m_EditAreaPen; }
	inline const QBrush& GetRoadNodeBrush() const { return m_RoadNodeBrush; }
	inline const QBrush& GetBuildingNodeBrush() const { return m_BuildingNodeBrush; }
	inline const double& GetRadiusThreshold() const { return m_dRadiusThreshold; }
	inline const QFont&  GetNodeIdFont() const { return m_NodeIdFont; }
	inline const QPen&   GetNodeIdPen() const { return m_NodeIdPen; }

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
	bool			   m_bShowNodeId;			 QFont m_NodeIdFont;            // 是否显示节点编号以及编号字体
	QPen			   m_NodeIdPen;    // 节点编号画笔
};


#endif // !SYSTEMDATA_H
