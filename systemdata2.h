#ifndef SYSTEMDATA_H
#define SYSTEMDATA_H

#include "Graph.h"

class CSystemData2
{
public:
	static CSystemData2* GetSystemData();
	CGraph* GetGraph();

public:
	CSystemData2();
	~CSystemData2();



private:
	static CSystemData2 g_SystemData;
 
};


#endif // !SYSTEMDATA_H
 
