#pragma once

class CCollider;

// �߻�Ŭ����
class CObject
{
private:
	Vec2		m_vPos;			// ��ü�� �߽��� ��ǥ(x, y)
	Vec2		m_vScale;		// ��ü�� ũ��(w, h)

	CCollider*	m_pCollider;	// �浹 ��� ������Ʈ

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	CCollider* getCollider() { return m_pCollider; }
	void createCollider();

public:
	virtual void update() = 0;			// ���������Լ�
	virtual void finalUpdate() final;	// �θ��Լ��� ȣ��ǵ���...������ ����(final)
	virtual void render(HDC _dc);		// �����Լ�

	void renderComponent(HDC _dc);		// ������Ʈ �׸���

public:
	CObject();
	virtual ~CObject();
};

