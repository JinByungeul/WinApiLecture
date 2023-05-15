#include "pch.h"
#include "func.h"
#include "CEventMgr.h"

void createObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evt = {};
	evt.eEvent = EVENT_TYPE::CREATE_OBJECT;
	evt.lParam = (DWORD_PTR)_pObj;
	evt.wParam = (DWORD_PTR)_eGroup;

	CEventMgr::GetInst()->addEvent(evt);
}

void deleteObject(CObject* _pObj)
{
	tEvent evt = {};
	evt.eEvent = EVENT_TYPE::DELETE_OBJECT;
	evt.lParam = (DWORD_PTR)_pObj;

	CEventMgr::GetInst()->addEvent(evt);
}

void changeScene(SCENE_TYPE _eNext)
{
	tEvent evt = {};
	evt.eEvent = EVENT_TYPE::SCENE_CHANGE;
	evt.lParam = (DWORD_PTR)_eNext;

	CEventMgr::GetInst()->addEvent(evt);
}
