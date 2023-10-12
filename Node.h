#ifndef NODE_H
#define NODE_H

#include "Macro.h"
#include <QString>

enum class NodeType
{
	Node_Road = 0,
	Node_Building = 1
};

class CNode
{
public:
	CNode();

	CNode(const CNode& node); 
	~CNode();

	bool operator == (const CNode& data) const;
	bool operator != (const CNode& data) const;

	inline void setNodeId(int i) { m_iNodeId = i; }
	inline void setNodePosX(double x) { m_dNodePosX = x; }
	inline void setNodePosY(double y) { m_dNodePosY = y; }
	inline void setNodeType(NodeType t) { m_NodeType = t; }
	inline void setNodeName(QString m_qstrNodeName_) { m_qstrNodeName = m_qstrNodeName_; }

 
	NodeType m_NodeType;
	int m_iNodeId;
	double m_dNodePosX;
	double m_dNodePosY;
	QString m_qstrNodeName;



};


#endif // !NODE_H
