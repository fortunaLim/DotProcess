#pragma once


// CTHIRD 대화 상자
#include "afxdialogex.h"
#include "MainFrm.h"
#include "DotProcessDoc.h"
#include "DotProcessView.h"

class CTHIRD : public CDialog
{
	DECLARE_DYNAMIC(CTHIRD)

public:
	CTHIRD(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTHIRD();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BINARY};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_Third;
	CSliderCtrl m_binSlider;
	virtual BOOL OnInitDialog();
	afx_msg void OnCustomdrawSliderBin(NMHDR* pNMHDR, LRESULT* pResult);
};
