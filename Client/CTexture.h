#pragma once
 
#include "CRes.h"

class CTexture :
    public CRes
{
private:
    HDC         m_hDC;
    HBITMAP     m_hBit;

public:
    CTexture();
    ~CTexture();
};

