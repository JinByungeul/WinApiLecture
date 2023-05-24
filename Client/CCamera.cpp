#include "pch.h"
#include "CCamera.h"
#include "CObject.h"
#include "CCore.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
{

}

CCamera::~CCamera()
{

}

void CCamera::update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->isDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}

	if (KEY_HOLD(KEY::UP))
	{
		m_vLookAt.y -= 500.f * fDT;
	}
	if (KEY_HOLD(KEY::DOWN))
	{
		m_vLookAt.y += 500.f * fDT;
	}
	if (KEY_HOLD(KEY::LEFT))
	{
		m_vLookAt.x -= 500.f * fDT;
	}
	if (KEY_HOLD(KEY::RIGHT))
	{
		m_vLookAt.x += 500.f * fDT;
	}

	// 화면 중앙 좌표와 카메라 LookAt 좌표 간의 차이 값 계산
	calDiff();
}

Vec2 CCamera::calDiff()
{
	// 이전 LookAt과 현재 Look 의 차이 값을 보정해서 현재 LookAt을 구한다.


	Vec2  vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2.f;
	m_vDiff = m_vLookAt - vCenter;
	return Vec2();
}
