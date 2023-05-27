#include "CUI.h"

CUI::CUI()
	: m_pParentUI(nullptr)
{
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

	finalUpdateChild();
}

void CUI::updateChild()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->update();
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

	Rectangle(_dc
		, int(vPos.x)
		, int(vPos.y)
		, int(vPos.x + vScale.x)
		, int(vPos.y + vScale.y));

	// child ui render
	renderChild(_dc);
}

void CUI::mouseOn()
{
}

void CUI::mouseLDown()
{
}

void CUI::mouseLUp()
{
}

void CUI::mouseClicked()
{
}
