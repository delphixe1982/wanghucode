#include "StdAfx.h"
#include "Tableframesink.h"
#include "GameServerManager.h"
#include "..\消息定义\CMD_LLShow.h"

//////////////////////////////////////////////////////////////////////////

//全局变量
static CGameServiceManager			g_GameServiceManager;				//管理变量

//////////////////////////////////////////////////////////////////////////

//构造函数
CGameServiceManager::CGameServiceManager(void)
{
	//设置属性
	m_GameServiceAttrib.wKindID=KIND_ID;
	m_GameServiceAttrib.wChairCount=GAME_PLAYER;
	lstrcpyn(m_GameServiceAttrib.szKindName,GAME_NAME,CountArray(m_GameServiceAttrib.szKindName));
	lstrcpyn(m_GameServiceAttrib.szDataBaseName,TEXT("QPLLShowDB"),CountArray(m_GameServiceAttrib.szDataBaseName));
	lstrcpyn(m_GameServiceAttrib.szDescription,TEXT("连连看服务组件"),CountArray(m_GameServiceAttrib.szDescription));
	lstrcpyn(m_GameServiceAttrib.szServerModuleName,TEXT("LLShowServer.DLL"),CountArray(m_GameServiceAttrib.szServerModuleName));
	lstrcpyn(m_GameServiceAttrib.szClientModuleName,TEXT("LLShow.EXE"),CountArray(m_GameServiceAttrib.szClientModuleName));

	return;
}

//析构函数
CGameServiceManager::~CGameServiceManager(void)
{
}

//接口查询
void * __cdecl CGameServiceManager::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IGameServiceManager,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IGameServiceManager,Guid,dwQueryVer);
	return NULL;
}

//创建游戏桌
void * __cdecl CGameServiceManager::CreateTableFrameSink(const IID & Guid, DWORD dwQueryVer)
{
	//建立对象
	CTableFrameSink * pTableFrameSink=NULL;
	try
	{
		pTableFrameSink=new CTableFrameSink();
		if (pTableFrameSink==NULL) throw TEXT("创建失败");
		void * pObject=pTableFrameSink->QueryInterface(Guid,dwQueryVer);
		if (pObject==NULL) throw TEXT("接口查询失败");
		return pObject;
	}
	catch (...) {}

	//清理对象
	SafeDelete(pTableFrameSink);

	return NULL;
}

//获取属性
void __cdecl CGameServiceManager::GetGameServiceAttrib(tagGameServiceAttrib & GameServiceAttrib)
{
	GameServiceAttrib=m_GameServiceAttrib;
	return;
}

//参数修改
bool __cdecl CGameServiceManager::RectifyServiceOption(tagGameServiceOption * pGameServiceOption)
{
	//效验参数
	ASSERT(pGameServiceOption!=NULL);
	if (pGameServiceOption==NULL) return false;

	//单元积分
	pGameServiceOption->lCellScore=__max(1L,pGameServiceOption->lCellScore);

	//积分下限
	if (pGameServiceOption->wServerType!=GAME_GENRE_SCORE)
	{
		pGameServiceOption->lLessScore=__max(1L,pGameServiceOption->lLessScore);
	}

	//输分限制(原来的积分上限)
	if (pGameServiceOption->lRestrictScore!=0L)
	{
		pGameServiceOption->lRestrictScore=__max(pGameServiceOption->lRestrictScore,pGameServiceOption->lLessScore);
	}

	//积分上限
	if (pGameServiceOption->wServerType!=GAME_GENRE_SCORE)
	{
		if(pGameServiceOption->lMaxScore<=pGameServiceOption->lLessScore)
			pGameServiceOption->lMaxScore=0L;
		else if(pGameServiceOption->lRestrictScore>0)
			pGameServiceOption->lMaxScore=__min(pGameServiceOption->lMaxScore,pGameServiceOption->lRestrictScore);
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////

//建立对象函数
extern "C" __declspec(dllexport) void * __cdecl CreateGameServiceManager(const GUID & Guid, DWORD dwInterfaceVer)
{
	return g_GameServiceManager.QueryInterface(Guid,dwInterfaceVer);
}

//////////////////////////////////////////////////////////////////////////
