#include "SystemData.h"
#include "systemdata2.h"

// ����һ����̬����
CSystemData CSystemData::g_SystemData;

CSystemData* CSystemData::GetSystemData()
{
	return &g_SystemData;
}

CGraph* CSystemData::GetGraph()
{
	return &m_Graph;
}

 

CSystemData::CSystemData()
{
}

CSystemData::~CSystemData()
{

}
