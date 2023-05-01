#pragma once

// �߻�Ŭ����
class CObject
{
private:
	Vec2	m_vPos;		// ��ü�� �߽��� ��ǥ(x, y)
	Vec2	m_vScale;	// ��ü�� ũ��(w, h)

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

public:
	virtual void update() = 0;			// ���������Լ�
	virtual void render(HDC _dc) = 0;	// ���������Լ�

public:
	CObject();
	virtual ~CObject();
};

