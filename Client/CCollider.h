#pragma once

class CObject;
 
class CCollider
{
private:
	CObject*	m_pOwner;		// Collider를 소유하고 있는 오브젝트
	Vec2		m_vOffsetPos;	// 오브젝트로 부터 상대적인 위치
	Vec2		m_vFinalPos;	// finalUpdate 에서 매 프레임마다 계산

	Vec2		m_vScale;		// 충돌체의 크기

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

