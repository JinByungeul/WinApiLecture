#pragma once

class CObject;
 
class CCollider
{
private:
	static UINT	g_iNextID;

	CObject*	m_pOwner;		// Collider�� �����ϰ� �ִ� ������Ʈ
	Vec2		m_vOffsetPos;	// ������Ʈ�� ���� ������� ��ġ
	Vec2		m_vFinalPos;	// finalUpdate ���� �� �����Ӹ��� ���
	Vec2		m_vScale;		// �浹ü�� ũ��

	UINT		m_iID;			// �浹ü ������ ID ��
	UINT		m_iCol;

public:
	void setOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void setScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 getOffsetPos() { return m_vOffsetPos; }
	Vec2 getScale() { return m_vScale; }

	Vec2 getFinalPos() { return m_vFinalPos; }

	CObject* getObject() { return m_pOwner; }

	UINT getID() { return m_iID; }

public:
	void finalUpdate();
	void render(HDC _hDC);

public:
	// �浹 ���� �Լ�
	void OnCollision(CCollider* _pOther);		// �浹 ���� ��� ȣ��Ǵ� �Լ�
	void OnCollisionEnter(CCollider* _pOther);	// ���� �� �浹 ������ ��� ȣ�� �Լ�
	void OnCollisionExit(CCollider* _pOther);	// ���� �� �浹���� ��� ��� ȣ�� �Լ�

	CCollider& operator = (CCollider& _origin) = delete;	// ����Ʈ ���Կ����� ���� ��ü�� ���� �ڵ�

public:
	CCollider();
	CCollider(const CCollider& _origin);	// ID �� �����ؾ� �ϹǷ� ��������ڸ� ���� ����
	~CCollider();

	friend class CObject;
};