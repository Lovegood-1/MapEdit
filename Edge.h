
#ifndef EDGE_H
#define EDGE_H

#include "Macro.h"
#include "Node.h"

class CEdge
{
public:
	CEdge();
	CEdge(const CEdge& edge);
	~CEdge();

private:
	/*
	* 边的编号
	开始节点编号，直接用节点对象
	结束节点编号
	长度
	*/
	int m_iEdgeId;
	CNode m_iNode1;
	CNode m_iNode2;
	double  m_dLength;


};

#endif // !EDGE_H


