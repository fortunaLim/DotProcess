
// DotProcessView.h: CDotProcessView 클래스의 인터페이스
//

#pragma once


class CDotProcessView : public CView
{
protected: // serialization에서만 만들어집니다.
	CDotProcessView() noexcept;
	DECLARE_DYNCREATE(CDotProcessView)

// 특성입니다.
public:
	CDotProcessDoc* GetDocument() const;

// 작업입니다.
public:

	int hin;
	int hout;
	int hinV;
	int houtV;

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
	virtual ~CDotProcessView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnConstsum();
	afx_msg void OnConstsum2();
	afx_msg void OnImagesum();
	int m_ViewConst;
	afx_msg void OnSumVarconst();
	afx_msg void OnSlideSum();
	afx_msg void OnConstAnd();
	afx_msg void OnConstOr();
	afx_msg void OnConstXor();
	afx_msg void OnHistoin();
	afx_msg void OnHistoOut();
	afx_msg void OnHistoequal();
	afx_msg void OnStretch();
	int m_ViewThird;
	afx_msg void OnBinary();
	afx_msg void OnOtuz();
	afx_msg void OnNiblack();
	afx_msg void OnHisinVer();
	afx_msg void OnHisoutVer();
	afx_msg void OnLowpass1();
	afx_msg void OnMedian();
	afx_msg void OnPrewitt();
	afx_msg void OnCanny();
	afx_msg void OnGausslap();
	afx_msg void OnSobel();
	afx_msg void OnEmbossing();
	afx_msg void OnRoberts();
	afx_msg void OnLaplacian();
	afx_msg void OnSharpening();
};

#ifndef _DEBUG  // DotProcessView.cpp의 디버그 버전
inline CDotProcessDoc* CDotProcessView::GetDocument() const
   { return reinterpret_cast<CDotProcessDoc*>(m_pDocument); }
#endif

