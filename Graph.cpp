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

int CGraph::LoadFile(const QString& qstrFilePath)
{
	if (!QFile(qstrFilePath).exists())				   return FILE_NOT_FOUND;
  
	QFile file(qstrFilePath);
	if (!file.open(QIODevice::OpenModeFlag::ReadOnly)) return OPEN_FILE_FAILED;

	m_NodeVec.clear();
	m_EdgeVec.clear();
	m_NodeVec.shrink_to_fit();
	m_EdgeVec.shrink_to_fit();

	int iSize = 0;
	bool bBuilding = false;
	QDataStream stream(&file);
	// 1, 读取节点
	stream >> iSize;
	for (int i = 0; i < iSize; i++)
	{
		CNode node;
		stream >> bBuilding;
		node.m_NodeType = bBuilding ? NodeType::Node_Building : NodeType::Node_Road;
		stream >> node.m_iNodeId >> node.m_dNodePosX >> node.m_dNodePosY >> node.m_qstrNodeName;
		m_NodeVec.push_back(node);
	}

	stream >> iSize;
	for (int i = 0; i < iSize; i++)
	{
		CEdge edge;
		stream >> edge.m_iEdgeId;
		CNode node1, node2;

		stream >> bBuilding;
		stream >> edge.m_Node1.m_iNodeId >> edge.m_Node1.m_dNodePosX >> edge.m_Node1.m_dNodePosY >> edge.m_Node1.m_qstrNodeName;
		edge.m_Node1.m_NodeType = bBuilding ? NodeType::Node_Building : NodeType::Node_Road;

		
		stream >> bBuilding;
		stream >> edge.m_Node2.m_iNodeId >> edge.m_Node2.m_dNodePosX >> edge.m_Node2.m_dNodePosY >> edge.m_Node2.m_qstrNodeName;
		edge.m_Node2.m_NodeType = bBuilding ? NodeType::Node_Building : NodeType::Node_Road;

		m_EdgeVec.push_back(edge);
	}

	stream >> m_iMaxNodeId >> m_iMaxEdgeId;
	stream >> m_MapImage;
	file.close();

	return NORMAL_RETURN;
}

int CGraph::SaveData(const QString& qstrFilePath)
{
	// 1 检测文件合法性
	QFile file(qstrFilePath);
	if (!file.open(QIODevice::OpenModeFlag::WriteOnly | QIODevice::OpenModeFlag::Truncate))
		return OPEN_FILE_FAILED;
	QDataStream stream(&file);

	// 2 放入节点
	stream << m_NodeVec.size();
	QVector<CNode>::const_iterator citn = m_NodeVec.constBegin();
	while (citn!=m_NodeVec.constEnd())
	{
		

		stream << (citn->m_NodeType == NodeType::Node_Building);
		stream << citn->m_iNodeId << citn->m_dNodePosX << citn->m_dNodePosY << citn->m_qstrNodeName;
		citn++;
	}

	// 3 放入边
	stream << m_EdgeVec.size();
	auto cite = m_EdgeVec.constBegin();
	while (cite != m_EdgeVec.constEnd())
	{
		stream << cite->m_iEdgeId;
		stream << (cite->m_Node1.m_NodeType == NodeType::Node_Building);
		stream << cite->m_Node1.m_iNodeId << cite->m_Node1.m_dNodePosX << cite->m_Node1.m_dNodePosY << cite->m_Node1.m_qstrNodeName;
		stream << (cite->m_Node2.m_NodeType == NodeType::Node_Building);
		stream << cite->m_Node2.m_iNodeId << cite->m_Node2.m_dNodePosX << cite->m_Node2.m_dNodePosY << cite->m_Node2.m_qstrNodeName;
		cite++;
	}

	stream << m_iMaxNodeId << m_iMaxEdgeId;
	stream << m_MapImage;

	file.close();

	return NORMAL_RETURN;
}
