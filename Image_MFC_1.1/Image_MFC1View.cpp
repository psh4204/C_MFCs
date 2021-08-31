
// Image_MFC1View.cpp: CImageMFC1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Image_MFC1.h"
#endif

#include "Image_MFC1Doc.h"
#include "Image_MFC1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageMFC1View

IMPLEMENT_DYNCREATE(CImageMFC1View, CView)

BEGIN_MESSAGE_MAP(CImageMFC1View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_EQUAL_IMAGE, &CImageMFC1View::OnEqualImage)
	ON_COMMAND(IDM_BW_VAL_IMAGE, &CImageMFC1View::OnBwValImage)
	ON_COMMAND(IDM_BW_127_IMAGE, &CImageMFC1View::OnBw127Image)
	ON_COMMAND(IDM_BW_AVG_IMAGE, &CImageMFC1View::OnBwAvgImage)
	ON_COMMAND(IDM_LIGHT_PM_IMAGE, &CImageMFC1View::OnLightPmImage)
	ON_COMMAND(IDM_LIGHT_GN_IMAGE, &CImageMFC1View::OnLightGnImage)
	ON_COMMAND(IDM_NGT_IMAGE, &CImageMFC1View::OnNgtImage)
	ON_COMMAND(IDM_GAMMA_IMAGE, &CImageMFC1View::OnGammaImage)
	ON_COMMAND(IDM_PARA_CAP_IMAGE, &CImageMFC1View::OnParaCapImage)
	ON_COMMAND(IDM_PARA_CUP_IMAGE, &CImageMFC1View::OnParaCupImage)
	ON_COMMAND(IDM_ZMIN_NRML_IMAGE, &CImageMFC1View::OnZminNrmlImage)
	ON_COMMAND(IDM_ZMIN_NH_IMAGE, &CImageMFC1View::OnZminNhImage)
	ON_COMMAND(IDM_ZMIN_YS_IMAGE, &CImageMFC1View::OnZminYsImage)
	ON_COMMAND(IDM_ZOUT_IMAGE, &CImageMFC1View::OnZoutImage)
	ON_COMMAND(IDM_TURN_IMAGE, &CImageMFC1View::OnTurnImage)
	ON_COMMAND(IDM_MOVE_IMAGE, &CImageMFC1View::OnMoveImage)
	ON_COMMAND(IDM_MIRROR_UD_IMAGE, &CImageMFC1View::OnMirrorUdImage)
	ON_COMMAND(IDM_MIRROR_LR_IMAGE, &CImageMFC1View::OnMirrorLrImage)
	ON_COMMAND(IDM_EMBOS_IMAGE, &CImageMFC1View::OnEmbosImage)
	ON_COMMAND(IDM_BLR_AVG_IMAGE, &CImageMFC1View::OnBlrAvgImage)
	ON_COMMAND(IDM_BLR_GAUS_IMAGE, &CImageMFC1View::OnBlrGausImage)
	ON_COMMAND(IDM_HPF_IMAGE, &CImageMFC1View::OnHpfImage)
	ON_COMMAND(IDM_LPF_IMAGE, &CImageMFC1View::OnLpfImage)
	ON_COMMAND(IDM_CALC_USA_IMAGE, &CImageMFC1View::OnCalcUsaImage)
	ON_COMMAND(IDM_CALC_MNS_IMAGE, &CImageMFC1View::OnCalcMnsImage)
	ON_COMMAND(IDM_RBRTS_IMAGE, &CImageMFC1View::OnRbrtsImage)
	ON_COMMAND(IDM_PRW_IMAGE, &CImageMFC1View::OnPrwImage)
	ON_COMMAND(IDM_SOBL_IMAGE, &CImageMFC1View::OnSoblImage)
	ON_COMMAND(IDM_LAPLA_IMAGE, &CImageMFC1View::OnLaplaImage)
	ON_COMMAND(IDM_LOG_IMAGE, &CImageMFC1View::OnLogImage)
	ON_COMMAND(IDM_DOG_IMAGE, &CImageMFC1View::OnDogImage)
	ON_COMMAND(IDM_HIST_CHART_IMAGE, &CImageMFC1View::OnHistChartImage)
	ON_COMMAND(IDM_HIST_STCH_IMAGE, &CImageMFC1View::OnHistStchImage)
	ON_COMMAND(IDM_HIST_EQUAL_IMAGE, &CImageMFC1View::OnHistEqualImage)
END_MESSAGE_MAP()

// CImageMFC1View 생성/소멸

CImageMFC1View::CImageMFC1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageMFC1View::~CImageMFC1View()
{
}

BOOL CImageMFC1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CImageMFC1View 그리기

void CImageMFC1View::OnDraw(CDC* pDC)
{
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	int px;
	for (int i = 0; i < pDoc->m_inH; i++) {
		for (int k = 0; k < pDoc->m_inW; k++) {
			px = pDoc->m_InputImage[i][k];
			pDC->SetPixel(k + 5, i + 5, RGB(px, px, px));
		}
	}
	for (int i = 0; i < pDoc->m_outH; i++) {
		for (int k = 0; k < pDoc->m_outW; k++) {
			px = pDoc->m_OutputImage[i][k];
			pDC->SetPixel(pDoc->m_inW + k + 20, i + 5, RGB(px, px, px));
		}
	}
}


// CImageMFC1View 인쇄

BOOL CImageMFC1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageMFC1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageMFC1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CImageMFC1View 진단

#ifdef _DEBUG
void CImageMFC1View::AssertValid() const
{
	CView::AssertValid();
}

void CImageMFC1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageMFC1Doc* CImageMFC1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageMFC1Doc)));
	return (CImageMFC1Doc*)m_pDocument;
}
#endif //_DEBUG


// CImageMFC1View 메시지 처리기


void CImageMFC1View::OnEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnEqualImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnBwValImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBwValImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnBw127Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBw127Image();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnBwAvgImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBwAvgImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnLightPmImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnLightPmImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnLightGnImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnLightGnImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnNgtImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnNgtImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnGammaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnGammaImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnParaCapImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnParaCapImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnParaCupImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnParaCupImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnZminNrmlImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnZminNrmlImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnZminNhImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnZminNhImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnZminYsImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnZminYsImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnZoutImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnZoutImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnTurnImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnTurnImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnMoveImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnMoveImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnMirrorUdImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnMirrorUdImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnMirrorLrImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnMirrorLrImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnEmbosImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnEmbosImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnBlrAvgImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBlrAvgImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnBlrGausImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBlrGausImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnHpfImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnHpfImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnLpfImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnLpfImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnCalcUsaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnCalcUsaImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnCalcMnsImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnCalcMnsImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnRbrtsImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnRbrtsImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnPrwImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnPrwImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnSoblImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnSoblImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnLaplaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnLaplaImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnLogImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnLogImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnDogImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnDogImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnHistChartImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnHistChartImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnHistStchImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnHistStchImage();
	Invalidate(TRUE); // 화면 리프레쉬
}


void CImageMFC1View::OnHistEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnHistEqualImage();
	Invalidate(TRUE); // 화면 리프레쉬
}
