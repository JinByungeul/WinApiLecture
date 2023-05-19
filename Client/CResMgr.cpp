#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"

CResMgr::CResMgr()
    : m_mapTex{}
{

}

CResMgr::~CResMgr()
{
    safeDeleteMap(m_mapTex);
}

CTexture* CResMgr::loadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
    CTexture* pTex = findTexture(_strKey);
    if (nullptr != pTex)
    {
        return pTex;
    }

    wstring strFilePath = CPathMgr::GetInst()->getContentPath();
    strFilePath += _strRelativePath;

    pTex = new CTexture;
    pTex->road(strFilePath);
    pTex->setKey(_strKey);
    pTex->setRelativePath(_strRelativePath);

    m_mapTex.insert(make_pair(_strKey, pTex));

    return pTex;
}

CTexture* CResMgr::findTexture(const wstring& _strKey)
{
    map<wstring, CRes*>::iterator iter = m_mapTex.find(_strKey);

    if (iter == m_mapTex.end())
    {
        return nullptr;
    }

    return (CTexture*)iter->second;
}