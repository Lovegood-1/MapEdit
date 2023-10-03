#ifndef SYSTEMDATA_H
#define SYSTEMDATA_H

#include "Graph.h"

class CSystemData
{
public:
	static CSystemData* GetSystemData();
	CGraph* GetGraph();
	 

public:
	CSystemData();
	~CSystemData();



private:
	static CSystemData g_SystemData;
 	CGraph			   m_Graph;
};


#endif // !SYSTEMDATA_H
