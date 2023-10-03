#ifndef NODE_H
#define NODE_H

#include "Macro.h"
#include <QString>

enum class NodeType
{
	Node_Road = 0,
	Node_Road_ = 1
};

class CNode
{
public:
	CNode();
	CNode(const CNode& node); 
	~CNode();

private:
	NodeType m_NodeType;
	int m_iNodeId;
	double m_dNodePosX;
	double m_dNodePosY;
	QString m_qstrNodeName;
 


};


#endif // !NODE_H
