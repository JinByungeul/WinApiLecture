#include "pch.h"
#include "CUIMgr.h"

#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"

CUIMgr::CUIMgr()
{

}

CUIMgr::~CUIMgr()
{

}

CUI* CUIMgr::getTargetUI(CUI* _pParentUI)
{
	bool bLBtnAway = KEY_AWAY(KEY::LBTN);

	// 1. 부모 UI 포함, 모든 자식들을 검사한다.
	CUI* pTargetUI = nullptr;

	// 자주 사용되는 애들은 정적변수로 선언
	static list<CUI*> queue;
	static vector<CUI*> vecNonTarget;

	queue.clear();
	vecNonTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// 큐에서 데이터 하나 꺼내기
		CUI* pUI = queue.front();
		queue.pop_front();

		// 큐에서 꺼내온 UI가 TargetUI 인지 확인
		// 타겟 UI 들 중, 더 우선순위가 높은 기준은 더 낮은 계층의 자식 UI
		if (pUI->isMouseOn())
		{
			if (nullptr != pTargetUI)
			{
				vecNonTarget.push_back(pTargetUI);
			}

			pTargetUI = pUI;
		}
		else
		{
			vecNonTarget.push_back(pUI);
		}
		
		const vector<CUI*> vecChild = pUI->getChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
	}

	// 왼쪽버튼 떼면, 눌렸던 체크를 다시 해제
	if (bLBtnAway)
	{
		// 타겟팅 안된 애들만 모아서 
		for (size_t i = 0; i < vecNonTarget.size(); ++i)
		{
			vecNonTarget[i]->m_bLBtnDown = false;
		}
	}

	return pTargetUI;
}

void CUIMgr::update()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);

	bool bLBtnTap = KEY_TAP(KEY::LBTN);
	bool bLBtnAway = KEY_AWAY(KEY::LBTN);
	
	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		CUI* pUI = (CUI*)vecUI[i];

		// 부모 UI 포함, 자식 UI 들 중 실제 타겟팅 된 UI 를 가져온다
		pUI = getTargetUI(pUI);	

		if (nullptr != pUI)
		{
			pUI->mouseOn();

			if (bLBtnTap)
			{
				pUI->mouseLBtnDown();
				pUI->m_bLBtnDown = true;
			}
			else if (bLBtnAway)
			{
				pUI->mouseLBtnUp();

				if (pUI->m_bLBtnDown)
				{
					pUI->mouseLBtnClicked();
				}
				
				// 왼쪽 버튼 떼면, 눌렸던 체크를 다시 해제
				pUI->m_bLBtnDown = false;
			}
		}
	}
}
