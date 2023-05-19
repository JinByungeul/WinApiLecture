#pragma once


class CRes
{
private:
	wstring m_strKey;			// 리소스 키
	wstring m_strRelativePath;	// 리소스 상대경로

public:
	void setKey(const wstring& _strKey) { m_strKey = _strKey; }
	void setRelativePath(const wstring& _strRelativePath) { m_strRelativePath = _strRelativePath; }

	const wstring& getKey() { return m_strKey; }
	const wstring& getRelativePath() { return m_strRelativePath; }

public:
	CRes();
	virtual ~CRes();
};

