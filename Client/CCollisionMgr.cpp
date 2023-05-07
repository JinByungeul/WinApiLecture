#include "pch.h"
#include "CCollisionMgr.h"

#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)	// 대각으로 중첩되는 부분은 제외
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				collisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::collisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);
	map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		CCollider* pLeftCol = vecLeft[i]->getCollider();

		// 충돌체를 보유하지 않은 경우 
		if (nullptr == pLeftCol)
		{
			continue;
		}
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			CCollider* pRightCol = vecRight[j]->getCollider();

			// 충돌체를 보유하지 않거나 자기 자신과의 충돌인 경우
			if (nullptr == pRightCol || vecLeft[i] == vecRight[j])
			{
				continue;
			}

			// 두 충돌체 조합 아이디 생성
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->getID();
			ID.Right_id = pRightCol->getID();

			iter = m_mapColInfo.find(ID.ID);

			// 충돌 정보가 미등록 상태인 경우 등록(충돌하지 않았다)
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));	// 그럼 false 로 등록
				iter = m_mapColInfo.find(ID.ID);
			}
			

			// 현재 충돌 중이다.
			if (isCollision(pLeftCol, pRightCol))
			{
				// 이전에도 충돌하고 있었다.
				if (iter->second)
				{
					// 근데 둘중 하나가 삭제 예정이라면, 충돌 해제시켜준다.
					if (vecLeft[i]->isDead() || vecRight[j]->isDead())
					{
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}
				}
				// 이전에는 충돌하지 않았다.
				else
				{
					// 근데 둘중 하나가 삭제 예정이라면, 충돌하지 않은 것으로 취급
					if (!vecLeft[i]->isDead() && !vecRight[j]->isDead())
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
			}
			// 현재 충돌하지 않음
			else
			{
				// 이전에는 충돌하고 있었다.
				if (iter->second)
				{
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
			}
		}
	}
}

bool CCollisionMgr::isCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	// 충돌 검사
	Vec2 vLeftPos = _pLeftCol->getFinalPos();
	Vec2 vLeftScale = _pLeftCol->getScale();

	Vec2 vRightPos = _pRightCol->getFinalPos();
	Vec2 vRightScale = _pRightCol->getScale();

	if (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x / 2.f + vRightScale.x / 2.f)
		&& abs(vRightPos.y - vLeftPos.y) < (vLeftScale.y / 2.f + vRightScale.y / 2.f))
	{
		return true;
	}
	return false;
}

void CCollisionMgr::checkGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 더 작은 값의 그룹 타입을 행으로,
	// 큰 값을 열(비트)로 사용
	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol))		// 그 자리에 1로 채워져 있으면
	{
		m_arrCheck[iRow] &= ~(1 << iCol);	// 0
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);	// 1
	}
}
