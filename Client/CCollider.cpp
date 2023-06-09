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

// 자체 복사생성자
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
	// Object의 위치를 따라간다
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

	// 임시 객체 생성(함수 종료 시 자동 소멸)
	SelectGDI p(_hDC, ePen);
	SelectGDI b(_hDC, BRUSH_TYPE::HOLLOW);	// 투명색

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
