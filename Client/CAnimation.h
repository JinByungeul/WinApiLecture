#pragma once

class CAnimator;
class CTexture;

struct tAnimFrm
{
	Vec2	vLT;
	Vec2	vSlice;
	float	fDuration;
};

class CAnimation
{
private:
	wstring				m_strName;
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex;
	vector<tAnimFrm>	m_vecFrm;	// ��� ������ ����
	int					m_iCurFrm;	// ���� ������
	float				m_fAccTime;	// �ð� ����
	bool				m_bFinish;	// ��� ��������

public:
	const wstring& getName() { return m_strName; }
	void setFrame(int _iFrameIdx) 
	{ 
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0;
		m_bFinish = false;
	}
	bool isFinish() { return m_bFinish; }

private:
	void setName(const wstring& _strName) { m_strName = _strName; }

public:
	void update();
	void render(HDC _dc);
	void create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);

public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};