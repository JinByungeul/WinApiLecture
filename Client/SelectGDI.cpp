#include "pch.h"
#include "SelectGDI.h"
#include "CCore.h"

SelectGDI::SelectGDI(HDC _dc, PEN_TYPE _ePenType)
	: m_hDC(_dc)
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr)
{
	HPEN hPen = CCore::GetInst()->getPen(_ePenType);
	m_hDefaultPen = (HPEN)SelectObject(_dc, hPen);
}

SelectGDI::SelectGDI(HDC _dc, BRUSH_TYPE _eBrushType)
	: m_hDC(_dc)
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr) 
{
	HBRUSH hBrush = CCore::GetInst()->getBrush(_eBrushType);
	m_hDefaultBrush = (HBRUSH)SelectObject(_dc, hBrush);
}

SelectGDI::~SelectGDI()
{
	if (nullptr != m_hDefaultBrush)
		SelectObject(m_hDC, m_hDefaultBrush);

	if (nullptr != m_hDefaultPen)
		SelectObject(m_hDC, m_hDefaultPen);
}
