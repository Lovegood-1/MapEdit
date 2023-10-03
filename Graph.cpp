#include "Graph.h"


CGraph::CGraph()
{
	m_iMaxEdgeId = 1;
	m_iMaxNodeId = 1;

	m_MapImage = QImage(300, 300, QImage::Format::Format_RGB888);
	m_MapImage.fill(QColor(0, 255, 255));
}

CGraph::~CGraph()
{
	m_NodeVec.clear();
	m_NodeVec.shrink_to_fit();
	m_EdgeVec.clear();
	m_EdgeVec.shrink_to_fit();
}
