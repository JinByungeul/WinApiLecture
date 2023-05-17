#pragma once

class CObject;
class CAnimation;

// �� ���� Animation�� �����ϴ� Ŭ����
class CAnimator
{
private:
	map<wstring, CAnimator*>	m_mapAnim;	// ��� Animation
	CAnimation*					m_pCurAnim;	// ���� ������� Animation
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