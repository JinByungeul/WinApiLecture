#pragma once

class CObject;
class CAnimation;
class CTexture;

// �� ���� Animation�� �����ϴ� Ŭ����
class CAnimator
{
private:
	map<wstring, CAnimation*>	m_mapAnim;	// ��� Animation
	CAnimation*					m_pCurAnim;	// ���� ������� Animation
	CObject*					m_pOwner;
	
public:
	CObject* getObj() { return m_pOwner; }

public:
	void createAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);
	CAnimation* findAnimation(const wstring& _strName);
	void play(const wstring& _strName);

	void update();
	void render(HDC _dc);

public:
	CAnimator();
	~CAnimator();

	friend class CObject;
};