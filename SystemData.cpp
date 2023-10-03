#include "SystemData.h"
#include "systemdata2.h"

// 定义一个静态对象
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
