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
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)	// �밢���� ��ø�Ǵ� �κ��� ����
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

		// �浹ü�� �������� ���� ��� 
		if (nullptr == pLeftCol)
		{
			continue;
		}
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			CCollider* pRightCol = vecRight[j]->getCollider();

			// �浹ü�� �������� �ʰų� �ڱ� �ڽŰ��� �浹�� ���
			if (nullptr == pRightCol || vecLeft[i] == vecRight[j])
			{
				continue;
			}

			// �� �浹ü ���� ���̵� ����
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->getID();
			ID.Right_id = pRightCol->getID();

			iter = m_mapColInfo.find(ID.ID);

			// �浹 ������ �̵�� ������ ��� ���(�浹���� �ʾҴ�)
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));	// �׷� false �� ���
				iter = m_mapColInfo.find(ID.ID);
			}
			

			// ���� �浹 ���̴�.
			if (isCollision(pLeftCol, pRightCol))
			{
				// �������� �浹�ϰ� �־���.
				if (iter->second)
				{
					// �ٵ� ���� �ϳ��� ���� �����̶��, �浹 ���������ش�.
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
				// �������� �浹���� �ʾҴ�.
				else
				{
					// �ٵ� ���� �ϳ��� ���� �����̶��, �浹���� ���� ������ ���
					if (!vecLeft[i]->isDead() && !vecRight[j]->isDead())
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
			}
			// ���� �浹���� ����
			else
			{
				// �������� �浹�ϰ� �־���.
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
	// �浹 �˻�
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
	// �� ���� ���� �׷� Ÿ���� ������,
	// ū ���� ��(��Ʈ)�� ���
	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol))		// �� �ڸ��� 1�� ä���� ������
	{
		m_arrCheck[iRow] &= ~(1 << iCol);	// 0
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);	// 1
	}
}
