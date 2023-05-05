#pragma once


class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_lICurCount;
	LARGE_INTEGER	m_lIPrevCount;
	LARGE_INTEGER	m_lIFrequency;

	double			m_dDT;			// 프레임 사이의 시간 값
	double			m_dAcc;			// 1초 체크를 위한 누적 시간
	UINT			m_iCallCount;	// 함수 호출 횟수 체크
	UINT			m_iFPS;			// 초당 호출 횟수

	// FPS
	// 1프레임당 시간 (Delta Time)

public:
	void init();
	void update();
	void render();	// 윈도우 제목 표시줄에 텍스트 표시

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};

