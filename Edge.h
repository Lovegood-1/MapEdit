
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


	/*
	* 边的编号
	开始节点编号，直接用节点对象
	结束节点编号
	长度
	*/
	int m_iEdgeId;
	CNode m_Node1;
	CNode m_Node2;
	double  m_dLength;
private:

};

#endif // !EDGE_H


