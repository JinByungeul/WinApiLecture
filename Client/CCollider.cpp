#include "pch.h"
#include "CCollider.h"
#include "CObject.h"
#include "CCore.h"
#include "SelectGDI.h"

CCollider::CCollider()
	: m_pOwner(nullptr)
{
}

CCollider::~CCollider()
{
}

void CCollider::finalUpdate()
{
	// Object�� ��ġ�� ���󰣴�
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;
}

void CCollider::render(HDC _hDC)
{
	// �ӽ� ��ü ����(�Լ� ���� �� �ڵ� �Ҹ�)
	SelectGDI p(_hDC, PEN_TYPE::GREEN);
	SelectGDI b(_hDC, BRUSH_TYPE::HOLLOW);

	Rectangle(_hDC
		, (int)(m_vFinalPos.x - m_vScale.x / 2.f)
		, (int)(m_vFinalPos.y - m_vScale.y / 2.f)
		, (int)(m_vFinalPos.x + m_vScale.x / 2.f)
		, (int)(m_vFinalPos.y + m_vScale.y / 2.f));
}
