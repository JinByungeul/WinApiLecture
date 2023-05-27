#include "CSceneTool.h"

#include "CCore.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CUIMgr.h"
#include "CUI.h"
#include "CPanelUI.h"
#include "CBtnUI.h"
#include "CTile.h"
#include "resource.h"

CSceneTool::CSceneTool()
	: m_pUI(nullptr)
{
}

CSceneTool::~CSceneTool()
{
}

void CSceneTool::Enter()
{
	// 타일 생성
	createTile(5, 5);

	// UI 하나 만들어보기
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	//CUI* pPanelUI = new CPanelUI;
	//pPanelUI->setName(L"ParentUI");
	//pPanelUI->SetScale(Vec2(300.f, 1500.f));
	//pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x, 0.f));

	//CBtnUI* pBtnUI = new CBtnUI;
	//pBtnUI->setName(L"ChildUI");
	//pBtnUI->SetScale(Vec2(100.f, 40.f));
	//pBtnUI->SetPos(Vec2(0.f, 0.f));
	//
	//pPanelUI->addChild(pBtnUI);
	CUI* pUI = new CUI;
	pUI->SetScale(Vec2(300.f, 1500.f));
	pUI->SetPos(Vec2(vResolution.x - pUI->GetScale().x, 0.f));

	CUI* pChildUI = new CUI;
	pChildUI->SetScale(Vec2(100.f, 40.f));
	pChildUI->SetPos(Vec2(0.f, 0.f));
	
	pUI->addChild(pChildUI);
	AddObject(pUI, GROUP_TYPE::UI);

	// Camera Look 지정
	CCamera::GetInst()->setLookAt(vResolution / 2.f);
}

void CSceneTool::Exit()
{
	deleteAll();
}

void CSceneTool::update()
{
	CScene::update();

	setTileIdx();

	if (KEY_TAP(KEY::LSHIFT))
	{
		//CUIMgr::GetInst()->setFocusedUI(m_pUI);

		saveTileData();
	}
	if (KEY_TAP(KEY::CTRL))
	{
		loadTileData();
	}
}

void CSceneTool::setTileIdx()
{
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousPos = MOUSE_POS;
		vMousPos = CCamera::GetInst()->getRealPos(vMousPos);

		int iTileX = (int)getTileX();
		int iTileY = (int)getTileY();

		int iCol = (int)vMousPos.x / TILE_SIZE;
		int iRow = (int)vMousPos.y / TILE_SIZE;

		if (vMousPos.x < 0 || iTileX <= iCol
			|| vMousPos.y < 0 || iTileY <= iRow)
		{
			return;
		}

		UINT iIdx = iRow * iTileX + iCol;

		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->addImgIdx();
	}
}

void CSceneTool::saveTileData()
{
	OPENFILENAME ofn = {};
	
	wchar_t szName[256] = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL(*.*)\0*.*\0Tile(*.tile)\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->getContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// 모달 창
	if (GetSaveFileName(&ofn))
	{
		saveTile(szName);
	}
}

void CSceneTool::saveTile(const wstring& _strFilePath)
{
	// 커널 오브젝트
	FILE* pFile = nullptr;

	// 파일 열기
	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb");	// 쓰기 + 바이너리 모드
	assert(pFile);

	// 타일 가로 세로 개수 저장
	UINT xCount = getTileX();
	UINT yCount = getTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	// 모든 타일을 개별적으로 저장할 데이터를 저장하게 함
	const vector<CObject*> vecTile = GetGroupObject(GROUP_TYPE::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->save(pFile);
	}

	// 파일 닫기
	fclose(pFile);
}

void CSceneTool::loadTileData()
{
	OPENFILENAME ofn = {};

	wchar_t szName[256] = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL(*.*)\0*.*\0Tile(*.tile)\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->getContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// 모달 창
	if (GetOpenFileName(&ofn))
	{
		// 절대경로를 상대경로로 변환해서 타일 로드
		wstring strRelativePath = CPathMgr::GetInst()->getRelativePath(szName);
		loadTile(strRelativePath);
	}
}

void changeScene(DWORD_PTR, DWORD_PTR)
{
	changeScene(SCENE_TYPE::START);
}



// ======================
// Tile Count Window Proc
// ======================
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			UINT iXCount = ::GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = ::GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

			// ToolScene 인지 확인
			CSceneTool* pToolScene = dynamic_cast<CSceneTool*>(pCurScene);
			assert(pToolScene);

			pCurScene->deleteGroup(GROUP_TYPE::TILE);
			pCurScene->createTile(iXCount, iYCount);

			::EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			::EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}