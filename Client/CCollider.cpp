#include "pch.h"
#include "CCollider.h"
#include "CObject.h"
#include "CCore.h"
#include "SelectGDI.h"
#include "CCamera.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++)
	, m_iCol(0)
{
}

// ��ü ���������
CCollider::CCollider(const CCollider& _origin)
	: m_pOwner(nullptr)
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_vScale(_origin.m_vScale)
	, m_iID(g_iNextID++)
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

	assert(0 <= m_iCol);
}

void CCollider::render(HDC _hDC)
{
	PEN_TYPE ePen = PEN_TYPE::GREEN;

	if (m_iCol > 0)
	{
		ePen = PEN_TYPE::RED;
	}

	// �ӽ� ��ü ����(�Լ� ���� �� �ڵ� �Ҹ�)
	SelectGDI p(_hDC, ePen);
	SelectGDI b(_hDC, BRUSH_TYPE::HOLLOW);	// �����

	Vec2 vRenderPos = CCamera::GetInst()->getRenderPos(m_vFinalPos);

	Rectangle(_hDC
		, (int)(vRenderPos.x - m_vScale.x / 2.f)
		, (int)(vRenderPos.y - m_vScale.y / 2.f)
		, (int)(vRenderPos.x + m_vScale.x / 2.f)
		, (int)(vRenderPos.y + m_vScale.y / 2.f));
}

void CCollider::OnCollision(CCollider* _pOther)
{
	m_pOwner->onCollision(_pOther);
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
	++m_iCol;
	m_pOwner->onCollisionEnter(_pOther);
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	--m_iCol;
	m_pOwner->onCollisionExit(_pOther);
}
