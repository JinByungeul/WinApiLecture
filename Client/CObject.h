#pragma once

#include "global.h"

#include "CCamera.h"

class CCollider;
class CAnimator;

// 추상클래스
class CObject
{
private:
	wstring		m_strName;		// 물체의 이름

	Vec2		m_vPos;			// 물체의 중심점 좌표(x, y)
	Vec2		m_vScale;		// 물체의 크기(w, h)

	// Component
	CCollider*	m_pCollider;	// 충돌 기능 컴포넌트
	CAnimator*	m_pAnimator;	// 애니메이터 컴포넌트

	bool		m_bAlive;		// 활성 / 비활성 상태

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

	void createCollider();		// 충돌체 생성
	void createAnimator();		// 애니메이터 생성

	virtual void onCollision(CCollider* _pOther) {}
	virtual void onCollisionEnter(CCollider* _pOther) {}
	virtual void onCollisionExit(CCollider* _pOther) {}

private:
	void setDead() { m_bAlive = false; }// 요기를 false 세팅 안해서 에러 났었음!(23.05.10)

public:
	virtual void update() = 0;			// 순수가상함수
	virtual void finalUpdate();	// 부모함수가 호출되도록...재정의 방지(final)
	virtual void render(HDC _dc);		// 가상함수

	void renderComponent(HDC _dc);		// 컴포넌트 그리기

	virtual CObject* clone() = 0;		// 자기 자신의 복제 버전을 되돌려 줌

public:
	CObject();
	CObject(const CObject& _origin);	// 복사 생성자 필요
	virtual ~CObject();

	friend class CEventMgr;
};