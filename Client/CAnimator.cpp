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

CAnimation* CAnimator::findAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
	{
		return nullptr;
	}

	return iter->second;
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

void CAnimator::createAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _iFrameCount)
{
	CAnimation* pAnim = findAnimation(_strName);
	assert(nullptr == pAnim);

	pAnim = new CAnimation;

	pAnim->setName(_strName);
	pAnim->m_pAnimator = this;
	pAnim->create(_pTex, _vLT, _vSliceSize, _vStep, _iFrameCount);

	m_mapAnim.insert(make_pair(_strName, pAnim));
}