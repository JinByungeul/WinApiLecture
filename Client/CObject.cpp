#include "pch.h"

#include "CObject.h"
#include "CCollider.h"
#include "CAnimator.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_bAlive(true)
{
}

CObject::CObject(const CObject& _origin)
	: m_strName(_origin.m_strName)
	, m_vPos(_origin.m_vPos)
	, m_vScale(_origin.m_vScale)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_bAlive(true)
{
	// Collider ���� ����
	if (_origin.m_pCollider)
	{
		m_pCollider = new CCollider(*_origin.m_pCollider);
		m_pCollider->m_pOwner = this;
	}

	// Animator ���� ����
	if (_origin.m_pAnimator)
	{
		m_pAnimator = new CAnimator(*_origin.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}
}

CObject::~CObject()
{
	if (nullptr != m_pCollider)
	{ 
		delete m_pCollider;
	}

	if (nullptr != m_pAnimator)
	{
		delete m_pAnimator;
	}
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

	// �ִϸ����� 
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->render(_dc);
	}
}

CObject* CObject::clone()
{
	return nullptr;
}

void CObject::createCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}

void CObject::createAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;
}
