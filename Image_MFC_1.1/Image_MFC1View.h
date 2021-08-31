
// Image_MFC1View.h: CImageMFC1View 클래스의 인터페이스
//

#pragma once


class CImageMFC1View : public CView
{
protected: // serialization에서만 만들어집니다.
	CImageMFC1View() noexcept;
	DECLARE_DYNCREATE(CImageMFC1View)

// 특성입니다.
public:
	CImageMFC1Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CImageMFC1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEqualImage();
	afx_msg void OnBwValImage();
	afx_msg void OnBw127Image();
	afx_msg void OnBwAvgImage();
	afx_msg void OnLightPmImage();
	afx_msg void OnLightGnImage();
	afx_msg void OnNgtImage();
	afx_msg void OnGammaImage();
	afx_msg void OnParaCapImage();
	afx_msg void OnParaCupImage();
	afx_msg void OnZminNrmlImage();
	afx_msg void OnZminNhImage();
	afx_msg void OnZminYsImage();
	afx_msg void OnZoutImage();
	afx_msg void OnTurnImage();
	afx_msg void OnMoveImage();
	afx_msg void OnMirrorUdImage();
	afx_msg void OnMirrorLrImage();
	afx_msg void OnEmbosImage();
	afx_msg void OnBlrAvgImage();
	afx_msg void OnBlrGausImage();
	afx_msg void OnHpfImage();
	afx_msg void OnLpfImage();
	afx_msg void OnCalcUsaImage();
	afx_msg void OnCalcMnsImage();
	afx_msg void OnRbrtsImage();
	afx_msg void OnPrwImage();
	afx_msg void OnSoblImage();
	afx_msg void OnLaplaImage();
	afx_msg void OnLogImage();
	afx_msg void OnDogImage();
	afx_msg void OnHistChartImage();
	afx_msg void OnHistStchImage();
	afx_msg void OnHistEqualImage();
};

#ifndef _DEBUG  // Image_MFC1View.cpp의 디버그 버전
inline CImageMFC1Doc* CImageMFC1View::GetDocument() const
   { return reinterpret_cast<CImageMFC1Doc*>(m_pDocument); }
#endif

