#include "pch.h"
#include "CEventMgr.h"
#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"

CEventMgr::CEventMgr()
	:m_vecEvent{}
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::update()
{
	// ============================================
	// 이전 프레임에서 모아둔 DeadObject 들을 삭제
	// ============================================
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();	// 메모리에서 지운다.

	// ==================
	// Event 처리
	// ==================
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		execute(m_vecEvent[i]);
	}
	m_vecEvent.clear();	// 이벤트를 처리했으면 지운다.
}

void CEventMgr::execute(const tEvent& _evt)
{
	switch (_evt.eEvent)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : Object Address
		// wParam : Group Type
		CObject* pNewObj = (CObject*)_evt.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_evt.wParam;

		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lpParam : Object Address
		// Object 를 Dead 상태로 변경
		// 삭제예정 오브젝트들을 모아둔다.
		CObject* pDeadObj = (CObject*)_evt.lParam;
		pDeadObj->setDead();
		m_vecDead.push_back(pDeadObj);
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
	{
		// lParam : Next Scene Type
		// Scene 변경
		CSceneMgr::GetInst()->changeScene((SCENE_TYPE)_evt.lParam);

		// 포커스 UI 해제(이전 SCENE 의 UI 를 가리키고 있기 때문)
		//CUIMgr::GetInst()->setFocusedUI(nullptr);
	}
		break;
	}

}
