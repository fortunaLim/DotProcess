// CTHIRD.cpp: 구현 파일
//

#include "pch.h"
#include "DotProcess.h"
#include "CTHIRD.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "DotProcessDoc.h"
#include "DotProcessView.h"

#include "MainFrm.h" // 추가
#include "ChildFrm.h" // 추가


// CTHIRD 대화 상자

IMPLEMENT_DYNAMIC(CTHIRD, CDialog)

CTHIRD::CTHIRD(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_BINARY, pParent)
	, m_Third(0)
{

}

CTHIRD::~CTHIRD()
{
}

void CTHIRD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_THIRD, m_Third);
	DDV_MinMaxInt(pDX, m_Third, 0, 255);
	DDX_Control(pDX, IDC_SLIDER_BIN, m_binSlider);
}


BEGIN_MESSAGE_MAP(CTHIRD, CDialog)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_BIN, &CTHIRD::OnCustomdrawSliderBin)
END_MESSAGE_MAP()


// CTHIRD 메시지 처리기


BOOL CTHIRD::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_binSlider.SetRange(0, 255);
	m_binSlider.SetPos(100);
	m_Third = m_binSlider.GetPos();
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CTHIRD::OnCustomdrawSliderBin(NMHDR* pNMHDR, LRESULT* pResult)
{
	/*
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	*/
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다. 
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	ASSERT(pFrame);
	CChildFrame* pChild = (CChildFrame*)pFrame->GetActiveFrame();
	ASSERT(pChild);
	CDotProcessDoc* pDoc = (CDotProcessDoc*)pChild->GetActiveDocument();
	ASSERT(pDoc);
	m_Third = m_binSlider.GetPos();
	UpdateData(FALSE);
	pDoc->m_slideBinary(m_Third);
}
