#pragma once

class CAnimator;
class CTexture;

struct tAnimFrm
{

};

class CAnimation
{
private:
	wstring		m_strName;
	CAnimator*	m_pAnimator;

	CTexture*	m_pTex;

public:
	const wstring& getName() { return m_strName; }

private:
	void setName(const wstring& _strName) { m_strName = _strName; }

public:
	void update();
	void render(HDC _dc);
	void create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _iFrameCount);

public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};