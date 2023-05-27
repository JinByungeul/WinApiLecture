#pragma once
#include "CUI.h"

class CBtnUI :
    public CUI
{
private:


public:
    //void update();
    //void render(HDC _dc);

    virtual void mouseOn();
    virtual void mouseLBtnDown();
    virtual void mouseLBtnUp();

    CLONE(CBtnUI);

public:
    CBtnUI();
    ~CBtnUI();
};