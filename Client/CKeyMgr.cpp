#include "pch.h"
#include "CKeyMgr.h"

#include "CCore.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,	// LEFT,
	VK_RIGHT,	// RIGHT,
	VK_UP,		// UP,
	VK_DOWN,	// DOWN,

	'Q',		// Q,
	'W',		// W,
	'E',		// E,
	'R',		// R,
	'T',		// T,
	'Y',		// Y,
	'U',		// U,
	'I',		// I,
	'O',		// O,
	'P',		// P,
	'A',		// A,
	'S',		// S,
	'D',		// D,
	'F',		// F,
	'G',		// G,
	'Z',		// Z,
	'X',		// X,
	'C',		// C,
	'V',		// V,
	'B',		// B,

	VK_MENU,	// ALT,
	VK_CONTROL,	// CTRL,
	VK_LSHIFT,	// LSHIFT,
	VK_SPACE,	// SPACE,
	VK_RETURN,	// ENTER,
	VK_ESCAPE,	// ESC,

};

CKeyMgr::CKeyMgr()
{}

CKeyMgr::~CKeyMgr()
{}

void CKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::update()
{
	// 윈도우 포커싱 알아내기
	//HWND hMainWnd = CCore::GetInst()->GetMainHwnd();	// 메인 윈도우
	HWND hWnd = GetFocus();								// 현재 포커싱 윈도우

	// 윈도우 포커싱 중일때 키 이벤트
	if (nullptr != hWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			// 키가 눌려있다.
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrevPush)
				{
					// 이전에도 눌려있었다.
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					// 이전에 눌려있지 않았다 -> 막 눌린 상태
					m_vecKey[i].eState = KEY_STATE::TAP;
				}

				m_vecKey[i].bPrevPush = true;
			}

			// 키가 안눌려 있다.
			else
			{
				if (m_vecKey[i].bPrevPush)
				{
					// 이전에 눌려있었다.
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					// 이전에도 안눌려 있었다.
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrevPush = false;
			}
		}
	}
	// 윈도우 포커싱 해제 상태
	else
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].bPrevPush = false;

			if (KEY_STATE::TAP == m_vecKey[i].eState 
				|| KEY_STATE::HOLD == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
	
}
