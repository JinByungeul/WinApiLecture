#pragma once
 
#include "CRes.h"

class CTexture :
    public CRes
{
private:
    HDC         m_hDC;
    HBITMAP     m_hBit;
    BITMAP      m_bitInfo;

public:
    void road(const wstring& _strFilePath);

    UINT width() { return m_bitInfo.bmWidth; }
    UINT height() { return m_bitInfo.bmHeight; }

    HDC getDC() { return m_hDC; }

private:
    CTexture();
    ~CTexture();

    friend class CResMgr;
};