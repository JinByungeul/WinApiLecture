#pragma once


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
	CObject();
	~CObject();

};
