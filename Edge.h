
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
	* �ߵı��
	��ʼ�ڵ��ţ�ֱ���ýڵ����
	�����ڵ���
	����
	*/
	int m_iEdgeId;
	CNode m_Node1;
	CNode m_Node2;
	double  m_dLength;
private:

};

#endif // !EDGE_H


