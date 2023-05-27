#include "CUI.h"

#include "CCamera.h"
#include "CKeyMgr.h"
#include "SelectGDI.h"

CUI::CUI(bool _bCamAff)
	: m_pParentUI(nullptr)
	, m_bCamAffected(_bCamAff)
	, m_bMouseOn(false)
{
}

CUI::CUI(const CUI& _origin)	// 깊은 복사생성자
	: m_pParentUI(nullptr)
	, m_bCamAffected(_origin.m_bCamAffected)
	, m_bMouseOn(false)
	, m_bLBtnDown(false)
{
	for (size_t i = 0; i < _origin.m_vecChildUI.size(); ++i)
	{
		addChild(_origin.m_vecChildUI[i]->clone());
	}
}

CUI::~CUI()
{
	safeDeleteVec(m_vecChildUI);
}

void CUI::finalUpdateChild()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->finalUpdate();
	}
}

void CUI::finalUpdate()
{
	CObject::finalUpdate();

	// ui의 최종 위치를 구한다.
	m_vFinalPos = GetPos();
	
	if (getParent())
	{
		Vec2 vParentPos = getParent()->getFinalPos();
		m_vFinalPos += vParentPos;
	}

	// UI Mouse 체크
	checkMouseOn();

	//if (KEY_AWAY(KEY::LBTN))
	//{
	//	m_bMouseOn = false;
	//}

	finalUpdateChild();
}

void CUI::updateChild()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->update();
	}
}

void CUI::checkMouseOn()
{
	Vec2 vMousePos = MOUSE_POS;
	Vec2 vScale = GetScale();

	if (m_bCamAffected)
	{
		vMousePos = CCamera::GetInst()->getRealPos(vMousePos);
	}

	if (m_vFinalPos.x <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + vScale.x
		&& m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + vScale.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}

void CUI::update()
{
	// child ui update
	updateChild();
}

void CUI::renderChild(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}

void CUI::render(HDC _dc)
{
	Vec2 vPos = getFinalPos();
	Vec2 vScale = GetScale();

	if (m_bCamAffected)
	{
		vPos = CCamera::GetInst()->getRenderPos(vPos);
	}

	if (m_bLBtnDown)
	{
		SelectGDI select(_dc, PEN_TYPE::GREEN);

		Rectangle(_dc
			, int(vPos.x)
			, int(vPos.y)
			, int(vPos.x + vScale.x)
			, int(vPos.y + vScale.y));
	}
	else
	{
		Rectangle(_dc
			, int(vPos.x)
			, int(vPos.y)
			, int(vPos.x + vScale.x)
			, int(vPos.y + vScale.y));
	}

	// child ui render
	renderChild(_dc);
}

void CUI::mouseOn()
{
}

void CUI::mouseLBtnDown()
{
}

void CUI::mouseLBtnUp()
{
}

void CUI::mouseLBtnClicked()
{
}
