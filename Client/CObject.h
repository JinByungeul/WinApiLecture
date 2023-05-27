#pragma once

#include "global.h"

#include "CCamera.h"

class CCollider;
class CAnimator;

// �߻�Ŭ����
class CObject
{
private:
	wstring		m_strName;		// ��ü�� �̸�

	Vec2		m_vPos;			// ��ü�� �߽��� ��ǥ(x, y)
	Vec2		m_vScale;		// ��ü�� ũ��(w, h)

	// Component
	CCollider*	m_pCollider;	// �浹 ��� ������Ʈ
	CAnimator*	m_pAnimator;	// �ִϸ����� ������Ʈ

	bool		m_bAlive;		// Ȱ�� / ��Ȱ�� ����

public:
	wstring getName() { return m_strName; }
	void setName(const wstring& _strName) { m_strName = _strName; }

	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	bool isDead() { return !m_bAlive; }

	CCollider* getCollider() { return m_pCollider; }
	CAnimator* getAnimator() { return m_pAnimator; }

	void createCollider();		// �浹ü ����
	void createAnimator();		// �ִϸ����� ����

	virtual void onCollision(CCollider* _pOther) {}
	virtual void onCollisionEnter(CCollider* _pOther) {}
	virtual void onCollisionExit(CCollider* _pOther) {}

private:
	void setDead() { m_bAlive = false; }// ��⸦ false ���� ���ؼ� ���� ������!(23.05.10)

public:
	virtual void update() = 0;			// ���������Լ�
	virtual void finalUpdate();	// �θ��Լ��� ȣ��ǵ���...������ ����(final)
	virtual void render(HDC _dc);		// �����Լ�

	void renderComponent(HDC _dc);		// ������Ʈ �׸���

	virtual CObject* clone() = 0;		// �ڱ� �ڽ��� ���� ������ �ǵ��� ��

public:
	CObject();
	CObject(const CObject& _origin);	// ���� ������ �ʿ�
	virtual ~CObject();

	friend class CEventMgr;
};