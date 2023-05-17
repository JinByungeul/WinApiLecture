#include "pch.h"
#include "CAnimator.h"
#include "CAnimation.h"

CAnimator::CAnimator()
	: m_pCurAnim(nullptr)
	, m_pOwner(nullptr)
{

}

CAnimator::~CAnimator()
{
	safeDeleteMap(m_mapAnim);
}

void CAnimator::createAnimation()
{

}

void CAnimator::findAnimation()
{

}

void CAnimator::play()
{

}

void CAnimator::update()
{
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->update();
	}
}

void CAnimator::render(HDC _dc)
{
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->render(_dc);
	}
}
