#pragma once

class CCore
{
	SINGLE(CCore);	// ��ũ��

private:
	HWND	m_hWnd;			// ���� ������ �ڵ�
	POINT	m_ptResolution;	// ���� ������ �ػ�
	HDC		m_hDC;			// ���� �����쿡 Draw �� DC

public:
	int init(HWND _hWnd, POINT _ptResolution);

	void process();			// ������ �޽��� ������ ���� �Լ�

private:
	void update();
	void render();

public:
	HWND GetMainHwnd() { return m_hWnd; }

};