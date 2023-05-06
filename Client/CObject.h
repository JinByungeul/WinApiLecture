#pragma once

class CCollider;

// 추상클래스
class CObject
{
private:
	Vec2		m_vPos;			// 물체의 중심점 좌표(x, y)
	Vec2		m_vScale;		// 물체의 크기(w, h)

	CCollider*	m_pCollider;	// 충돌 기능 컴포넌트

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	CCollider* getCollider() { return m_pCollider; }
	void createCollider();

public:
	virtual void update() = 0;			// 순수가상함수
	virtual void finalUpdate() final;	// 부모함수가 호출되도록...재정의 방지(final)
	virtual void render(HDC _dc);		// 가상함수

	void renderComponent(HDC _dc);		// 컴포넌트 그리기

public:
	CObject();
	virtual ~CObject();
};

