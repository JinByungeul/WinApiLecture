#include "CMonster.h"

#include "CTimeMgr.h"
#include "CCollider.h"

CMonster::CMonster()
	: m_vCenterPos(Vec2(0.f, 0.f))
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)	// Right ����
	, m_iHP(5)
{
	// �浹ü ���� �� ũ�� ����
	createCollider();
	getCollider()->setScale(Vec2(40.f, 40.f));
}

CMonster::~CMonster()
{

}

void CMonster::update()
{
	Vec2 vCurPos = GetPos();

	// ���� ���� �������� �ð��� m_fSpeed ��ŭ �̵�
	vCurPos.x += fDT * m_fSpeed * m_iDir;

	// ��ȸ �Ÿ� ���ط��� �Ѿ���� Ȯ��
	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;
	if (0.f < fDist)
	{
		// ���� ����
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;
	}

	SetPos(vCurPos);
}

void CMonster::render(HDC _dc)
{
	//Vec2 vPos = GetPos();
	//Vec2 vScale = GetScale();

	//Rectangle(_dc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f)
	//	, (int)(vPos.x + vScale.x / 2.f), (int)(vPos.y + vScale.y / 2.f));

	CObject::render(_dc);
}

void CMonster::onCollision(CCollider* _pOther)
{
}

void CMonster::onCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->getObject();

	if (pOtherObj->getName() == L"Missile_Player")
	{
		m_iHP -= 1;

		if (m_iHP <= 0)
		{
			deleteObject(this);
		}
	}
}

void CMonster::onCollisionExit(CCollider* _pOther)
{
}
