#include "pch.h"
#include "CSceneTool.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "func.h"

CSceneTool::CSceneTool()
{
}

CSceneTool::~CSceneTool()
{
}

void CSceneTool::update()
{
	CScene::update();

	if (KEY_TAP(KEY::ENTER))
	{
		changeScene(SCENE_TYPE::START);
	}
}

void CSceneTool::Enter()
{

}

void CSceneTool::Exit()
{

}
