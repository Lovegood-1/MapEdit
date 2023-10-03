#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include "Edge.h"
#include "Macro.h"

#include <QVector>
#include <QImage>

class CGraph
{
public:
	CGraph();
	~CGraph();


public:
	QImage		  m_MapImage;


	QVector<CNode> m_NodeVec;
	QVector<CEdge> m_EdgeVec;

	int			   m_iMaxNodeId;
	int			   m_iMaxEdgeId;
};


#endif // !GRAPH_H
