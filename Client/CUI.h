#pragma once
#include "CObject.h"

class CUI :
    public CObject
{
private:
    vector<CUI*>    m_vecChildUI;
    CUI*            m_pParentUI;

    Vec2            m_vFinalPos;    // 최종 위치

private:
    void updateChild();
    void finalUpdateChild();
    void renderChild(HDC _dc);

public:
    Vec2 getFinalPos() { return m_vFinalPos; }

    CUI* getParent() { return m_pParentUI; }
    void addChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }

public:
    virtual void update();
    virtual void finalUpdate();
    virtual void render(HDC _dc);

    virtual void mouseOn();
    virtual void mouseLDown();
    virtual void mouseLUp();
    virtual void mouseClicked();

    CLONE(CUI);		// 자기 자신의 복제 버전을 되돌려 줌

public:
    CUI();
    virtual ~CUI();
};