#pragma once

class CPathMgr
{
	SINGLE(CPathMgr);

private:
	wchar_t		m_szContentPath[256];
	wchar_t		m_szRelativePath[256];

public:
	void init();
	
	const wchar_t* getContentPath() { return m_szContentPath; }
	const wstring getRelativePath(const wchar_t* _filepath);
};