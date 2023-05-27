#include "CTile.h"

#include "CTexture.h"

CTile::CTile()
	: m_pTileTex(nullptr)
	, m_iImgIdx(0)
{
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}

CTile::~CTile()
{
}

void CTile::update()
{
}

void CTile::render(HDC _dc)
{
	if (nullptr == m_pTileTex || -1 == m_iImgIdx)
	{
		return;
	}

	UINT iWidth = m_pTileTex->width();
	UINT iHeight = m_pTileTex->height();

	UINT iMaxCol = iWidth / TILE_SIZE;
	UINT iMaxRow = iHeight / TILE_SIZE;

	UINT iCurRow = (UINT)m_iImgIdx / iMaxCol;	// (행) 몫
	UINT iCurCol = (UINT)m_iImgIdx % iMaxCol;	// (열) 나머지

	// 이미지 범위를 벗어난 인덱스
	if (iMaxRow <= iCurRow)
		assert(nullptr);

	Vec2 vRenderPos = CCamera::GetInst()->getRenderPos(GetPos());
	Vec2 vScale = GetScale();

	BitBlt(_dc
		, int(vRenderPos.x)
		, int(vRenderPos.y)
		, int(vScale.x)
		, int(vScale.y)
		, m_pTileTex->getDC()
		, iCurCol * TILE_SIZE
		, iCurRow * TILE_SIZE
		, SRCCOPY);
}

void CTile::save(FILE* _pFile)
{
	fwrite(&m_iImgIdx, sizeof(UINT), 1, _pFile);
}

void CTile::load(FILE* _pFile)
{
	fread(&m_iImgIdx, sizeof(UINT), 1, _pFile);
}
