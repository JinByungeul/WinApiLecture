#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"
#include "CCollider.h"

CMissile::CMissile()
	: m_fTheta(PI / 4.f)		// 45��
	, m_vDir(Vec2(1.f, 1.f))
{
	// ������ ũ�⸦ 1�� ����ȭ ����
	m_vDir.normalize();
	createCollider();	// �浹 ��� ����
	getCollider()->setScale(Vec2(15.f, 15.f));
}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	Vec2 vPos = GetPos();

	// �ﰢ�Լ� �̿� ��
	//vPos.x += 600.f * cosf(m_fTheta) * fDT;
	//vPos.y -= 600.f * sinf(m_fTheta) * fDT;

	// ���� �̿� ��
	vPos.x += 600.f * m_vDir.x * fDT;
	vPos.y += 600.f * m_vDir.y * fDT;

	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Ellipse(_dc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f)
		, (int)(vPos.x + vScale.x / 2.f), (int)(vPos.y + vScale.y / 2.f));

	renderComponent(_dc);
}

void CMissile::onCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->getObject();
	if (pOtherObj->getName() == L"Monster")
	{
		DeleteObject(this);
	}
}
