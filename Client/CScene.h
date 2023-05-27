#pragma once

#include "global.h"

class CObject;

class CScene
{
private:
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];	// ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	wstring				m_strName;							// Scene �̸�

	UINT				m_iTileX;							// Ÿ�� ���� ����
	UINT				m_iTileY;							// Ÿ�� ���� ����

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	UINT getTileX() { return m_iTileX; }
	UINT getTileY() { return m_iTileY; }

	virtual void update();
	virtual void finalUpdate();			// �浹 ��� ���� ��
	virtual void render(HDC _dc);

	virtual void Enter() = 0;	// �ش� Scene �� ���� �� ȣ��
	virtual void Exit() = 0;	// �ش� Scene �� Ż�� �� ȣ��

public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType) { m_arrObj[(UINT)_eType].push_back(_pObj); }
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	
	void deleteGroup(GROUP_TYPE _eTarget);
	void deleteAll();

	void createTile(UINT _iXCount, UINT _iYCount);
	void loadTile(const wstring& _strRelativePath);

	vector<CObject*>& getUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }

public:
	CScene();
	virtual ~CScene();
};

