#include "Node.h"

 CNode::CNode()
{
	qDebug("use con fun\n");
	std::cout << "use construction fun" << std::endl;
	m_NodeType = NodeType::Node_Road;
	m_iNodeId = ERROR_NODE_ID;
	m_dNodePosX = INIT_NODE_POS_X;
	m_dNodePosY = INIT_NODE_POS_Y;
}


// TODO : 可以设计一个移动构造函数
CNode::CNode(const CNode& data)
{

	qDebug("use copy fun\n");    //方式2
	//std::cout << "use copy fun" << std::endl;
	m_NodeType	= data.m_NodeType;
	m_iNodeId	= data.m_iNodeId;
	m_dNodePosX = data.m_dNodePosX;
	m_dNodePosY = data.m_dNodePosY;
	m_qstrNodeName = data.m_qstrNodeName;
}

/*
CNode::CNode(CNode&& node)
{
	std::cout << "use move fun" << std::endl;
}
*/
CNode::~CNode()
{
}

bool CNode::operator==(const CNode& data) const
{
	if(m_NodeType		!=data.m_NodeType	|| 
		m_iNodeId		!= data.m_iNodeId   ||
		m_dNodePosX		!= data.m_dNodePosX ||
		m_dNodePosY		!= data.m_dNodePosY ||
		m_qstrNodeName  != data.m_qstrNodeName)
		return false;
	return true;
}

bool CNode::operator!=(const CNode& data) const
{
	if (m_NodeType		== data.m_NodeType	&&
		m_iNodeId		== data.m_iNodeId	&&
		m_dNodePosX		== data.m_dNodePosX &&
		m_dNodePosY		== data.m_dNodePosY &&
		m_qstrNodeName  == data.m_qstrNodeName)
		return false;
	return true;
}
