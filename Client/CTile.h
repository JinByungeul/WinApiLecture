#pragma once
#include "CObject.h"

class CTexture;

class CTile :
    public CObject
{
private:
    CTexture*   m_pTileTex;     // �ε��� �ؽ�ó
    int         m_iImgIdx;      // ����ϰ� ���� �ε��� ��ǥ

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