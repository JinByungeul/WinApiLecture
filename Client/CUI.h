#pragma once
#include "CObject.h"

class CUI :
    public CObject
{
private:
    vector<CUI*>    m_vecChildUI;
    CUI*            m_pParentUI;
    Vec2            m_vFinalPos;

    bool            m_bCamAffected; // UI 가 카메라에 영향을 받는지 여부
    bool            m_bMouseOn;     // UI 위에 마우스가 있는지 여부
    bool            m_bLBtnDown;    // UI 에 왼쪽 버튼이 눌린적이 있는지 

private:
    void updateChild();
    void finalUpdateChild();
    void renderChild(HDC _dc);

public:
    Vec2 getFinalPos() { return m_vFinalPos; }
    CUI* getParent() { return m_pParentUI; }
    
    void addChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }
    const vector<CUI*>getChildUI() { return m_vecChildUI; }

    void checkMouseOn();
    bool isMouseOn() { return m_bMouseOn; }
    bool isLBtnDown() { return m_bLBtnDown; }

public:
    virtual void update();
    virtual void finalUpdate();
    virtual void render(HDC _dc);

public:
    virtual void mouseOn();
    virtual void mouseLBtnDown();
    virtual void mouseLBtnUp();
    virtual void mouseLBtnClicked();

    virtual CUI* clone() = 0;		// 자기 자신의 복제 버전을 되돌려 줌

public:
    CUI(bool _bCamAff);
    CUI(const CUI& _origin);
    virtual ~CUI();

    friend class CUIMgr;
};