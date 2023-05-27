#pragma once
#include "CUI.h"

class CPanelUI :
    public CUI
{
private:
    Vec2 m_vDragStart;

public:
    //void update();
    //void render(HDC _dc);

public:
    virtual void mouseOn();
    virtual void mouseLBtnDown();
    virtual void mouseLBtnUp();

    CLONE(CPanelUI);

public:
    CPanelUI();
    ~CPanelUI();
};