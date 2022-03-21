﻿// CConstCntrDlg.cpp: 구현 파일
//

#include "pch.h"
#include "DotProcess.h"
#include "CConstCntrDlg.h"
#include "afxdialogex.h"


#include "ChildFrm.h"
#include "DotProcessDoc.h"
#include "MainFrm.h"
// CConstCntrDlg 대화 상자

IMPLEMENT_DYNAMIC(CConstCntrDlg, CDialog)

CConstCntrDlg::CConstCntrDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_SLIDE, pParent)
	, m_constDisp(0)
{

}

CConstCntrDlg::~CConstCntrDlg()
{
}

void CConstCntrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_constDisp);
	DDV_MinMaxInt(pDX, m_constDisp, 0, 255);
	DDX_Control(pDX, IDC_SLIDER1, m_constSlider);
}


BEGIN_MESSAGE_MAP(CConstCntrDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CConstCntrDlg::OnClickedButton1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CConstCntrDlg::OnCustomdrawSlider1)
END_MESSAGE_MAP()


// CConstCntrDlg 메시지 처리기


void CConstCntrDlg::OnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK(); // 대화상자를 종료
}


BOOL CConstCntrDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO: 여기에 추가 초기화 작업을 추가합니다. m_constSlider.SetRange(0, 255);
	m_constSlider.SetPos(100);
	m_constDisp = m_constSlider.GetPos();
	UpdateData(FALSE);
	return TRUE; // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다
}


void CConstCntrDlg::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다. 
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	ASSERT(pFrame);
	CChildFrame* pChild = (CChildFrame*)pFrame->GetActiveFrame();
	ASSERT(pChild);
	CDotProcessDoc* pDoc = (CDotProcessDoc*)pChild->GetActiveDocument();
	ASSERT(pDoc);
	m_constDisp = m_constSlider.GetPos();
	UpdateData(FALSE);
	pDoc->m_slideSum(m_constDisp);
}
