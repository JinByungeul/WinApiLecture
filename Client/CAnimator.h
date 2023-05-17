#pragma once

class CObject;
class CAnimation;

// 수 많은 Animation을 관리하는 클래스
class CAnimator
{
private:
	map<wstring, CAnimator*>	m_mapAnim;	// 모든 Animation
	CAnimation*					m_pCurAnim;	// 현재 재생중인 Animation
	CObject*					m_pOwner;
	
public:
	void createAnimation();
	void findAnimation();
	void play();

	void update();
	void render(HDC _dc);

public:
	CAnimator();
	~CAnimator();

	friend class CObject;
};