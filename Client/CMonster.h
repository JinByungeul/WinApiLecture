#pragma once
#include "CObject.h"


class CMonster :
    public CObject
{
private:
    Vec2 m_vCenterPos;
    float m_fSpeed;
    float m_fMaxDistance;
    int m_iDir; // 1, -1(left)
    int m_iHP;

public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _f) { m_fSpeed = _f; }
    void SetMoveDistance(float _f) { m_fMaxDistance = _f; }
    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }

public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void onCollision(CCollider* _pOther);
    virtual void onCollisionEnter(CCollider* _pOther);
    virtual void onCollisionExit(CCollider* _pOther);

public:
    CMonster();
    ~CMonster();
};

