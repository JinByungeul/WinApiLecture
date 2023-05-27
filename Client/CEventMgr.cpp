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
	// ���� �����ӿ��� ��Ƶ� DeadObject ���� ����
	// ============================================
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();	// �޸𸮿��� �����.

	// ==================
	// Event ó��
	// ==================
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		execute(m_vecEvent[i]);
	}
	m_vecEvent.clear();	// �̺�Ʈ�� ó�������� �����.
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
		// Object �� Dead ���·� ����
		// �������� ������Ʈ���� ��Ƶд�.
		CObject* pDeadObj = (CObject*)_evt.lParam;
		pDeadObj->setDead();
		m_vecDead.push_back(pDeadObj);
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
	{
		// lParam : Next Scene Type
		// Scene ����
		CSceneMgr::GetInst()->changeScene((SCENE_TYPE)_evt.lParam);

		// ��Ŀ�� UI ����(���� SCENE �� UI �� ����Ű�� �ֱ� ����)
		//CUIMgr::GetInst()->setFocusedUI(nullptr);
	}
		break;
	}

}
