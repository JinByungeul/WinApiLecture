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
	// 현재 경로: 프로그램의 실행위치!
	GetCurrentDirectory(255, m_szContentPath);

	// 상위 폴더로
	size_t iLen = wcslen(m_szContentPath);
	
	for (size_t i = iLen - 1; i >= 0; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	// 문자열 합치기
	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");
}
