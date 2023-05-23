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
#include "CAnimation.h"

CPlayer::CPlayer()
	//: m_pTex(nullptr)
{
	// Texture �ε��ϱ�
	//m_pTex = CResMgr::GetInst()->loadTexture(L"player_64.bmp", L"texture\\player_64.bmp");

	// �浹 ��� ž��
	createCollider();
	getCollider()->setOffsetPos(Vec2(0.f, 12.f));
	getCollider()->setScale(Vec2(20.f, 40.f));

	// Texture �ε��ϱ�
	CTexture* pTex = CResMgr::GetInst()->loadTexture(L"walkman_65", L"texture\\walkman_65.bmp");
	
	createAnimator();
	getAnimator()->createAnimation(L"WALK_DOWN", pTex, Vec2(0.f, 260.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10);
	getAnimator()->play(L"WALK_DOWN", true);

	// Animation�� Offset ����
	CAnimation* pAnim = getAnimator()->findAnimation(L"WALK_DOWN");
	for (int i = 0; i < pAnim->getMaxFrame(); ++i)
	{
		pAnim->getFrame(i).vOffset = Vec2(0.f, -20.f);
	}
}

CPlayer::~CPlayer()
{

}

void CPlayer::update()
{
	Vec2 vPos = GetPos();

	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.f * fDT;
	}
	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.f * fDT;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		createMissile();
	}

	SetPos(vPos);	// ���� ��ġ ����

	getAnimator()->update();
}

void CPlayer::render(HDC _hDC)
{
	// �浹ü �׸���
	CObject::renderComponent(_hDC);
}

void CPlayer::createMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->setName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));
	
	// ��⸦ EventMgr ���� �߰�
	createObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}
