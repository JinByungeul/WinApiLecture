#pragma once
#include "CObject.h"

class CTexture;

class CTile :
    public CObject
{
private:
    CTexture*   m_pTileTex;     // 로드한 텍스처
    int         m_iImgIdx;      // 출력하고 싶은 인덱스 좌표

public:
    void setTexture(CTexture* _pTex) { m_pTileTex = _pTex; }
    void addImgIdx() { ++m_iImgIdx; }

    virtual void update();
    virtual void render(HDC _dc);

    virtual void save(FILE* _pFile);
    virtual void load(FILE* _pFile);

    CLONE(CTile);

public:
    CTile();
    ~CTile();
};