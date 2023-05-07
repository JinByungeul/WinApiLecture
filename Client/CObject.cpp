#include "pch.h"

#include "CObject.h"
#include "CCollider.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
	, m_pCollider(nullptr)
	, m_bAlive(true)
{
}

CObject::~CObject()
{
	if (nullptr != m_pCollider)
		delete m_pCollider;
}

void CObject::finalUpdate()
{
	if (m_pCollider)
		m_pCollider->finalUpdate();
}

void CObject::render(HDC _dc)
{
	// ������Ʈ �ڽ��� �׸���
	Rectangle(_dc, (int)(m_vPos.x - m_vScale.x / 2.f), (int)(m_vPos.y - m_vScale.y / 2.f)
				 , (int)(m_vPos.x + m_vScale.x / 2.f), (int)(m_vPos.y + m_vScale.y / 2.f));

	// ������Ʈ�� �׸���
	renderComponent(_dc);
}

void CObject::renderComponent(HDC _dc)
{
	// �浹ü�� �׸���
	if (nullptr != m_pCollider)
		m_pCollider->render(_dc);
}

void CObject::createCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}
