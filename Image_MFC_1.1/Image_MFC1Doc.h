
// Image_MFC1Doc.h: CImageMFC1Doc 클래스의 인터페이스
//


#pragma once


class CImageMFC1Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CImageMFC1Doc() noexcept;
	DECLARE_DYNCREATE(CImageMFC1Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CImageMFC1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	unsigned char** m_InputImage = NULL;
	unsigned char** m_OutputImage = NULL;
	int m_inH;
	int m_inW;
	int m_outH;
	int m_outW;
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	void free2D(unsigned char** memory, int h);
	unsigned char** malloc2D(int h, int w);
	virtual void OnCloseDocument();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	void OnEqualImage();
	void OnBwValImage();
	double** malloc2D_double(int h, int w);
	void free2D_double(double** memory, int h);
	void OnBw127Image();
	void OnBwAvgImage();
	void OnLightPmImage();
	void OnLightGnImage();
	void OnNgtImage();
	void OnGammaImage();
	void OnParaCapImage();
	void OnParaCupImage();
	void OnZminNrmlImage();
	void OnZminNhImage();
	void OnZminYsImage();
	void OnZoutImage();
	void OnTurnImage();
	void OnMoveImage();
	void OnMirrorUdImage();
	void OnMirrorLrImage();
	void OnEmbosImage();
	void OnBlrAvgImage();
	void OnBlrGausImage();
	void OnHpfImage();
	void OnLpfImage();
	void OnCalcUsaImage();
	void OnCalcMnsImage();
	void OnRbrtsImage();
	void OnPrwImage();
	void OnSoblImage();
	void OnLaplaImage();
	void OnLogImage();
	void OnDogImage();
	void OnHistChartImage();
	void OnHistStchImage();
	void OnHistEqualImage();
	double doubleABS(double x);
};
