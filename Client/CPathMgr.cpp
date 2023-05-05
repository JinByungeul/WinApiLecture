#include "pch.h"
#include "CPathMgr.h"

#include "CCore.h"

CPathMgr::CPathMgr()
	: m_szContentPath{}
{

}

CPathMgr::~CPathMgr()
{

}

void CPathMgr::init()
{
	// ���� ���: ���α׷��� ������ġ!
	GetCurrentDirectory(255, m_szContentPath);

	// ���� ������
	size_t iLen = wcslen(m_szContentPath);
	
	for (size_t i = iLen - 1; i >= 0; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	// ���ڿ� ��ġ��
	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");
}
