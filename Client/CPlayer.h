#pragma once

#include "CObject.h"

class CTexture;

class CPlayer :
    public CObject
{
private:
    CTexture* m_pTex;

public:
    virtual void update();
    virtual void render(HDC _hDC);

private:
    void CreateMissile();

public:
    CPlayer();
    ~CPlayer();
};

