#pragma once


class CRes
{
private:
	wstring m_strKey;			// ���ҽ� Ű
	wstring m_strRelativePath;	// ���ҽ� �����

public:
	void setKey(const wstring& _strKey) { m_strKey = _strKey; }
	void setRelativePath(const wstring& _strRelativePath) { m_strRelativePath = _strRelativePath; }

	const wstring& getKey() { return m_strKey; }
	const wstring& getRelativePath() { return m_strRelativePath; }

public:
	CRes();
	virtual ~CRes();
};

