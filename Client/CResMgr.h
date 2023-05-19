#pragma once

class CRes;
class CTexture;

class CResMgr
{
	SINGLE(CResMgr);
private:
	map<wstring, CRes*> m_mapTex;

public:
	CTexture* loadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* findTexture(const wstring& _strKey);
};

