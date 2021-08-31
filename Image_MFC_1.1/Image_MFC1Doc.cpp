
// Image_MFC1Doc.cpp: CImageMFC1Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Image_MFC1.h"
#endif

#include "Image_MFC1Doc.h"
#include "CInputDlg.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageMFC1Doc

IMPLEMENT_DYNCREATE(CImageMFC1Doc, CDocument)

BEGIN_MESSAGE_MAP(CImageMFC1Doc, CDocument)
END_MESSAGE_MAP()


// CImageMFC1Doc 생성/소멸

CImageMFC1Doc::CImageMFC1Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageMFC1Doc::~CImageMFC1Doc()
{
}

BOOL CImageMFC1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}


// CImageMFC1Doc serialization

void CImageMFC1Doc::Serialize(CArchive& ar)
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
void CImageMFC1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CImageMFC1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageMFC1Doc::SetSearchContent(const CString& value)
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

// CImageMFC1Doc 진단

#ifdef _DEBUG
void CImageMFC1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageMFC1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageMFC1Doc 명령


BOOL CImageMFC1Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CFile rfp;
	rfp.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);
	// 기존입력 메모리 해제
	free2D(m_InputImage, m_inH);
	// 파일 크기 알아내기
	unsigned long fsize = rfp.GetLength();
	// (중요!) 영상의 높이와 폭 계산
	m_inH = m_inW = (int)sqrt((double)fsize);
	// 메모리 할당.	
	m_InputImage = malloc2D(m_inH, m_inW);
	// 파일 --> 메모리로 로딩
	for (int i = 0; i < m_inH; i++)
		rfp.Read(m_InputImage[i],  m_inW);
	rfp.Close();


	return TRUE;
}


void CImageMFC1Doc::free2D(unsigned char** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory != NULL) {
		for (int i = 0; i < h; i++)
			free(memory[i]);
		free(memory);
	}
}


unsigned char** CImageMFC1Doc::malloc2D(int h, int w)
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


void CImageMFC1Doc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	free2D(m_InputImage, m_inH); // 임의로 만들어둔 2차원 free();
	free2D(m_OutputImage, m_outH);
	CDocument::OnCloseDocument();
}

// 실수의 절대 값 연산 함수
double CImageMFC1Doc::doubleABS(double x)
{
	// TODO: 여기에 구현 코드 추가.

	if (x >= 0) return x;
	else        return -x;
}

// 저장 로직 다시짜야함
BOOL CImageMFC1Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CFileDialog SaveDlg(FALSE, L"raw", NULL, OFN_HIDEREADONLY);
	if (SaveDlg.DoModal() != IDOK)
		return FALSE;

	CFile File;
	File.Open(SaveDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);
	for (int i = 0; i < m_outH; i++)
		File.Write(m_OutputImage[i], m_outW);
	File.Close();

	return CDocument::OnSaveDocument(lpszPathName);
}

// 2차원 double형 동적배열 선언
double** CImageMFC1Doc::malloc2D_double(int h, int w)
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

// 2차원 double형 동적배열 초기화
void CImageMFC1Doc::free2D_double(double** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory != NULL) {
		for (int i = 0; i < h; i++)
			free(memory[i]);
		free(memory);
	}
}

void CImageMFC1Doc::OnEqualImage()
{
	// TODO: 여기에 구현 코드 추가.
	
	// 기존 출력 메모리 해제
	free2D(m_OutputImage, m_outH);
	//(중요!) 출력 영상의 높이와 폭을 결정 (알고리즘에 따름)
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 영상 메모리 할당
	m_OutputImage = malloc2D(m_outH, m_outW);

	// 진짜 영상 처리 알고리즘
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_OutputImage[i][k] = m_InputImage[i][k];
		}
	}
}

// OnBwValImage() : 입력값 중심 반전효과
void CImageMFC1Doc::OnBwValImage()
{
	// TODO: 여기에 구현 코드 추가.
	
	// 기존 출력 메모리 해제
	free2D(m_OutputImage, m_outH);
	//(중요!) 출력 영상의 높이와 폭을 결정 (알고리즘에 따름)
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 영상 메모리 할당
	m_OutputImage = malloc2D(m_outH, m_outW);

	//Input1 으로 입력받기
	CInputDlg dlg;					// 인스턴스
	if (dlg.DoModal() != IDOK)		// 화면띄우기
		return;
	int value = (int)dlg.m_input1;	// 대화상자 내에 Value 받음	

	// 진짜 영상 처리 알고리즘
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_InputImage[i][k] > value) m_OutputImage[i][k] = 255;
			else m_OutputImage[i][k] = 0;
		}
	}
}


void CImageMFC1Doc::OnBw127Image()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;
	m_OutputImage = malloc2D(m_outH, m_outW);
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_InputImage[i][k] > 127) m_OutputImage[i][k] = 255;
			else m_OutputImage[i][k] = 0;
		}
	}
}


void CImageMFC1Doc::OnBwAvgImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;
	m_OutputImage = malloc2D(m_outH, m_outW);

	unsigned long hap = 0;
	int cnt = 0;
	int avg = 0;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			hap += m_InputImage[i][k];
			cnt++;
		}
	}
	avg = (int)hap / cnt;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_InputImage[i][k] >= avg) m_OutputImage[i][k] = 255;
			else m_OutputImage[i][k] = 0;
		}
	}
}


void CImageMFC1Doc::OnLightPmImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;
	m_OutputImage = malloc2D(m_outH, m_outW);

	//Input1 으로 입력받기
	CInputDlg dlg;					// 인스턴스
	if (dlg.DoModal() != IDOK)		// 화면띄우기
		return;
	int value = (int)dlg.m_input1;	// 대화상자 내에 Value 받음	

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_OutputImage[i][k] += value;
			if ((m_InputImage[i][k] + value) > 255) m_OutputImage[i][k] = 255;
			else if ((m_InputImage[i][k] + value) <= 0) m_OutputImage[i][k] = 0;
			else m_OutputImage[i][k] = m_InputImage[i][k] + value;
		}
	}
}


void CImageMFC1Doc::OnLightGnImage()
{
	// TODO: 여기에 구현 코드 추가.
		// 기존 출력 메모리 해제
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;
	m_OutputImage = malloc2D(m_outH, m_outW);

	//Input1 으로 입력받기
	CInputDlg dlg;					// 인스턴스
	if (dlg.DoModal() != IDOK)		// 화면띄우기
		return;
	int value = (int)dlg.m_input1;	// 대화상자 내에 Value 받음	

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if ((m_InputImage[i][k] * value) > 255) m_OutputImage[i][k] = 255;
			else if ((m_InputImage[i][k] * value) <= 0) m_OutputImage[i][k] = 0;
			else m_OutputImage[i][k] = m_InputImage[i][k] * value;
		}
	}

}


void CImageMFC1Doc::OnNgtImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;
	m_OutputImage = malloc2D(m_outH, m_outW);
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_OutputImage[i][k] = 255 - m_InputImage[i][k];
		}
	}
}


void CImageMFC1Doc::OnGammaImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;
	m_OutputImage = malloc2D(m_outH, m_outW);

	//Input1 으로 입력받기
	CInputDlg dlg;					// 인스턴스
	if (dlg.DoModal() != IDOK)		// 화면띄우기
		return;
	float gamma = (float)dlg.m_input1;	// 대화상자 내에 Value 받음

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double m = m_InputImage[i][k];
			m_OutputImage[i][k] = (unsigned int)255.0 * pow(m / 255.0, gamma); // pow(a,b) ; a의 b 제곱
		}
	}
}


void CImageMFC1Doc::OnParaCapImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH; m_outW = m_inW;
	m_OutputImage = malloc2D(m_outH, m_outW);

	//Input1 으로 입력받기
	CInputDlg dlg;					// 인스턴스
	if (dlg.DoModal() != IDOK)		// 화면띄우기
		return;
	int value = (int)dlg.m_input1;	// 대화상자 내에 Value 받음	

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			//pow()// 거듭제곱 : x의 y제곱
			double value = 255.0 - 255.0 * pow((m_InputImage[i][k] / 128.0 - 1.0), 2); //밝은 곳 입체형 (CAP)
			if (value > 255.0) value = 255.0;
			else if (value < 0.0) value = 0.0;

			m_OutputImage[i][k] = (unsigned)value;
		}
	}
}


void CImageMFC1Doc::OnParaCupImage()
{
	// TODO: 여기에 구현 코드 추가.
	// TODO: 여기에 구현 코드 추가.
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH; m_outW = m_inW;
	m_OutputImage = malloc2D(m_outH, m_outW);

	//Input1 으로 입력받기
	CInputDlg dlg;					// 인스턴스
	if (dlg.DoModal() != IDOK)		// 화면띄우기
		return;
	int value = (int)dlg.m_input1;	// 대화상자 내에 Value 받음	

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			//pow()// 거듭제곱 : x의 y제곱
			double value = 255.0 * pow((m_InputImage[i][k] / 128.0 - 1.0), 2); //밝은 곳 입체형 (CAP)
			if (value > 255.0) value = 255.0;
			else if (value < 0.0) value = 0.0;

			m_OutputImage[i][k] = (unsigned)value;
		}
	}
}


void CImageMFC1Doc::OnZminNrmlImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 출력 메모리 해제
	free2D(m_OutputImage, m_outH);

	//Input1 으로 입력받기
	CInputDlg dlg;					// 인스턴스
	if (dlg.DoModal() != IDOK)		// 화면띄우기
		return;
	int scale = (int)dlg.m_input1;	// 대화상자 내에 Value 받음
	m_outH = m_inH * scale;
	m_outW = m_inW * scale;

	m_OutputImage = malloc2D(m_outH, m_outW);

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_OutputImage[i * scale][k * scale] = m_InputImage[i][k];
		}
	}
}


void CImageMFC1Doc::OnZminNhImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 출력 메모리 해제
	free2D(m_OutputImage, m_outH);

	//Input1 으로 입력받기
	CInputDlg dlg;					// 인스턴스
	if (dlg.DoModal() != IDOK)		// 화면띄우기
		return;
	int scale = (int)dlg.m_input1;	// 대화상자 내에 Value 받음
	m_outH = m_inH * scale;
	m_outW = m_inW * scale;

	m_OutputImage = malloc2D(m_outH, m_outW);

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_OutputImage[i][k] = m_InputImage[i / scale][k / scale];
		}
	}

}


void CImageMFC1Doc::OnZminYsImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_OutputImage, m_outH);
	double scale = 0.0;

	//Input1 으로 입력받기
	CInputDlg dlg;					// 인스턴스
	if (dlg.DoModal() != IDOK)		// 화면띄우기
		return;
	scale = (double)dlg.m_input1;	// 대화상자 내에 Value 받음

	m_outH = m_inH * scale;
	m_outW = m_inW * scale;
	double** tempImage = malloc2D_double(m_inH, m_inW);
	m_OutputImage = malloc2D(m_outH, m_outW);

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tempImage[i][k] = (double)m_InputImage[i][k];
		}
	}

	double r_H, r_W, s_H, s_W;
	int i_W, i_H;
	double C1, C2, C3, C4;
	int v = 0;
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			r_H = i / scale;
			r_W = k / scale;

			i_H = (int)floor(r_H); //  내림. celi = 올림
			i_W = (int)floor(r_W);

			s_H = r_H - i_H;
			s_W = r_W - i_W;

			if (i_H < 0 || i_H >= (m_inH - 1) || i_W < 0 || i_W >= (m_inW - 1)) {
				m_OutputImage[i][k] = 255;
			}
			else
			{
				C1 = (double)tempImage[i_H][i_W];           // A
				C2 = (double)tempImage[i_H][i_W + 1];       // B
				C3 = (double)tempImage[i_H + 1][i_W + 1];   // C
				C4 = (double)tempImage[i_H + 1][i_W];       // D
			}
			v = (unsigned char)(C1 * (1 - s_H) * (1 - s_W) + C2 * s_W * (1 - s_H)
				+ C3 * s_W * s_H + C4 * (1 - s_W) * s_H);
			m_OutputImage[i][k] = v;
		}
	}
	free2D_double(tempImage, m_inH);
}


void CImageMFC1Doc::OnZoutImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 출력 메모리 해제
	free2D(m_OutputImage, m_outH);

	//Input1 으로 입력받기
	CInputDlg dlg;					// 인스턴스
	if (dlg.DoModal() != IDOK)		// 화면띄우기
		return;
	int scale = (int)dlg.m_input1;	// 대화상자 내에 Value 받음
	m_outH = m_inH * scale;
	m_outW = m_inW * scale;

	m_OutputImage = malloc2D(m_outH, m_outW);

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_OutputImage[i][k] = m_InputImage[i / scale][k / scale];
		}
	}
}


void CImageMFC1Doc::OnTurnImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_OutputImage, m_outH);
	// 진짜 영상 처리 알고리즘
	int angle; // 0 ~ 360

	//Input1 으로 입력받기
	CInputDlg dlg;					// 인스턴스
	if (dlg.DoModal() != IDOK)		// 화면띄우기
		return;
	angle = (int)dlg.m_input1;	// 대화상자 내에 Value 받음
	double tmp_radian = angle % 90 * 3.141592 / 180.0;
	double tmp_radian90 = (90 - angle % 90) * 3.141592 / 180.0;

	//(중요!) 출력 영상의 높이와 폭을 결정 --> 알고리즘에 따름
	m_outH = (int)(m_inH * cos(tmp_radian90) + m_inW * cos(tmp_radian));
	m_outW = (int)(m_inW * cos(tmp_radian) + m_inW * cos(tmp_radian90));
	// 출력 영상 메모리 할당
	double radian = angle * 3.141592 / 180.0;
	m_OutputImage = malloc2D(m_outH, m_outW);

	// 임시 입력 영상 ---> 출력과 크기가 같게 하고, 입력 영상을 중앙에 두기.
	unsigned char** tmpInput = malloc2D(m_outH, m_outW);
	int dx = (m_outH - m_inH) / 2;
	int dy = (m_outW - m_inW) / 2;
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInput[i + dx][k + dy] = m_InputImage[i][k];

	// 중앙 위치 구하기
	int cx = m_outH / 2;
	int cy = m_outW / 2;
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			int oldI = (cos(radian) * (i - cx) + sin(radian) * (k - cy)) + cx;
			int oldK = (-sin(radian) * (i - cx) + cos(radian) * (k - cy)) + cy;
			if (((0 <= oldI) && (oldI < m_outH)) && ((0 <= oldK) && (oldK < m_outW)))
				m_OutputImage[i][k] = tmpInput[oldI][oldK];
		}
	}
	free2D(tmpInput, m_outH);
}


void CImageMFC1Doc::OnMoveImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_OutputImage, m_outH);
	int input = 0;

	//Input1 으로 입력받기
	CInputDlg dlg;					// 인스턴스
	if (dlg.DoModal() != IDOK)		// 화면띄우기
		return;
	input = (int)dlg.m_input1;	// 대화상자 내에 Value 받음
	if (m_inH < input) input = 0;

	m_outH = m_inH + input;
	m_outW = m_inW + input;
	m_OutputImage = malloc2D(m_outH, m_outW);

	for (int i = input; i < m_inH; i++) {
		for (int k = input; k < m_inW; k++) {

			m_OutputImage[i+input][k+input] = m_InputImage[i][k];
		}
	}
}


void CImageMFC1Doc::OnMirrorUdImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;
	m_OutputImage = malloc2D(m_outH, m_outW);
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_OutputImage[i][k] = m_InputImage[m_inH - i - 1][k];
		}
	}
}


void CImageMFC1Doc::OnMirrorLrImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;
	m_OutputImage = malloc2D(m_outH, m_outW);
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_OutputImage[i][k] = m_InputImage[i][m_inW - k - 1];
		}
	}
}


void CImageMFC1Doc::OnEmbosImage()
{
	// TODO: 여기에 구현 코드 추가.
		// 기존 출력 메모리 해제
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;
	m_OutputImage = malloc2D(m_outH, m_outW);
	//(중요!) 화소영역 알고리즘에 해당하는 마스크 (엠보싱)
	double mask[3][3] = { {-1.,0.,0.},
						  {0.,0.,0.},
						  {0.,0.,1.} };
	// 임시 입력/출력 메모리 준비
	double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
	double** tmpOutput = malloc2D_double(m_outH, m_outW);
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInput[i + 1][k + 1] = m_InputImage[i][k]; // 임시Input의 중심에 사진을 넣는중.
		}
	}

	// 진짜 영상 처리 알고리즘 ==> 회선연산
	double S; // 마스크9개 X 입력영상 9개의 합
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0; // 누적 값은 초기화하는 것 권장
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					S += tmpInput[i + m][k + n] * mask[m][n];
				}
			}
			tmpOutput[i][k] = S;
		}
	}

	// 마무리 (다듬기) --> 마스크합계가 0 또는 1 이면 127 더하기
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			tmpOutput[i][k] += 127.0;
		}
	}
	// tmpOutput -> m_OutputImage // 오버플로우, 언더플로우 확인 후.
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			double v = tmpOutput[i][k];
			if (v > 255.0) v = 255.0;
			if (v < 0.0) v = 0.0;
			m_OutputImage[i][k] = (unsigned char)v;
		}
	}
	free2D_double(tmpInput, m_inH + 2);
	free2D_double(tmpOutput, m_outH);
}


void CImageMFC1Doc::OnBlrAvgImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 출력 메모리 해제
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;
	m_OutputImage = malloc2D(m_outH, m_outW);
	int input = 0;

	//Input1 으로 입력받기
	CInputDlg dlg;					// 인스턴스
	if (dlg.DoModal() != IDOK)		// 화면띄우기
		return;
	input = (int)dlg.m_input1;	// 대화상자 내에 Value 받음
	if (input % 2 == 0) {
		input += 1;
	}

	double** mask = malloc2D_double(input, input);
	for (int i = 0; i < input; i++) {
		for (int k = 0; k < input; k++) {
			mask[i][k] = (double)(1.0 / ((double)(input * input)));
		}
	}
	// 임시 입력/출력 메모리 준비
	double** tmpInput = malloc2D_double(m_inH + (int)(input / 2) * 2, m_inW + (int)(input / 2) * 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
	double** tmpOutput = malloc2D_double(m_outH, m_outW);
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInput[i + (int)(input / 2)][k + (int)(input / 2)] = m_InputImage[i][k];
		}
	}

	// 진짜 영상 처리 알고리즘 ==> 회선연산
	double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0; // 누적 값은 초기화하는 것 권장
			for (int m = 0; m < input; m++) {
				for (int n = 0; n < input; n++) {
					S += tmpInput[i + m][k + n] * mask[m][n];
				}
			}
			tmpOutput[i][k] = S;
		}
	}
	//// 마무리 (다듬기) --> 마스크합계가 0 또는 1 이면 127 더하기
	//for (int i = 0; i < m_outH; i++) {
	//    for (int k = 0; k < m_outW; k++) {
	//        tmpOutput[i][k] += 127.0;
	//    }
	//}
	// tmpOutput -> m_OutputImage // 오버플로우, 언더플로우 확인 후.

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			double v = tmpOutput[i][k];
			if (v > 255.0) v = 255.0;
			if (v < 0.0) v = 0.0;
			m_OutputImage[i][k] = (unsigned char)v;
		}
	}
	free2D_double(tmpInput, m_inH + (int)(input / 2) * 2);
	free2D_double(tmpOutput, m_outH);
}


void CImageMFC1Doc::OnBlrGausImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;
	m_OutputImage = malloc2D(m_outH, m_outW);
	//(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
	double mask[3][3] = { {1 / 16.,1 / 8.,1 / 16.},
						  {1 / 8.,1 / 4.,1 / 8.},
						  {1 / 16.,1 / 8.,1 / 16.} };
	// 임시 입력/출력 메모리 준비
	double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
	double** tmpOutput = malloc2D_double(m_outH, m_outW);
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInput[i + 1][k + 1] = m_InputImage[i][k];
		}
	}

	// 진짜 영상 처리 알고리즘 ==> 회선연산
	double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0; // 누적 값은 초기화하는 것 권장
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					S += tmpInput[i + m][k + n] * mask[m][n];
				}
			}
			tmpOutput[i][k] = S;
		}
	}

	//// 마무리 (다듬기) --> 마스크합계가 0 또는 1 이면 127 더하기
	//for (int i = 0; i < m_outH; i++) {
	//    for (int k = 0; k < m_outW; k++) {
	//        tmpOutput[i][k] += 127.0;
	//    }
	//}
	// tmpOutput -> m_OutputImage // 오버플로우, 언더플로우 확인 후.
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			double v = tmpOutput[i][k];
			if (v > 255.0) v = 255.0;
			if (v < 0.0) v = 0.0;
			m_OutputImage[i][k] = (unsigned char)v;
		}
	}
	free2D_double(tmpInput, m_inH + 2);
	free2D_double(tmpOutput, m_outH);
}


void CImageMFC1Doc::OnHpfImage()
{
	// TODO: 여기에 구현 코드 추가.
	 // 기존 출력 메모리 해제
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;
	m_OutputImage = malloc2D(m_outH, m_outW);
	//(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
	double mask[3][3] = { {0.,-1.,0},
						  {-1., 5.,-1.},
						  {0,-1.,0.} };
	// 임시 입력/출력 메모리 준비
	double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
	double** tmpOutput = malloc2D_double(m_outH, m_outW);
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInput[i + 1][k + 1] = m_InputImage[i][k];
		}
	}

	// 진짜 영상 처리 알고리즘 ==> 회선연산
	double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0; // 누적 값은 초기화하는 것 권장
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					S += tmpInput[i + m][k + n] * mask[m][n];
				}
			}
			tmpOutput[i][k] = S;
		}
	}

	//// 마무리 (다듬기) --> 마스크합계가 0 또는 1 이면 127 더하기
	//for (int i = 0; i < m_outH; i++) {
	//    for (int k = 0; k < m_outW; k++) {
	//        tmpOutput[i][k] += 127.0;
	//    }
	//}
	// tmpOutput -> m_OutputImage // 오버플로우, 언더플로우 확인 후.
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			double v = tmpOutput[i][k];
			if (v > 255.0) v = 255.0;
			if (v < 0.0) v = 0.0;
			m_OutputImage[i][k] = (unsigned char)v;
		}
	}
	free2D_double(tmpInput, m_inH + 2);
	free2D_double(tmpOutput, m_outH);
}


void CImageMFC1Doc::OnLpfImage()
{
	// TODO: 여기에 구현 코드 추가.
	 // 기존 출력 메모리 해제
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;
	m_OutputImage = malloc2D(m_outH, m_outW);
	//(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
	double mask[3][3] = { {-1. / 9.,1 / 9.,-1. / 9.},
						  {-1. / 9.,8. / 9.,-1. / 8.},
						  {-1. / 9.,1 / 9.,-1. / 9.} };
	// 임시 입력/출력 메모리 준비
	double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
	double** tmpOutput = malloc2D_double(m_outH, m_outW);
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInput[i + 1][k + 1] = m_InputImage[i][k];
		}
	}

	// 진짜 영상 처리 알고리즘 ==> 회선연산
	double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0; // 누적 값은 초기화하는 것 권장
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					S += tmpInput[i + m][k + n] * mask[m][n];
				}
			}
			tmpOutput[i][k] = S;
		}
	}

	//// 마무리 (다듬기) --> 마스크합계가 0 또는 1 이면 127 더하기
	//for (int i = 0; i < m_outH; i++) {
	//    for (int k = 0; k < m_outW; k++) {
	//        tmpOutput[i][k] += 127.0;
	//    }
	//}
	// tmpOutput -> m_OutputImage // 오버플로우, 언더플로우 확인 후.
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			double v = tmpOutput[i][k];
			if (v > 255.0) v = 255.0;
			if (v < 0.0) v = 0.0;
			m_OutputImage[i][k] = (unsigned char)v;
		}
	}
	free2D_double(tmpInput, m_inH + 2);
	free2D_double(tmpOutput, m_outH);
}


void CImageMFC1Doc::OnCalcUsaImage()
{
	// TODO: 여기에 구현 코드 추가.
		// 기존 출력 메모리 해제
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;
	m_OutputImage = malloc2D(m_outH, m_outW);
	// 임시 입력/출력 메모리 준비
	double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
	double** tmpOutput = malloc2D_double(m_outH, m_outW);
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInput[i + 1][k + 1] = m_InputImage[i][k];
		}
	}

	// 진짜 영상 처리 알고리즘 ==> 회선연산
	double max = 0.0; // 블록이 이동할 때 마다 최대값
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			max = 0.0; // 최대값도 초기화
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					if (doubleABS(tmpInput[i + 1][k + 1] -
						tmpInput[i + m][k + n]) >= max)
						// 블록의 가운대값 - 블록의 주변 픽셀값의 절대값 중에서
						// 최대값을 찾는다.
						max = doubleABS(tmpInput[i + 1][k + 1] - tmpInput[i + m][k + n]);
				}
			}
			tmpOutput[i][k] = max;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			double v = tmpOutput[i][k];
			if (v > 255.0) v = 255.0;
			if (v < 0.0) v = 0.0;
			m_OutputImage[i][k] = (unsigned char)v;
		}
	}
	free2D_double(tmpInput, m_inH + 2);
	free2D_double(tmpOutput, m_outH);
}


void CImageMFC1Doc::OnCalcMnsImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 출력 메모리 해제
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;
	m_OutputImage = malloc2D(m_outH, m_outW);
	// 임시 입력/출력 메모리 준비
	double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
	double** tmpOutput = malloc2D_double(m_outH, m_outW);
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInput[i + 1][k + 1] = m_InputImage[i][k];
		}
	}

	// 진짜 영상 처리 알고리즘 ==> 회선연산
	double max = 0.0; // 블록이 이동할 때 마다 최대값
	double mask[4] = { 0, };
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			max = 0.0; // 최대값 초기화
			mask[0] = doubleABS(tmpInput[i][k] - tmpInput[i + 2][k + 2]);
			mask[1] = doubleABS(tmpInput[i][k + 1] - tmpInput[i + 2][k + 1]);
			mask[2] = doubleABS(tmpInput[i][k + 2] - tmpInput[i + 2][k]);
			mask[3] = doubleABS(tmpInput[i + 1][k] - tmpInput[i + 1][k + 2]);
			for (int m = 0; m < 4; m++) {
				if (mask[m] >= max) max = mask[m];
			}
			tmpOutput[i][k] = max;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			double v = tmpOutput[i][k];
			if (v > 255.0) v = 255.0;
			if (v < 0.0) v = 0.0;
			m_OutputImage[i][k] = (unsigned char)v;
		}
	}
	free2D_double(tmpInput, m_inH + 2);
	free2D_double(tmpOutput, m_outH);
}


void CImageMFC1Doc::OnRbrtsImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;
	m_OutputImage = malloc2D(m_outH, m_outW);
	//(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
	double maskV[3][3]
		= { {-1,0,0} ,
			{0,1,0} ,
			{0,0,0} };
	double maskH[3][3]
		= { {0,0,-1} ,
			{0,1,0} ,
			{0,0,0} };

	// 임시 입력/출력 메모리 준비
	double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
	double** tmpOutput = malloc2D_double(m_outH, m_outW);
	double** tmpOutput2 = malloc2D_double(m_outH, m_outW);
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInput[i + 1][k + 1] = m_InputImage[i][k];
		}
	}

	// 진짜 영상 처리 알고리즘 ==> 회선연산
	double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0; // 누적 값은 초기화하는 것 권장
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					S += tmpInput[i + m][k + n] * maskH[m][n];
				}
			}
			tmpOutput[i][k] = S;
		}
	}
	S = 0.0; // 마스크9개 X 입력영상 9개의 합...
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0; // 누적 값은 초기화하는 것 권장
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					S += tmpInput[i + m][k + n] * maskV[m][n];
				}
			}
			tmpOutput2[i][k] = S;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			double v1 = tmpOutput[i][k];
			double v2 = tmpOutput[i][k];
			double v = v1 + v2;
			if (v > 255.0) v = 255.0;
			if (v < 0.0) v = 0.0;
			m_OutputImage[i][k] = (unsigned char)v;
		}
	}
	free2D_double(tmpInput, m_inH + 2);
	free2D_double(tmpOutput, m_outH);
	free2D_double(tmpOutput2, m_outH);
}


void CImageMFC1Doc::OnPrwImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;
	m_OutputImage = malloc2D(m_outH, m_outW);
	//(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
	double maskV[3][3]
		= { {-1,0,1} ,
			{-1,0,1} ,
			{-1,0,1} };
	double maskH[3][3]
		= { {1,1,1} ,
			{0,0,0} ,
			{-1,-1,-1} };


	// 임시 입력/출력 메모리 준비
	double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
	double** tmpOutput = malloc2D_double(m_outH, m_outW);
	double** tmpOutput2 = malloc2D_double(m_outH, m_outW);
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInput[i + 1][k + 1] = m_InputImage[i][k];
		}
	}

	// 진짜 영상 처리 알고리즘 ==> 회선연산
	double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0; // 누적 값은 초기화하는 것 권장
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					S += tmpInput[i + m][k + n] * maskH[m][n];
				}
			}
			tmpOutput[i][k] = S;
		}
	}
	S = 0.0; // 마스크9개 X 입력영상 9개의 합...
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0; // 누적 값은 초기화하는 것 권장
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					S += tmpInput[i + m][k + n] * maskV[m][n];
				}
			}
			tmpOutput2[i][k] = S;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			double v1 = tmpOutput[i][k];
			double v2 = tmpOutput[i][k];
			double v = v1 + v2;
			if (v > 255.0) v = 255.0;
			if (v < 0.0) v = 0.0;
			m_OutputImage[i][k] = (unsigned char)v;
		}
	}
	free2D_double(tmpInput, m_inH + 2);
	free2D_double(tmpOutput, m_outH);
	free2D_double(tmpOutput2, m_outH);
}


void CImageMFC1Doc::OnSoblImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 출력 메모리 해제
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;
	m_OutputImage = malloc2D(m_outH, m_outW);
	//(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
	double maskV[3][3]
		= { {1,2,1} ,
			{0,0,0} ,
			{-1,-2,-1} };
	double maskH[3][3]
		= { {-1,0,1} ,
		   {-2,0,2} ,
		   {-1,0,1} };

	// 임시 입력/출력 메모리 준비
	double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
	double** tmpOutput = malloc2D_double(m_outH, m_outW);
	double** tmpOutput2 = malloc2D_double(m_outH, m_outW);
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInput[i + 1][k + 1] = m_InputImage[i][k];
		}
	}

	// 진짜 영상 처리 알고리즘 ==> 회선연산
	double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0; // 누적 값은 초기화하는 것 권장
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					S += tmpInput[i + m][k + n] * maskH[m][n];
				}
			}
			tmpOutput[i][k] = S;
		}
	}
	S = 0.0; // 마스크9개 X 입력영상 9개의 합...
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0; // 누적 값은 초기화하는 것 권장
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					S += tmpInput[i + m][k + n] * maskV[m][n];
				}
			}
			tmpOutput2[i][k] = S;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			double v1 = tmpOutput[i][k];
			double v2 = tmpOutput[i][k];
			double v = v1 + v2;
			if (v > 255.0) v = 255.0;
			if (v < 0.0) v = 0.0;
			m_OutputImage[i][k] = (unsigned char)v;
		}
	}
	free2D_double(tmpInput, m_inH + 2);
	free2D_double(tmpOutput, m_outH);
	free2D_double(tmpOutput2, m_outH);
}


void CImageMFC1Doc::OnLaplaImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 출력 메모리 해제
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;
	m_OutputImage = malloc2D(m_outH, m_outW);
	//(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
	double mask[3][3]
		= { {-1,-1,-1} ,
			{-1,8,-1} ,
			{-1,-1,-1} };

	// 임시 입력/출력 메모리 준비
	double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
	double** tmpOutput = malloc2D_double(m_outH, m_outW);
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInput[i + 1][k + 1] = m_InputImage[i][k];
		}
	}

	// 진짜 영상 처리 알고리즘 ==> 회선연산
	double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0; // 누적 값은 초기화하는 것 권장
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					S += tmpInput[i + m][k + n] * mask[m][n];
				}
			}
			tmpOutput[i][k] = S;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			double v = tmpOutput[i][k];
			if (v > 255.0) v = 255.0;
			if (v < 0.0) v = 0.0;
			m_OutputImage[i][k] = (unsigned char)v;
		}
	}
	free2D_double(tmpInput, m_inH + 2);
	free2D_double(tmpOutput, m_outH);
}


void CImageMFC1Doc::OnLogImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 출력 메모리 해제
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;
	m_OutputImage = malloc2D(m_outH, m_outW);
	//(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
	double mask[5][5]
		= { {0,0,-1,0,0} ,
			{0,-1,-2,-1,0} ,
			{-1,-2,16,-2,-1},
			{0,-1,-2,-1,0} ,
			{0,0,-1,0,0} };

	// 임시 입력/출력 메모리 준비
	double** tmpInput = malloc2D_double(m_inH + 4, m_inW + 4); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
	double** tmpOutput = malloc2D_double(m_outH, m_outW);
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInput[i + 2][k + 2] = m_InputImage[i][k];
		}
	}

	// 진짜 영상 처리 알고리즘 ==> 회선연산
	double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0; // 누적 값은 초기화하는 것 권장
			for (int m = 0; m < 5; m++) {
				for (int n = 0; n < 5; n++) {
					S += tmpInput[i + m][k + n] * mask[m][n];
				}
			}
			tmpOutput[i][k] = S;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			double v = tmpOutput[i][k];
			if (v > 255.0) v = 255.0;
			if (v < 0.0) v = 0.0;
			m_OutputImage[i][k] = (unsigned char)v;
		}
	}
	free2D_double(tmpInput, m_inH + 4);
	free2D_double(tmpOutput, m_outH);
}


void CImageMFC1Doc::OnDogImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 출력 메모리 해제
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;
	m_OutputImage = malloc2D(m_outH, m_outW);
	//(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
	double mask[9][9]
		= { {0,0,0,-1,-1,-1,0,0,0},
			{0,-2,-3,-3,-3,-3,-3,-2,0},
			{0,-3,-2,-1,-1,-1,-2,-3,0},
			{0,-3,-1,9,9,9,-1,-3,0},
			{-1,-3,-1,9,19,9,-1,-3,-1},
			{0,-3,-1,9,9,9,-1,-3,0},
			{0,-3,-2,-1,-1,-1,-2,-3,0},
			{0,-2,-3,-3,-3,-3,-3,-2,0},
			{0,0,0,-1,-1,-1,0,0,0}
	};

	// 임시 입력/출력 메모리 준비
	double** tmpInput = malloc2D_double(m_inH + 8, m_inW + 8); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
	double** tmpOutput = malloc2D_double(m_outH, m_outW);
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInput[i + 4][k + 4] = m_InputImage[i][k];
		}
	}

	// 진짜 영상 처리 알고리즘 ==> 회선연산
	double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0; // 누적 값은 초기화하는 것 권장
			for (int m = 0; m < 9; m++) {
				for (int n = 0; n < 9; n++) {
					S += tmpInput[i + m][k + n] * mask[m][n];
				}
			}
			tmpOutput[i][k] = S;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			double v = tmpOutput[i][k];
			if (v > 255.0) v = 255.0;
			if (v < 0.0) v = 0.0;
			m_OutputImage[i][k] = (unsigned char)v;
		}
	}
	free2D_double(tmpInput, m_inH + 8);
	free2D_double(tmpOutput, m_outH);
}


void CImageMFC1Doc::OnHistChartImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_OutputImage, m_outH);
	m_outH = 256;
	m_outW = 256;
	int reSize = m_outH * m_outW;
	unsigned char hist[256]; // 히스토그램 행렬
	int LOW = 0;
	int HIGH = 255;
	unsigned char value = 0;

	//초기화
	for (int i = 0; i < 256; i++) {
		hist[i] = 0;
	}
	//빈도수 조사
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			value = m_InputImage[i][k];
			hist[value]++;
		}
	}
	// 정규화
	unsigned char min = 0;// 최소값 초기화
	unsigned char max = 0; // 최대값 초기화
	unsigned char dif;
	int hNum = 0;
	for (int i = 0; i < 256; i++) {
		if (hist[i] <= min) min = (unsigned char)hist[i];
		if (hist[i] >= max) max = (unsigned char)hist[i];
	}
	dif = max - min;
	unsigned char scaleHist[256];
	// 정규화 된 히스토그램
	for (int i = 0; i < 256; i++) {
		scaleHist[i] = (unsigned char)((hist[i] - min) * HIGH / dif);
	}
	// 정규화된 히스토그램 출력
	unsigned char* OutImage = (unsigned char*)malloc((reSize) * sizeof(unsigned char));
	// 정규화된히스토그램의값은출력배열에검은점(0)으로표현
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < scaleHist[i]; k++) {
			OutImage[m_outW * (m_outH - k - 1) + i] = 0;
		}
	}
	hNum = 0;
	m_OutputImage = malloc2D(m_outH, m_outW);
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_OutputImage[i][k] = OutImage[hNum];
			hNum++;
		}
	}
	free(OutImage);
}


void CImageMFC1Doc::OnHistStchImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;
	int LOW = 0;
	int HIGH = 255;
	unsigned char min = (unsigned char)HIGH;// 최소값 초기화
	unsigned char max = (unsigned char)LOW; // 최대값 초기화

	//입력 영상의 최소값 찾기
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_InputImage[i][k] <= min)
				min = m_InputImage[i][k];
		}
	}
	//입력 영상의 최대값 찾기
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_InputImage[i][k] >= max)
				max = m_InputImage[i][k];
		}
	}
	m_OutputImage = malloc2D(m_outH, m_outW);
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_OutputImage[i][k] = (unsigned char)(m_InputImage[i][k] - min) * HIGH / (max - min);
		}
	}
}


void CImageMFC1Doc::OnHistEqualImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_OutputImage, m_outH);
	m_outH = m_inH;
	m_outW = m_inW;

	int i, j, vmax, vmin;
	double m_HIST[256];
	double m_Sum_of_HIST[256];
	int value;
	unsigned char LOW, HIGH, Temp;
	double SUM = 0.0;

	int size = m_inH * m_inW;
	LOW = 0;
	HIGH = 255;

	// 초기화
	for (int i = 0; i < 256; i++)
		m_HIST[i] = LOW;
	// 빈도수조사
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			value = m_InputImage[i][k];
			m_HIST[value]++;
		}
	}
	// 누적히스토그램생성
	for (int i = 0; i < 256; i++) {
		SUM += m_HIST[i];
		m_Sum_of_HIST[i] = SUM;
	}

	m_OutputImage = malloc2D(m_outH, m_outW);
	// 입력영상을평활화된영상으로출력
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			Temp = m_InputImage[i][k];
			m_OutputImage[i][k] = (unsigned char)(m_Sum_of_HIST[Temp] * HIGH / size);
		}
	}
}


