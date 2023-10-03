#include "Edge.h"

CEdge::CEdge()
{
	m_iEdgeId = ERROR_EDGE_ID;
	m_dLength = 0.0;
}

CEdge::CEdge(const CEdge& edge)
{
	m_iEdgeId = edge.m_iEdgeId;
	m_iNode1 = edge.m_iNode1;
	m_iNode2 = edge.m_iNode2;
}

CEdge::~CEdge()
{
}
