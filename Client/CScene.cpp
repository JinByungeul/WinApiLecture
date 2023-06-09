#include "CScene.h"

#include "CObject.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CTile.h"
#include "CPathMgr.h"

CScene::CScene()
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			// m_arrObj[i] 그룹 벡터의 j 물체 삭제
			delete m_arrObj[i][j];
		}
		m_arrObj[i].clear();
	}
}

void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (!m_arrObj[i][j]->isDead())
			{
				m_arrObj[i][j]->update();
			}
		}
	}
}

void CScene::finalUpdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->finalUpdate();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		vector<CObject*>::iterator iter = m_arrObj[i].begin();

		for (; iter != m_arrObj[i].end();)
		{
			if (!(*iter)->isDead())
			{
				(*iter)->render(_dc);
				++iter;
			}
			else
			{
				iter = m_arrObj[i].erase(iter);
			}
		}
	}
}

void CScene::deleteGroup(GROUP_TYPE _eTarget)
{
	// vector<T> 함수 템플릿 임!
	safeDeleteVec<CObject*>(m_arrObj[(UINT)_eTarget]);
}

void CScene::deleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		deleteGroup((GROUP_TYPE)i);
	}
}

void CScene::createTile(UINT _iXCount, UINT _iYCount)
{
	// 기존의 Tile 을 지우고
	deleteGroup(GROUP_TYPE::TILE);

	m_iTileX = _iXCount;
	m_iTileY = _iYCount;

	CTexture* pTileTex = CResMgr::GetInst()->loadTexture(L"Tile", L"texture\\tile\\TILE.bmp");

	for (size_t i = 0; i < _iYCount; ++i)
	{
		for (size_t j = 0; j < _iXCount; ++j)
		{
			CTile* pTile = new CTile;

			pTile->SetPos(Vec2((float)(j * TILE_SIZE), (float)(i * TILE_SIZE)));
			pTile->setTexture(pTileTex);

			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}

void CScene::loadTile(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->getContentPath();
	strFilePath += _strRelativePath;

	// 파일 열기 - 커널 오브젝트
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _strRelativePath.c_str(), L"rb");	// 읽기 + 바이너리 모드
	assert(pFile);

	// 타일 가로 세로 개수 불러옴
	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	// 불러온 개수에 맞게 EmptyTile 만들어 두기
	createTile(xCount, yCount);

	// 만들어진 타일 개별로 필요한 정보를 불러오게 함
	const vector<CObject*> vecTile = GetGroupObject(GROUP_TYPE::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->load(pFile);
	}

	// 파일 닫기
	fclose(pFile);
}
