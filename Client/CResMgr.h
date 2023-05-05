#pragma once


class CTexture;

class CResMgr
{
	SINGLE(CResMgr);
private:
	map<wstring, CTexture*> m_mapTex;

public:
	CTexture* loadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* findTexture(const wstring& _strKey);
};

