#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);
private:


private:
	// �θ� UI ������ ������ Ÿ���� �� UI �� ã�Ƽ� ��ȯ
	CUI* getTargetUI(CUI* _pParentUI);

public:
	void setFocusedUI(CUI* _pUI);

public:
	void update();

};