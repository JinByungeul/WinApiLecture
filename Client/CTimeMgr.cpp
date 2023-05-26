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
	// 현재 카운트
	QueryPerformanceCounter(&m_lIPrevCount);

	// 초당 카운트 횟수
	QueryPerformanceFrequency(&m_lIFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_lICurCount);

	// 이전 프레임의 카운팅과 현재 프레임 카운팅 값의 차이를 구한다.
	m_dDT = (double)(m_lICurCount.QuadPart - m_lIPrevCount.QuadPart) / (double)m_lIFrequency.QuadPart;

	// 이전 카운트 값을 현재 카운트 값으로 갱신(다음번에 계산을 위해서)
	m_lIPrevCount = m_lICurCount;

#ifdef _DEBUG
	// 디버깅 시에 너무 오래 멈춰서 DT가 너무 커져버리면 위치 추적이 어려우니 DT를 보정한다.
	if (m_dDT > (1. / 60.))
		m_dDT = (1. / 60.);
#endif // _DEBUG
}

void CTimeMgr::render()
{
	++m_iCallCount;
	m_dAcc += m_dDT;	// DT 누적

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