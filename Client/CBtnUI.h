#pragma once
#include "CUI.h"

class CBtnUI :
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
    CLONE(CBtnUI);

public:
    CBtnUI();
    ~CBtnUI();
};