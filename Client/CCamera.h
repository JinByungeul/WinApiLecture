#pragma once

class CObject;

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2		m_vLookAt;		// 카메라 보는 위치
	Vec2		m_vPrevLookAt;	// 카메라가 보는 이전 프레임 위치
	CObject*	m_pTargetObj;	// 카메라 타겟 오브젝트
	Vec2		m_vDiff;		// 화면 중앙 좌표와 카메라 보는 위치 값의 차이

public:
	void setLookAt(Vec2 _vLook) { m_vLookAt = _vLook; }
	void setTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }
	Vec2 getRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; }
	Vec2 getRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }

public:
	void update();

private:
	Vec2 calDiff();
};