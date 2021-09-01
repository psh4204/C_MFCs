﻿
// ImagePSHView.h: CImagePSHView 클래스의 인터페이스
//

#pragma once


class CImagePSHView : public CView
{
protected: // serialization에서만 만들어집니다.
	CImagePSHView() noexcept;
	DECLARE_DYNCREATE(CImagePSHView)

// 특성입니다.
public:
	CImagePSHDoc* GetDocument() const;

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
	virtual ~CImagePSHView();
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
	afx_msg void OnBw127Image();
	afx_msg void OnBwInputImage();
	afx_msg void OnGrayImage();
	afx_msg void OnNgtvImage();
	afx_msg void OnLightPmImage();
	afx_msg void OnLightMdImage();
};

#ifndef _DEBUG  // ImagePSHView.cpp의 디버그 버전
inline CImagePSHDoc* CImagePSHView::GetDocument() const
   { return reinterpret_cast<CImagePSHDoc*>(m_pDocument); }
#endif

