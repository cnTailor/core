#include "PdfRenderer.h"

#include "Src/Document.h"
#include "Src/Pages.h"
#include "Src/Image.h"

#include "../DesktopEditor/graphics/Image.h"
#include "../DesktopEditor/raster/BgraFrame.h"
#include "../DesktopEditor/cximage/CxImage/ximage.h"

#define MM_2_PT(X) ((X) * 72.0 / 25.4)
#define PT_2_MM(X) ((X) * 25.4 / 72.0)

using namespace PdfWriter;

CPdfRenderer::CPdfRenderer()
{
	m_pDocument = new CDocument();
	if (!m_pDocument || !m_pDocument->CreateNew())
	{
		SetError();
		return;
	}

	m_bValid      = true;
	m_dPageHeight = 297;
	m_dPageWidth  = 210;
	m_pPage       = NULL;
}
CPdfRenderer::~CPdfRenderer()
{
	if (m_pDocument)
		delete m_pDocument;
}
void CPdfRenderer::SaveToFile(const std::wstring& wsPath)
{
	if (!IsValid())
		return;

	m_pDocument->SaveToFile(wsPath);
}
//----------------------------------------------------------------------------------------
// ��� ���������
//----------------------------------------------------------------------------------------
HRESULT CPdfRenderer::get_Type(LONG* lType)
{
	*lType = c_nPDFWriter;
	return S_OK;
}
//----------------------------------------------------------------------------------------
// ������� ��� ������ �� ���������
//----------------------------------------------------------------------------------------
HRESULT CPdfRenderer::NewPage()
{
	if (!IsValid())
		return S_FALSE;

	m_pPage = m_pDocument->AddPage();

	if (!m_pPage)
	{
		SetError();
		return S_FALSE;
	}

	m_pPage->SetWidth(m_dPageWidth);
	m_pPage->SetHeight(m_dPageHeight);

	m_oPen.Reset();

	return S_OK;
}
HRESULT CPdfRenderer::get_Height(double* dHeight)
{
	*dHeight = m_dPageHeight;
	return S_OK;
}
HRESULT CPdfRenderer::put_Height(const double& dHeight)
{
	if (!IsValid() || !m_pPage)
		return S_FALSE;

	m_dPageHeight = dHeight;
	m_pPage->SetHeight(MM_2_PT(dHeight));
	return S_OK;
}
HRESULT CPdfRenderer::get_Width(double* dWidth)
{
	*dWidth = m_dPageWidth;
	return S_OK;
}
HRESULT CPdfRenderer::put_Width(const double& dWidth)
{
	if (!IsValid() || !m_pPage)
		return S_FALSE;

	m_dPageWidth = dWidth;
	m_pPage->SetWidth(MM_2_PT(dWidth));
	return S_OK;
}
HRESULT CPdfRenderer::get_DpiX(double* dDpiX)
{
	*dDpiX = 72;
	return S_OK;
}
HRESULT CPdfRenderer::get_DpiY(double* dDpiY)
{
	*dDpiY = 72;
	return S_OK;
}
//----------------------------------------------------------------------------------------
// ������� ��� ������ � Pen
//----------------------------------------------------------------------------------------
HRESULT CPdfRenderer::get_PenColor(LONG* lColor)
{
	*lColor = m_oPen.GetColor();
	return S_OK;
}
HRESULT CPdfRenderer::put_PenColor(const LONG& lColor)
{
	m_oPen.SetColor(lColor);
	return S_OK;
}
HRESULT CPdfRenderer::get_PenAlpha(LONG* lAlpha)
{
	*lAlpha = m_oPen.GetAlpha();
	return S_OK;
}
HRESULT CPdfRenderer::put_PenAlpha(const LONG& lAlpha)
{
	m_oPen.SetAlpha(lAlpha);
	return S_OK;
}
HRESULT CPdfRenderer::get_PenSize(double* dSize)
{
	*dSize = m_oPen.GetSize();
	return S_OK;
}
HRESULT CPdfRenderer::put_PenSize(const double& dSize)
{
	m_oPen.SetSize(dSize);
	return S_OK;
}
HRESULT CPdfRenderer::get_PenDashStyle(BYTE* nDashStyle)
{
	*nDashStyle = m_oPen.GetDashStyle();
	return S_OK;
}
HRESULT CPdfRenderer::put_PenDashStyle(const BYTE& nDashStyle)
{
	m_oPen.SetDashStyle(nDashStyle);
	return S_OK;
}
HRESULT CPdfRenderer::get_PenLineStartCap(BYTE* nCapStyle)
{
	*nCapStyle = m_oPen.GetStartCapStyle();
	return S_OK;
}
HRESULT CPdfRenderer::put_PenLineStartCap(const BYTE& nCapStyle)
{
	m_oPen.SetStartCapStyle(nCapStyle);
	return S_OK;
}
HRESULT CPdfRenderer::get_PenLineEndCap(BYTE* nCapStyle)
{
	*nCapStyle = m_oPen.GetEndCapStyle();
	return S_OK;
}
HRESULT CPdfRenderer::put_PenLineEndCap(const BYTE& nCapStyle)
{
	m_oPen.SetEndCapStyle(nCapStyle);
	return S_OK;
}
HRESULT CPdfRenderer::get_PenLineJoin(BYTE* nJoinStyle)
{
	*nJoinStyle = m_oPen.GetJoinStyle();
	return S_OK;
}
HRESULT CPdfRenderer::put_PenLineJoin(const BYTE& nJoinStyle)
{
	m_oPen.SetJoinStyle(nJoinStyle);
	return S_OK;
}
HRESULT CPdfRenderer::get_PenDashOffset(double* dOffset)
{
	*dOffset = m_oPen.GetDashOffset();
	return S_OK;
}
HRESULT CPdfRenderer::put_PenDashOffset(const double& dOffset)
{
	m_oPen.SetDashOffset(dOffset);
	return S_OK;
}
HRESULT CPdfRenderer::get_PenAlign(LONG* lAlign)
{
	*lAlign = m_oPen.GetAlign();
	return S_OK;
}
HRESULT CPdfRenderer::put_PenAlign(const LONG& lAlign)
{
	m_oPen.SetAlign(lAlign);
	return S_OK;
}
HRESULT CPdfRenderer::get_PenMiterLimit(double* dMiter)
{
	*dMiter = m_oPen.GetMiter();
	return S_OK;
}
HRESULT CPdfRenderer::put_PenMiterLimit(const double& dMiter)
{
	m_oPen.SetMiter(dMiter);
	return S_OK;
}
HRESULT CPdfRenderer::PenDashPattern(double* pPattern, LONG lCount)
{
	m_oPen.SetDashPattern(pPattern, lCount);
	return S_OK;
}
//----------------------------------------------------------------------------------------
// ������� ��� ������ � Brush
//----------------------------------------------------------------------------------------
HRESULT CPdfRenderer::get_BrushType(LONG* lType)
{
	*lType = m_oBrush.GetType();
	return S_OK;
}
HRESULT CPdfRenderer::put_BrushType(const LONG& lType)
{
	m_oBrush.SetType(lType);
	return S_OK;
}
HRESULT CPdfRenderer::get_BrushColor1(LONG* lColor)
{
	*lColor = m_oBrush.GetColor1();
	return S_OK;
}
HRESULT CPdfRenderer::put_BrushColor1(const LONG& lColor)
{
	m_oBrush.SetColor1(lColor);
	return S_OK;
}
HRESULT CPdfRenderer::get_BrushAlpha1(LONG* lAlpha)
{
	*lAlpha = m_oBrush.GetAlpha1();
	return S_OK;
}
HRESULT CPdfRenderer::put_BrushAlpha1(const LONG& lAlpha)
{
	m_oBrush.SetAlpha1(lAlpha);
	return S_OK;
}
HRESULT CPdfRenderer::get_BrushColor2(LONG* lColor)
{
	*lColor = m_oBrush.GetColor2();
	return S_OK;
}
HRESULT CPdfRenderer::put_BrushColor2(const LONG& lColor)
{
	m_oBrush.SetColor2(lColor);
	return S_OK;
}
HRESULT CPdfRenderer::get_BrushAlpha2(LONG* lAlpha)
{
	*lAlpha = m_oBrush.GetAlpha2();
	return S_OK;
}
HRESULT CPdfRenderer::put_BrushAlpha2(const LONG& lAlpha)
{
	m_oBrush.SetAlpha2(lAlpha);
	return S_OK;
}
HRESULT CPdfRenderer::get_BrushTexturePath(std::wstring* wsPath)
{
	*wsPath = m_oBrush.GetTexturePath();
	return S_OK;
}
HRESULT CPdfRenderer::put_BrushTexturePath(const std::wstring& wsPath)
{
	m_oBrush.SetTexturePath(wsPath);
	return S_OK;
}
HRESULT CPdfRenderer::get_BrushTextureMode(LONG* lMode)
{
	*lMode = m_oBrush.GetTextureMode();
	return S_OK;
}
HRESULT CPdfRenderer::put_BrushTextureMode(const LONG& lMode)
{
	m_oBrush.SetTextureMode(lMode);
	return S_OK;
}
HRESULT CPdfRenderer::get_BrushTextureAlpha(LONG* lAlpha)
{
	*lAlpha = m_oBrush.GetTextureAlpha();
	return S_OK;
}
HRESULT CPdfRenderer::put_BrushTextureAlpha(const LONG& lAlpha)
{
	m_oBrush.SetTextureAlpha(lAlpha);
	return S_OK;
}
HRESULT CPdfRenderer::get_BrushLinearAngle(double* dAngle)
{
	*dAngle = m_oBrush.GetLinearAngle();
	return S_OK;
}
HRESULT CPdfRenderer::put_BrushLinearAngle(const double& dAngle)
{
	m_oBrush.SetLinearAngle(dAngle);
	return S_OK;
}
HRESULT CPdfRenderer::BrushRect(const INT& val, const double& left, const double& top, const double& width, const double& height)
{
	// TODO: ���� ������������ ��� �� �������� ����
	return S_OK;
}
HRESULT CPdfRenderer::BrushBounds(const double& left, const double& top, const double& width, const double& height)
{
	// TODO: ���� ������������ ��� �� �������� ����
	return S_OK;
}
HRESULT CPdfRenderer::put_BrushGradientColors(LONG* lColors, double* pPositions, LONG lCount)
{
	m_oBrush.SetShadingColors(lColors, pPositions, lCount);
	return S_OK;
}
//----------------------------------------------------------------------------------------
// ������� ��� ������ �� ��������
//----------------------------------------------------------------------------------------
HRESULT CPdfRenderer::get_FontName(std::wstring* wsName)
{
	*wsName = m_oFont.GetName();
	return S_OK;
}
HRESULT CPdfRenderer::put_FontName(const std::wstring& wsName)
{
	m_oFont.SetName(wsName);
	return S_OK;
}
HRESULT CPdfRenderer::get_FontPath(std::wstring* wsPath)
{
	*wsPath = m_oFont.GetPath();
	return S_OK;
}
HRESULT CPdfRenderer::put_FontPath(const std::wstring& wsPath)
{
	m_oFont.SetPath(wsPath);
	return S_OK;
}
HRESULT CPdfRenderer::get_FontSize(double* dSize)
{
	*dSize = m_oFont.GetSize();
	return S_OK;
}
HRESULT CPdfRenderer::put_FontSize(const double& dSize)
{
	m_oFont.SetSize(dSize);
	return S_OK;
}
HRESULT CPdfRenderer::get_FontStyle(LONG* lStyle)
{
	*lStyle = m_oFont.GetStyle();
	return S_OK;
}
HRESULT CPdfRenderer::put_FontStyle(const LONG& lStyle)
{
	m_oFont.SetStyle(lStyle);
	return S_OK;
}
HRESULT CPdfRenderer::get_FontStringGID(INT* bGid)
{
	*bGid = m_oFont.GetGid() ? 1 : 0;
	return S_OK;
}
HRESULT CPdfRenderer::put_FontStringGID(const INT& bGid)
{
	m_oFont.SetGid(bGid ? true : false);
	return S_OK;
}
HRESULT CPdfRenderer::get_FontCharSpace(double* dSpace)
{
	*dSpace = m_oFont.GetCharSpace();
	return S_OK;
}
HRESULT CPdfRenderer::put_FontCharSpace(const double& dSpace)
{
	m_oFont.SetCharSpace(dSpace);
	return S_OK;
}
HRESULT CPdfRenderer::get_FontFaceIndex(int* nFaceIndex)
{
	*nFaceIndex = (int)m_oFont.GetFaceIndex();
	return S_OK;
}
HRESULT CPdfRenderer::put_FontFaceIndex(const int& nFaceIndex)
{
	m_oFont.SetFaceIndex(nFaceIndex);
	return S_OK;
}
//----------------------------------------------------------------------------------------
// ������� ��� ������ ������
//----------------------------------------------------------------------------------------
HRESULT CPdfRenderer::CommandDrawTextCHAR(const LONG& lUnicode, const double& dX, const double& dY, const double& dW, const double& dH, const double& dBaselineOffset)
{
	// TODO: �����������
	return S_OK;
}
HRESULT CPdfRenderer::CommandDrawText(const std::wstring& wsUnicodeText, const double& dX, const double& dY, const double& dW, const double& dH, const double& dBaselineOffset)
{
	// TODO: �����������
	return S_OK;
}
HRESULT CPdfRenderer::CommandDrawTextExCHAR(const LONG& lUnicode, const LONG& lGid, const double& dX, const double& dY, const double& dW, const double& dH, const double& dBaselineOffset, const DWORD& dwFlags)
{
	// TODO: �����������
	return S_OK;
}
HRESULT CPdfRenderer::CommandDrawTextEx(const std::wstring& wsUnicodeText, const std::wstring& wsGidText, const double& dX, const double& dY, const double& dW, const double& dH, const double& dBaselineOffset, const DWORD& dwFlags)
{
	// TODO: �����������
	return S_OK;
}
//----------------------------------------------------------------------------------------
// ������� ������
//----------------------------------------------------------------------------------------
HRESULT CPdfRenderer::BeginCommand(const DWORD& dwType)
{
	// ����� �� ������ �� ������
	return S_OK;
}
HRESULT CPdfRenderer::EndCommand(const DWORD& dwType)
{
	// ����� �� ��������� ���� 2 �������: ������������ ������� ��� � ����� � �������� ����
	// TODO: �����������
	return S_OK;
}
//----------------------------------------------------------------------------------------
// ������� ��� ������ � �����
//----------------------------------------------------------------------------------------
HRESULT CPdfRenderer::PathCommandStart()
{
	m_oPath.Clear();
	return S_OK;
}
HRESULT CPdfRenderer::PathCommandEnd()
{
	m_oPath.Clear();
	return S_OK;
}
HRESULT CPdfRenderer::DrawPath(const LONG& lType)
{
	// TODO: �����������
	return S_OK;
}
HRESULT CPdfRenderer::PathCommandMoveTo(const double& dX, const double& dY)
{
	m_oPath.MoveTo(dX, dY);
	return S_OK;
}
HRESULT CPdfRenderer::PathCommandLineTo(const double& dX, const double& dY)
{
	m_oPath.LineTo(dX, dY);
	return S_OK;
}
HRESULT CPdfRenderer::PathCommandLinesTo(double* pPoints, const int& nCount)
{
	if (nCount < 4 || !pPoints)
		return S_OK;

	if (!m_oPath.IsMoveTo())
		m_oPath.MoveTo(pPoints[0], pPoints[1]);

	int nPointsCount = (nCount / 2) - 1;
	for (int nIndex = 1; nIndex <= nPointsCount; ++nIndex)
	{
		m_oPath.LineTo(pPoints[nIndex * 2], pPoints[nIndex * 2 + 1]);
	}

	return S_OK;
}
HRESULT CPdfRenderer::PathCommandCurveTo(const double& dX1, const double& dY1, const double& dX2, const double& dY2, const double& dXe, const double& dYe)
{
	m_oPath.CurveTo(dX1, dY1, dX2, dY2, dXe, dYe);
	return S_OK;
}
HRESULT CPdfRenderer::PathCommandCurvesTo(double* pPoints, const int& nCount)
{
	if (nCount < 8 || !pPoints)
		return S_OK;

	if (!m_oPath.IsMoveTo())
		m_oPath.MoveTo(pPoints[0], pPoints[1]);

	int nPointsCount = (nCount - 2) / 6;
	double* pCur = pPoints + 2;
	for (int nIndex = 0; nIndex <= nPointsCount; ++nIndex, pCur += 6)
	{
		m_oPath.CurveTo(pCur[0], pCur[1], pCur[2], pCur[3], pCur[4], pCur[5]);
	}

	return S_OK;
}
HRESULT CPdfRenderer::PathCommandArcTo(const double& dX, const double& dY, const double& dW, const double& dH, const double& dStartAngle, const double& dSweepAngle)
{
	m_oPath.ArcTo(dX, dY, dW, dH, dStartAngle, dSweepAngle);
	return S_OK;
}
HRESULT CPdfRenderer::PathCommandClose()
{
	m_oPath.Close();
	return S_OK;
}
HRESULT CPdfRenderer::PathCommandGetCurrentPoint(double* dX, double* dY)
{
	m_oPath.GetLastPoint(*dX, *dY);
	return S_OK;
}
HRESULT CPdfRenderer::PathCommandTextCHAR(const LONG& lUnicode, const double& dX, const double& dY, const double& dW, const double& dH, const double& dBaselineOffset)
{
	m_oPath.AddText(m_oFont, lUnicode, dX, dY, dW, dH, dBaselineOffset);
	return S_OK;
}
HRESULT CPdfRenderer::PathCommandText(const std::wstring& wsText, const double& dX, const double& dY, const double& dW, const double& dH, const double& dBaselineOffset)
{
	m_oPath.AddText(m_oFont, wsText, dX, dY, dW, dH, dBaselineOffset);
	return S_OK;
}
HRESULT CPdfRenderer::PathCommandTextExCHAR(const LONG& lUnicode, const LONG& lGid, const double& dX, const double& dY, const double& dW, const double& dH, const double& dBaselineOffset, const DWORD& dwFlags)
{
	m_oPath.AddText(m_oFont, lUnicode, lGid, dX, dY, dW, dH, dBaselineOffset, dwFlags);
	return S_OK;
}
HRESULT CPdfRenderer::PathCommandTextEx(const std::wstring& wsUnicodeText, const std::wstring& wsGidText, const double& dX, const double& dY, const double& dW, const double& dH, const double& dBaselineOffset, const DWORD& dwFlags)
{
	m_oPath.AddText(m_oFont, wsUnicodeText, wsGidText, dX, dY, dW, dH, dBaselineOffset, dwFlags);
	return S_OK;
}
//----------------------------------------------------------------------------------------
// ������� ��� ������ �����������
//----------------------------------------------------------------------------------------
HRESULT CPdfRenderer::DrawImage(IGrObject* pImage, const double& dX, const double& dY, const double& dW, const double& dH)
{
	if (!IsPageValid() || !pImage)
		return S_OK;

	// TODO: ����� �������� ���������

	if (!DrawImage((Aggplus::CImage*)pImage, dX, dY, dW, dH, 255))
		return S_FALSE;

	return S_OK;
}
HRESULT CPdfRenderer::DrawImageFromFile(const std::wstring& wsImagePath, const double& dX, const double& dY, const double& dW, const double& dH, const BYTE& nAlpha)
{
	if (!IsPageValid())
		return S_OK;

	// TODO: ����� �������� ���������

	Aggplus::CImage oAggImage(wsImagePath);
	if (!DrawImage(&oAggImage, dX, dY, dW, dH, nAlpha))
		return S_FALSE;

	return S_OK;
}
//----------------------------------------------------------------------------------------
// ������� ��� ����������� ��������������
//----------------------------------------------------------------------------------------
HRESULT CPdfRenderer::SetTransform(const double& dM11, const double& dM12, const double& dM21, const double& dM22, const double& dX, const double& dY)
{
	// TODO: �����������
	return S_OK;
}
HRESULT CPdfRenderer::GetTransform(double* dM11, double* dM12, double* dM21, double* dM22, double* dX, double* dY)
{
	// TODO: �����������
	return S_OK;
}
HRESULT CPdfRenderer::ResetTransform()
{
	// TODO: �����������
	return S_OK;
}
//----------------------------------------------------------------------------------------
// ��� �����
//----------------------------------------------------------------------------------------
HRESULT CPdfRenderer::get_ClipMode(LONG* lMode)
{
	*lMode = m_lClipMode;
	return S_OK;
}
HRESULT CPdfRenderer::put_ClipMode(const LONG& lMode)
{
	m_lClipMode = lMode;
	return S_OK;
}
//----------------------------------------------------------------------------------------
// �������������� �������
//----------------------------------------------------------------------------------------
HRESULT CPdfRenderer::CommandLong(const LONG& lType, const LONG& lCommand)
{
	return S_OK;
}
HRESULT CPdfRenderer::CommandDouble(const LONG& lType, const double& dCommand)
{
	return S_OK;
}
HRESULT CPdfRenderer::CommandString(const LONG& lType, const std::wstring& sCommand)
{
	return S_OK;
}
//----------------------------------------------------------------------------------------
// �������������� ������� Pdf ���������
//----------------------------------------------------------------------------------------
HRESULT CPdfRenderer::CommandDrawTextPdf(const std::wstring& bsUnicodeText, const std::wstring& bsGidText, const std::wstring& wsSrcCodeText, const double& dX, const double& dY, const double& dW, const double& dH, const double& dBaselineOffset, const DWORD& dwFlags)
{
	return S_OK;
}
HRESULT CPdfRenderer::PathCommandTextPdf(const std::wstring& bsUnicodeText, const std::wstring& bsGidText, const std::wstring& bsSrcCodeText, const double& dX, const double& dY, const double& dW, const double& dH, const double& dBaselineOffset, const DWORD& dwFlags)
{
	return S_OK;
}
HRESULT CPdfRenderer::DrawImage1bpp(Pix* pImageBuffer, const unsigned int& unWidth, const unsigned int& unHeight, const double& dX, const double& dY, const double& dW, const double& dH)
{
	if (!IsPageValid() || !pImageBuffer)
		return S_OK;

	// TODO: ������ ���������
	CImageDict* pPdfImage = m_pDocument->CreateImage();
	pPdfImage->LoadBW(pImageBuffer, unWidth, unHeight);
	m_pPage->DrawImage(pPdfImage, MM_2_PT(dX), MM_2_PT(m_dPageHeight - dY - dH), MM_2_PT(dW), MM_2_PT(dH));
	return S_OK;
}
//----------------------------------------------------------------------------------------
// ���������� �������
//----------------------------------------------------------------------------------------
bool CPdfRenderer::DrawImage(Aggplus::CImage* pImage, const double& dX, const double& dY, const double& dW, const double& dH, const BYTE& nAlpha)
{
	int nImageW = abs((int)pImage->GetWidth());
	int nImageH = abs((int)pImage->GetHeight());
	BYTE* pData = pImage->GetData();
	int nStride = 4 * nImageW;

	// ����������� �� �������� � ���������� ���� �� � ��� �����-�����
	bool bAlpha = false;
	for (int nIndex = 0, nSize = nImageW * nImageH; nIndex < nSize; nIndex++)
	{
		if (pData[4 * nIndex + 3] < 255)
		{
			bAlpha = true;
			break;
		}
	}

	CxImage oCxImage;
	if (!oCxImage.CreateFromArray(pData, nImageW, nImageH, 32, nStride, (nStride >= 0) ? true : false))
		return false;

	BYTE* pBuffer = NULL;
	int nBufferSize = 0;
	if (!oCxImage.Encode(pBuffer, nBufferSize, CXIMAGE_FORMAT_JP2))
		return false;

	if (!pBuffer || !nBufferSize)
		return false;

	CImageDict* pPdfImage = m_pDocument->CreateImage();
	if (bAlpha || nAlpha < 255)
		pPdfImage->LoadSMask(pData, nImageW, nImageH, nAlpha);

	pPdfImage->LoadJpx(pBuffer, nBufferSize, nImageW, nImageH);
	m_pPage->DrawImage(pPdfImage, MM_2_PT(dX), MM_2_PT(m_dPageHeight - dY - dH), MM_2_PT(dW), MM_2_PT(dH));
	free(pBuffer);

	return true;
}

