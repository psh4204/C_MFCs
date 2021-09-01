
// ImagePSHDoc.cpp: CImagePSHDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImagePSH.h"
#endif

#include "ImagePSHDoc.h"
#include "CInputDlg.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImagePSHDoc

IMPLEMENT_DYNCREATE(CImagePSHDoc, CDocument)

BEGIN_MESSAGE_MAP(CImagePSHDoc, CDocument)
END_MESSAGE_MAP()


// CImagePSHDoc 생성/소멸

CImagePSHDoc::CImagePSHDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImagePSHDoc::~CImagePSHDoc()
{
}

BOOL CImagePSHDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImagePSHDoc serialization

void CImagePSHDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImagePSHDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImagePSHDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImagePSHDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImagePSHDoc 진단

#ifdef _DEBUG
void CImagePSHDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImagePSHDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImagePSHDoc 명령


BOOL CImagePSHDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	// 입력 메모리 해제 (R G B)
	free2D(m_InputImageR, m_inH); free2D(m_InputImageG, m_inH); free2D(m_InputImageB, m_inH);

	// 컬러파일을 읽는 CImage 라이브러리 활용
	CImage bitmap;
	bitmap.Load(lpszPathName); // 입력 데이터 Load

	// 중요! 이미지의 높이, 폭 계산
	m_inH = bitmap.GetHeight();
	m_inW = bitmap.GetWidth();

	//메모리 할당
	m_InputImageR = malloc2D(m_inH, m_inW);
	m_InputImageG = malloc2D(m_inH, m_inW);
	m_InputImageB = malloc2D(m_inH, m_inW);

	COLORREF px; // 한점(R G B) _ (컬러레퍼런스) _ MFC라이브러리
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			px = bitmap.GetPixel(k, i); // 픽셀 받아오기 (행, 열)
			m_InputImageR[i][k] = (unsigned char)GetRValue(px);
			m_InputImageG[i][k] = (unsigned char)GetGValue(px);
			m_InputImageB[i][k] = (unsigned char)GetBValue(px);
		}
	}

	return TRUE;
}


BOOL CImagePSHDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (m_OutputImageR == NULL) {
		MessageBox(NULL, L"파일이 열리지 않았습니다.", L"", 0);
		return FALSE;
	}
	// .PNG 로 저장하는 관례적인 코드
	static TCHAR BASED_CODE szFilter[] = _T("PNG파일(*.PNG) | *.png | 모든파일(*.*) | *.* ||");
	CFileDialog SaveDlg(TRUE, _T("*.png"), _T(""), OFN_HIDEREADONLY, szFilter);
	if (SaveDlg.DoModal() != IDOK)
		return FALSE;
	CImage bitmap;
	bitmap.Create(m_outW, m_outH, 32); // 빈 파일 만들기(행, 열, 32); // CImage는 i랑 k가 반대임.
	COLORREF px;
	unsigned char RR, GG, BB;
	for (int i = 0; i < m_outW; i++) {
		for (int k = 0; k < m_outH; k++) {
			RR = m_OutputImageR[k][i];
			GG = m_OutputImageG[k][i];
			BB = m_OutputImageB[k][i];
			px = RGB(RR, GG, BB);
			bitmap.SetPixel(i, k, px);
		}
	}
	bitmap.Save(SaveDlg.GetPathName(), Gdiplus::ImageFormatPNG); // MFC에서는 PNG포멧을 지원한다.
	return TRUE; // 리턴 True해줘야 정상저장됨
}


void CImagePSHDoc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	free2D(m_InputImageR, m_inH); // 임의로 만들어둔 2차원 free();
	free2D(m_OutputImageR, m_outH);
	free2D(m_InputImageG, m_inH); // 임의로 만들어둔 2차원 free();
	free2D(m_OutputImageG, m_outH);
	free2D(m_InputImageB, m_inH); // 임의로 만들어둔 2차원 free();
	free2D(m_OutputImageB, m_outH);
	CDocument::OnCloseDocument();
}


unsigned char** CImagePSHDoc::malloc2D(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	unsigned char** memory;
	memory = (unsigned char**)malloc(h * sizeof(unsigned char*));
	for (int i = 0; i < h; i++)
		memory[i] = (unsigned char*)malloc(w * sizeof(unsigned char));
	// 초기화(클리어)
	for (int i = 0; i < h; i++)
		for (int k = 0; k < w; k++)
			memory[i][k] = 255;
	return memory;
}

void CImagePSHDoc::free2D(unsigned char** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory != NULL) {
		for (int i = 0; i < h; i++)
			free(memory[i]);
		free(memory);
	}
}

double** CImagePSHDoc::malloc2D_double(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	double** mem;
	mem = (double**)malloc(h * sizeof(double*));
	for (int i = 0; i < h; i++)
		mem[i] = (double*)malloc(w * sizeof(double));

	// 초기화(Clear)
	for (int i = 0; i < h; i++) {
		for (int k = 0; k < w; k++) {
			mem[i][k] = 0;
		}
	}
	return mem;
}

void CImagePSHDoc::free2D_double(double** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory != NULL) {
		for (int i = 0; i < h; i++)
			free(memory[i]);
		free(memory);
	}
}

double CImagePSHDoc::doubleABS(double x)
{
	// TODO: 여기에 구현 코드 추가.

	if (x >= 0) return x;
	else        return -x;
}

void CImagePSHDoc::OnEqualImage()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImageR == NULL) {
		MessageBox(NULL, L"파일이 열리지 않았습니다.", L"", 0);
		return;
	}
	// 기존 출력 메모리 해제
	free2D(m_OutputImageR, m_outH);
	free2D(m_OutputImageG, m_outH);
	free2D(m_OutputImageB, m_outH);
	//(중요!) 출력 영상의 높이와 폭을 결정 --> 알고리즘에 따름
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 영상 메모리 할당
	m_OutputImageR = malloc2D(m_outH, m_outW);
	m_OutputImageG = malloc2D(m_outH, m_outW);
	m_OutputImageB = malloc2D(m_outH, m_outW);

	// 진짜 영상 처리 알고리즘
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_OutputImageR[i][k] = m_InputImageR[i][k];
			m_OutputImageG[i][k] = m_InputImageG[i][k];
			m_OutputImageB[i][k] = m_InputImageB[i][k];
		}
	}
}




void CImagePSHDoc::OnBw127Image()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImageR == NULL) {
		MessageBox(NULL, L"파일이 열리지 않았습니다.", L"", 0);
		return;
	}
	// 기존 출력 메모리 해제
	free2D(m_OutputImageR, m_outH);
	free2D(m_OutputImageG, m_outH);
	free2D(m_OutputImageB, m_outH);
	//(중요!) 출력 영상의 높이와 폭을 결정 --> 알고리즘에 따름
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 영상 메모리 할당
	m_OutputImageR = malloc2D(m_outH, m_outW);
	m_OutputImageG = malloc2D(m_outH, m_outW);
	m_OutputImageB = malloc2D(m_outH, m_outW);

	// 진짜 영상 처리 알고리즘
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int px = (m_InputImageR[i][k] + m_InputImageG[i][k] + m_InputImageB[i][k]) / 3;
			if (px > 127) { m_OutputImageR[i][k] = 255; m_OutputImageG[i][k] = 255; m_OutputImageB[i][k] = 255; }
			else { m_OutputImageR[i][k] = 0; m_OutputImageG[i][k] = 0; m_OutputImageB[i][k] = 0; }
		}
	}
}


void CImagePSHDoc::OnBwInputImage()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImageR == NULL) {
		MessageBox(NULL, L"파일이 열리지 않았습니다.", L"", 0);
		return;
	}
	// 기존 출력 메모리 해제
	free2D(m_OutputImageR, m_outH);
	free2D(m_OutputImageG, m_outH);
	free2D(m_OutputImageB, m_outH);
	//(중요!) 출력 영상의 높이와 폭을 결정 --> 알고리즘에 따름
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 영상 메모리 할당
	m_OutputImageR = malloc2D(m_outH, m_outW);
	m_OutputImageG = malloc2D(m_outH, m_outW);
	m_OutputImageB = malloc2D(m_outH, m_outW);

	//Input1 으로 입력받기
	CInputDlg dlg;					// 인스턴스
	if (dlg.DoModal() != IDOK)		// 화면띄우기
		return;
	int value = (int)dlg.m_input1;	// 대화상자 내에 Value 받음	

	// 진짜 영상 처리 알고리즘
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int px = (m_InputImageR[i][k] + m_InputImageG[i][k] + m_InputImageB[i][k]) / 3;
			if (px > value) { m_OutputImageR[i][k] = 255; m_OutputImageG[i][k] = 255; m_OutputImageB[i][k] = 255; }
			else { m_OutputImageR[i][k] = 0; m_OutputImageG[i][k] = 0; m_OutputImageB[i][k] = 0; }
		}
	}
}


void CImagePSHDoc::OnGrayImage()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImageR == NULL) {
		MessageBox(NULL, L"파일이 열리지 않았습니다.", L"", 0);
		return;
	}
	// 기존 출력 메모리 해제
	free2D(m_OutputImageR, m_outH);
	free2D(m_OutputImageG, m_outH);
	free2D(m_OutputImageB, m_outH);
	//(중요!) 출력 영상의 높이와 폭을 결정 --> 알고리즘에 따름
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 영상 메모리 할당
	m_OutputImageR = malloc2D(m_outH, m_outW);
	m_OutputImageG = malloc2D(m_outH, m_outW);
	m_OutputImageB = malloc2D(m_outH, m_outW);
	int avg = 0;
	// 진짜 영상 처리 알고리즘
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			avg = (int)((m_InputImageR[i][k] + m_InputImageG[i][k] + m_InputImageB[i][k]) / 3);
			m_OutputImageR[i][k] = avg;
			m_OutputImageG[i][k] = avg;
			m_OutputImageB[i][k] = avg;
		}
	}
}


void CImagePSHDoc::OnNgtvImage()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImageR == NULL) {
		MessageBox(NULL, L"파일이 열리지 않았습니다.", L"", 0);
		return;
	}
	// 기존 출력 메모리 해제
	free2D(m_OutputImageR, m_outH);
	free2D(m_OutputImageG, m_outH);
	free2D(m_OutputImageB, m_outH);
	//(중요!) 출력 영상의 높이와 폭을 결정 --> 알고리즘에 따름
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 영상 메모리 할당
	m_OutputImageR = malloc2D(m_outH, m_outW);
	m_OutputImageG = malloc2D(m_outH, m_outW);
	m_OutputImageB = malloc2D(m_outH, m_outW);

	// 진짜 영상 처리 알고리즘
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_OutputImageR[i][k] = 255 - m_InputImageR[i][k];
			m_OutputImageG[i][k] = 255 - m_InputImageR[i][k];
			m_OutputImageB[i][k] = 255 - m_InputImageR[i][k];
		}
	}
}


void CImagePSHDoc::OnLightPmImage()
{
	// TODO: 여기에 구현 코드 추가.
}


void CImagePSHDoc::OnLightMdImage()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_InputImageR == NULL) {
		MessageBox(NULL, L"파일이 열리지 않았습니다.", L"", 0);
		return;
	}
	// 기존 출력 메모리 해제
	free2D(m_OutputImageR, m_outH);
	free2D(m_OutputImageG, m_outH);
	free2D(m_OutputImageB, m_outH);
	//(중요!) 출력 영상의 높이와 폭을 결정 --> 알고리즘에 따름
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 영상 메모리 할당
	m_OutputImageR = malloc2D(m_outH, m_outW);
	m_OutputImageG = malloc2D(m_outH, m_outW);
	m_OutputImageB = malloc2D(m_outH, m_outW);

	// 진짜 영상 처리 알고리즘
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_InputImageR[i][k] + 100 > 255) m_OutputImageR[i][k] = 255;
			else m_OutputImageR[i][k] = m_InputImageR[i][k] + 100;
			if (m_InputImageG[i][k] + 100 > 255) m_OutputImageG[i][k] = 255;
			else m_OutputImageG[i][k] = m_InputImageG[i][k] + 100;
			if (m_InputImageB[i][k] + 100 > 255) m_OutputImageB[i][k] = 255;
			else m_OutputImageB[i][k] = m_InputImageB[i][k] + 100;
		}
	}
}
