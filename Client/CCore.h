#pragma once

// �̱��� ����
// ��ü�� ������ 1���� ����
// ��𼭵� ���� ���� ����
//class CCore
//{
//private:
//	static CCore* g_pInst;
//
//public:
//	// ���� ����Լ�
//	static CCore* GetInstance()
//	{
//		// ���� ȣ��� ���
//		if (nullptr == g_pInst)
//		{
//			g_pInst = new CCore;
//		}
//
//		return g_pInst;
//	}
//
//	static void Release()
//	{
//		if (nullptr != g_pInst)
//		{
//			delete g_pInst;
//			g_pInst = nullptr;
//		}
//	}
//
//
//private:
//	CCore();
//	~CCore();
//};

class CCore
{
	SINGLE(CCore);	// ��ũ��

private:
	HWND	m_hWnd;			// ���� ������ �ڵ�
	POINT	m_ptResolution;	// ���� ������ �ػ�


public:
	int init(HWND _hWnd, POINT _ptResolution);

	void process();			// ������ �޽��� ������ ���� �Լ�

private:
	CCore();
	~CCore();
};