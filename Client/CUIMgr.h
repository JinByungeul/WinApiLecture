#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);
private:


private:
	// 부모 UI 내에서 실제로 타겟팅 된 UI 를 찾아서 반환
	CUI* getTargetUI(CUI* _pParentUI);

public:
	void setFocusedUI(CUI* _pUI);

public:
	void update();

};