#pragma once

class CCore
{
	SINGLE(CCore);	// 매크로

private:
	HWND	m_hWnd;			// 메인 윈도우 핸들
	POINT	m_ptResolution;	// 메인 윈도우 해상도
	HDC		m_hDC;			// 메인 윈도우에 Draw 할 DC

	HBITMAP	m_hBit;
	HDC		m_memDC;

public:
	int init(HWND _hWnd, POINT _ptResolution);

	void process();			// 윈도우 메시지 없을때 동작 함수

private:
	void update();
	void render();

public:
	HWND GetMainHwnd() { return m_hWnd; }

};