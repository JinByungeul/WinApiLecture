#pragma once

class CObject;
class CAnimation;
class CTexture;

// 수 많은 Animation을 관리하는 클래스
class CAnimator
{
private:
	map<wstring, CAnimation*>	m_mapAnim;	// 모든 Animation
	CAnimation*					m_pCurAnim;	// 현재 재생중인 Animation
	CObject*					m_pOwner;	// Animator 소유 오브젝트
	bool						m_bRepeat;	// 반복여부
	
public:
	CObject* getObj() { return m_pOwner; }

public:
	void createAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);
	CAnimation* findAnimation(const wstring& _strName);
	void play(const wstring& _strName, bool _bRepeat);

	void update();
	void finalUpdate();
	void render(HDC _dc);

public:
	CAnimator();
	~CAnimator();

	friend class CObject;
};