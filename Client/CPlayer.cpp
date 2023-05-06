#include "pch.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CCollider.h"

CPlayer::CPlayer()
	: m_pTex(nullptr)
{
	// Texture 로딩하기
	m_pTex = CResMgr::GetInst()->loadTexture(L"player_64.bmp", L"texture\\player_64.bmp");

	// 충돌 기능 탑재
	createCollider();
	getCollider()->setScale(Vec2(74.f, 74.f));
}

CPlayer::~CPlayer()
{

}

void CPlayer::update()
{
	Vec2 vPos = GetPos();

	if (KEY_HOLD(KEY::A) || KEY_HOLD(KEY::LEFT))
	{
		vPos.x -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::D) || KEY_HOLD(KEY::RIGHT))
	{
		vPos.x += 200.f * fDT;
	}
	if (KEY_HOLD(KEY::W) || KEY_HOLD(KEY::UP))
	{
		vPos.y -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::S) || KEY_HOLD(KEY::DOWN))
	{
		vPos.y += 200.f * fDT;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	SetPos(vPos);	// 변경 위치 적용
}

void CPlayer::render(HDC _hDC)
{
	// Player에 텍스쳐 입히기
	int iW = (int)m_pTex->width();
	int iH = (int)m_pTex->height();

	Vec2 vPos = GetPos();

	//BitBlt(_hDC
	//	, vPos.x - (float)(iW / 2)
	//	, vPos.y - (float)(iH / 2)
	//	, iW, iH
	//	, m_pTex->getDC()
	//	, 0, 0, SRCCOPY);

	TransparentBlt(_hDC
		, vPos.x - (float)(iW / 2)
		, vPos.y - (float)(iH / 2)
		, iW, iH
		, m_pTex->getDC()
		, 0, 0, iW, iH
		, RGB(255, 0, 255));

	// 충돌체 그리기
	CObject::renderComponent(_hDC);
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));
	
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::MISSILE);
	
}
