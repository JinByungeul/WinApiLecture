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

	// 자주 사용하는 GDI Object
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

public:
	int init(HWND _hWnd, POINT _ptResolution);

	void process();			// 윈도우 메시지 없을때 동작 함수

private:
	void createBrushPen();

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	POINT GetResolution() { return m_ptResolution; }

	HBRUSH getBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN getPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
};