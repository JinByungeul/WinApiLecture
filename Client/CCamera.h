#pragma once

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2 m_vLookAt;

public:
	void update();

	Vec2 calDiff();
};