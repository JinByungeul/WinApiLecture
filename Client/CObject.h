#pragma once

class CCollider;

// �߻�Ŭ����
class CObject
{
private:
	wstring		m_strName;		// ��ü�� �̸�

	Vec2		m_vPos;			// ��ü�� �߽��� ��ǥ(x, y)
	Vec2		m_vScale;		// ��ü�� ũ��(w, h)

	CCollider*	m_pCollider;	// �浹 ��� ������Ʈ

	bool		m_bAlive;		// Ȱ�� / ��Ȱ�� ����

public:
	wstring getName() { return m_strName; }
	void setName(const wstring& _strName) { m_strName = _strName; }

	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	CCollider* getCollider() { return m_pCollider; }

	bool isDead() { return !m_bAlive; }

	void createCollider();

	virtual void onCollision(CCollider* _pOther) {}
	virtual void onCollisionEnter(CCollider* _pOther) {}
	virtual void onCollisionExit(CCollider* _pOther) {}

private:
	void setDead() { m_bAlive = false; }// ��⸦ false ���� ���ؼ� ���� ������!(23.05.10)

public:
	virtual void update() = 0;			// ���������Լ�
	virtual void finalUpdate() final;	// �θ��Լ��� ȣ��ǵ���...������ ����(final)
	virtual void render(HDC _dc);		// �����Լ�

	void renderComponent(HDC _dc);		// ������Ʈ �׸���

public:
	CObject();
	virtual ~CObject();

	friend class CEventMgr;
};

