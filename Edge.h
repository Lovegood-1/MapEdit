
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
	* �ߵı��
	��ʼ�ڵ��ţ�ֱ���ýڵ����
	�����ڵ���
	����
	*/
	int m_iEdgeId;
	CNode m_iNode1;
	CNode m_iNode2;
	double  m_dLength;


};

#endif // !EDGE_H


