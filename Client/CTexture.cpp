#include "CTexture.h"
#include "CCore.h"

CTexture::CTexture()
	: m_hDC(0)
	, m_hBit(0)
	, m_bitInfo{}
{
}

CTexture::~CTexture()
{
	DeleteObject(m_hBit);
	DeleteDC(m_hDC);
}

void CTexture::road(const wstring& _strFilePath)
{
	// ���Ϸ� ���� �ε��� �����͸� ��Ʈ������ ����
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);	// �̹��� Full ������ �ε�
	assert(m_hBit);

	// ��Ʈ�ʰ� ������ DC
	m_hDC = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	// ��Ʈ�ʰ� DC ����
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
	DeleteObject(hPrevBit);

	// ��Ʈ�� ����
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);

}