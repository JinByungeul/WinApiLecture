#pragma once

class CObject;
 
class CCollider
{
private:
	CObject*	m_pOwner;		// Collider�� �����ϰ� �ִ� ������Ʈ
	Vec2		m_vOffsetPos;	// ������Ʈ�� ���� ������� ��ġ
	Vec2		m_vFinalPos;	// finalUpdate ���� �� �����Ӹ��� ���

	Vec2		m_vScale;		// �浹ü�� ũ��

public:
	void setOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void setScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 getOffsetPos() { return m_vOffsetPos; }
	Vec2 getScale() { return m_vScale; }

public:
	void finalUpdate();
	void render(HDC _hDC);

public:
	CCollider();
	~CCollider();

	friend class CObject;
};

