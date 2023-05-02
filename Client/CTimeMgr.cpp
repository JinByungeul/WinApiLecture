#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"

CTimeMgr::CTimeMgr()
	: m_lICurCount{}
	, m_lIPrevCount{}
	, m_lIFrequency{}
	, m_dDT(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	// ���� ī��Ʈ
	QueryPerformanceCounter(&m_lIPrevCount);

	// �ʴ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&m_lIFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_lICurCount);

	// ���� �������� ī���ð� ���� ������ ī���� ���� ���̸� ���Ѵ�.
	m_dDT = (double)(m_lICurCount.QuadPart - m_lIPrevCount.QuadPart) / (double)m_lIFrequency.QuadPart;

	// ���� ī��Ʈ ���� ���� ī��Ʈ ������ ����(�������� ����� ���ؼ�)
	m_lIPrevCount = m_lICurCount;

	++m_iCallCount;
	m_dAcc += m_dDT;	// DT ����

	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
