
// ImagePSHView.cpp: CImagePSHView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImagePSH.h"
#endif

#include "ImagePSHDoc.h"
#include "ImagePSHView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImagePSHView

IMPLEMENT_DYNCREATE(CImagePSHView, CView)

BEGIN_MESSAGE_MAP(CImagePSHView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_EQUAL_IMAGE, &CImagePSHView::OnEqualImage)
	ON_COMMAND(IDM_BW_127_IMAGE, &CImagePSHView::OnBw127Image)
	ON_COMMAND(IDM_BW_INPUT_IMAGE, &CImagePSHView::OnBwInputImage)
	ON_COMMAND(IDM_GRAY_IMAGE, &CImagePSHView::OnGrayImage)
	ON_COMMAND(IDM_NGTV_IMAGE, &CImagePSHView::OnNgtvImage)
	ON_COMMAND(IDM_LIGHT_PM_IMAGE, &CImagePSHView::OnLightPmImage)
	ON_COMMAND(IDM_LIGHT_MD_IMAGE, &CImagePSHView::OnLightMdImage)
END_MESSAGE_MAP()

// CImagePSHView 생성/소멸

CImagePSHView::CImagePSHView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImagePSHView::~CImagePSHView()
{
}

BOOL CImagePSHView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CImagePSHView 그리기

void CImagePSHView::OnDraw(CDC* pDC)
{
	CImagePSHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	int RR, GG, BB;
	for (int i = 0; i < pDoc->m_inH; i++) {
		for (int k = 0; k < pDoc->m_inW; k++) {
			RR = pDoc->m_InputImageR[i][k];
			GG = pDoc->m_InputImageG[i][k];
			BB = pDoc->m_InputImageB[i][k];
			pDC->SetPixel(k + 5, i + 5, RGB(RR, GG, BB));
		}
	}
	for (int i = 0; i < pDoc->m_outH; i++) {
		for (int k = 0; k < pDoc->m_outW; k++) {
			RR = pDoc->m_OutputImageR[i][k];
			GG = pDoc->m_OutputImageG[i][k];
			BB = pDoc->m_OutputImageB[i][k];
			pDC->SetPixel(pDoc->m_inW + k + 20, i + 5, RGB(RR, GG, BB));
		}
	}
}


// CImagePSHView 인쇄

BOOL CImagePSHView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImagePSHView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImagePSHView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CImagePSHView 진단

#ifdef _DEBUG
void CImagePSHView::AssertValid() const
{
	CView::AssertValid();
}

void CImagePSHView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImagePSHDoc* CImagePSHView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImagePSHDoc)));
	return (CImagePSHDoc*)m_pDocument;
}
#endif //_DEBUG


// CImagePSHView 메시지 처리기


void CImagePSHView::OnEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePSHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnEqualImage();
	Invalidate(FALSE);
}


void CImagePSHView::OnBw127Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePSHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBw127Image();
	Invalidate(FALSE);
}


void CImagePSHView::OnBwInputImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePSHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBwInputImage();
	Invalidate(FALSE);
}


void CImagePSHView::OnGrayImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePSHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnGrayImage();
	Invalidate(FALSE);
}


void CImagePSHView::OnNgtvImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePSHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnNgtvImage();
	Invalidate(FALSE);
}


void CImagePSHView::OnLightPmImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePSHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnLightPmImage();
	Invalidate(FALSE);
}


void CImagePSHView::OnLightMdImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePSHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnLightMdImage();
	Invalidate(FALSE);
}
