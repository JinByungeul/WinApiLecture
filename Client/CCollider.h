#pragma once

class CObject;
 
class CCollider
{
private:
	static UINT	g_iNextID;

	CObject*	m_pOwner;		// Collider를 소유하고 있는 오브젝트
	Vec2		m_vOffsetPos;	// 오브젝트로 부터 상대적인 위치
	Vec2		m_vFinalPos;	// finalUpdate 에서 매 프레임마다 계산
	Vec2		m_vScale;		// 충돌체의 크기

	UINT		m_iID;			// 충돌체 고유한 ID 값
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
	// 충돌 시점 함수
	void OnCollision(CCollider* _pOther);		// 충돌 중인 경우 호출되는 함수
	void OnCollisionEnter(CCollider* _pOther);	// 이제 막 충돌 시작한 경우 호출 함수
	void OnCollisionExit(CCollider* _pOther);	// 이제 막 충돌에서 벗어난 경우 호출 함수

	CCollider& operator = (CCollider& _origin) = delete;	// 디폴트 대입연산자 생성 자체를 막는 코드

public:
	CCollider();
	CCollider(const CCollider& _origin);	// ID 는 고유해야 하므로 복사생성자를 직접 구현
	~CCollider();

	friend class CObject;
};