#pragma once

class CObject;

struct tEvent
{
	EVENT_TYPE	eEvent;
	DWORD_PTR	lParam;	// 8����Ʈ(�÷����� ������� ũ�� ������)
	DWORD_PTR	wParam;
};

class CEventMgr
{
	SINGLE(CEventMgr);
private:
	vector<tEvent>	m_vecEvent;
	vector<CObject*> m_vecDead;

private:
	void execute(const tEvent& _evt);

public:
	void update();
	void addEvent(const tEvent& _evt) { m_vecEvent.push_back(_evt); }
};

