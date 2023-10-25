/**
 * @brief     重要数据类型
 * @details   图数据类型，向下包括节点数据类型和边数据类型。
 * @mainpage  MapDisplay.cpp -> this file -> Node.cpp Edge.cpp
 * @date 2023-10-24
 */


#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include "Edge.h"
#include "Macro.h"

#include <QFile>
#include <QVector>
#include <QImage>
#include <QDataStream>

class CGraph
{
public:
	CGraph();
	~CGraph();

	int LoadFile(const QString & qstrFilePath);
	int SaveData(const QString& qstrFilePath);


public:
	QImage		  m_MapImage;


	QVector<CNode> m_NodeVec;
	QVector<CEdge> m_EdgeVec;

	int			   m_iMaxNodeId;
	int			   m_iMaxEdgeId;
};


#endif // !GRAPH_H
