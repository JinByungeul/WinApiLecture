#pragma once

class CAnimator;
class CTexture;

struct tAnimFrm
{
	Vec2	vLT;
	Vec2	vSlice;
	Vec2	vOffset;
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

	bool				m_bFinish;	// ��� ���� ���޿���

public:
	const wstring& getName() { return m_strName; }
	bool isFinish() { return m_bFinish; }
	void setFrame(int _iFrameIdx) 
	{ 
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}

	tAnimFrm& getFrame(int _iIdx) { return m_vecFrm[_iIdx]; }
	int getMaxFrame() { return (int)m_vecFrm.size(); }

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