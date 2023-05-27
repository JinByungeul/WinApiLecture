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

	// 1. �θ� UI ����, ��� �ڽĵ��� �˻��Ѵ�.
	CUI* pTargetUI = nullptr;

	// ���� ���Ǵ� �ֵ��� ���������� ����
	static list<CUI*> queue;
	static vector<CUI*> vecNonTarget;

	queue.clear();
	vecNonTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// ť���� ������ �ϳ� ������
		CUI* pUI = queue.front();
		queue.pop_front();

		// ť���� ������ UI�� TargetUI ���� Ȯ��
		// Ÿ�� UI �� ��, �� �켱������ ���� ������ �� ���� ������ �ڽ� UI
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

	// ���ʹ�ư ����, ���ȴ� üũ�� �ٽ� ����
	if (bLBtnAway)
	{
		// Ÿ���� �ȵ� �ֵ鸸 ��Ƽ� 
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

		// �θ� UI ����, �ڽ� UI �� �� ���� Ÿ���� �� UI �� �����´�
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
				
				// ���� ��ư ����, ���ȴ� üũ�� �ٽ� ����
				pUI->m_bLBtnDown = false;
			}
		}
	}
}
