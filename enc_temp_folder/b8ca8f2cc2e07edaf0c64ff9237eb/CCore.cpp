#include "pch.h"
#include "CCore.h"

//CCore* CCore::g_pInst = nullptr;

CCore::CCore()
{

}

CCore::~CCore()
{

}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// �ػ󵵿� �°� ������ ũ�� ����(������ ��üũ��: Ÿ��Ʋ��, �޴���, �׵θ� ��)
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);


	SetWindowPos(m_hWnd, 0, 0, 0, m_ptResolution.x, m_ptResolution.y, false);

	_ptResolution.x;
	_ptResolution.y;

	return S_OK;	// success code
}

void CCore::process()
{

}

