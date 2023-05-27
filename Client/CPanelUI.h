#pragma once
#include "CUI.h"

class CPanelUI :
    public CUI
{
private:


public:
    void update();
    void render(HDC _dc);

    virtual void mouseOn();
    virtual void mouseLDown();
    virtual void mouseLUp();
    virtual void mouseClicked();

    //virtual CObject* clone();
    CLONE(CPanelUI);
public:
    CPanelUI();
    ~CPanelUI();
};