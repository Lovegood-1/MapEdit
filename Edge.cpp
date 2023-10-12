#include "Edge.h"

CEdge::CEdge()
{
	m_iEdgeId = ERROR_EDGE_ID;
	m_dLength = 0.0;
}

CEdge::CEdge(const CEdge& edge)
{
	m_iEdgeId = edge.m_iEdgeId;
	m_Node1 = edge.m_Node1;
	m_Node2 = edge.m_Node2;
}

CEdge::~CEdge()
{
}
