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
#include "CAnimator.h"

CPlayer::CPlayer()
	//: m_pTex(nullptr)
{
	// Texture 로딩하기
	//m_pTex = CResMgr::GetInst()->loadTexture(L"player_64.bmp", L"texture\\player_64.bmp");

	// 충돌 기능 탑재
	createCollider();
	getCollider()->setOffsetPos(Vec2(0.f, 12.f));
	getCollider()->setScale(Vec2(20.f, 40.f));

	// Texture 로딩하기
	CTexture* pTex = CResMgr::GetInst()->loadTexture(L"PlayerTex", L"texture\\animation01.bmp");
	
	createAnimator();
	getAnimator()->createAnimation(L"WALK_DOWN", pTex, Vec2(0.f, 260.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10);
	getAnimator()->play(L"WALK_DOWN");
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

	getAnimator()->update();
}

void CPlayer::render(HDC _hDC)
{
	// 충돌체 그리기
	CObject::renderComponent(_hDC);
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->setName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));
	
	// 요기를 EventMgr 에서 추가
	createObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}
