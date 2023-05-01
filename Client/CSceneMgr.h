#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);

private:
	CScene*	m_arrScene[(UINT)SCENE_TYPE::END];	// ��� Scene ���
	CScene*	m_pCurScene;						// ���� Scene

public:
	void init();
	void update();
	void render(HDC _dc);

};

