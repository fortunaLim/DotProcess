
// DotProcessView.cpp: CDotProcessView 클래스의 구현
//


#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "DotProcess.h"
#endif

#include "DotProcessDoc.h"
#include "DotProcessView.h"

#include "CCONST.h"
#include "CConstCntrDlg.h"
#include "CTHIRD.h"
#include "iostream"
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDotProcessView

IMPLEMENT_DYNCREATE(CDotProcessView, CView)

BEGIN_MESSAGE_MAP(CDotProcessView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDotProcessView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_CONSTSUM2, &CDotProcessView::OnConstsum2)
	ON_COMMAND(ID_IMAGESUM, &CDotProcessView::OnImagesum)
	ON_COMMAND(ID_SUM_VARCONST, &CDotProcessView::OnSumVarconst)
	ON_COMMAND(ID_SLIDE_SUM, &CDotProcessView::OnSlideSum)
	ON_COMMAND(ID_CONST_AND, &CDotProcessView::OnConstAnd)
	ON_COMMAND(ID_CONST_OR, &CDotProcessView::OnConstOr)
	ON_COMMAND(ID_CONST_XOR, &CDotProcessView::OnConstXor)
	ON_COMMAND(ID_HISTOIN, &CDotProcessView::OnHistoin)
	ON_COMMAND(ID_HISTO_OUT, &CDotProcessView::OnHistoOut)
	ON_COMMAND(ID_HISTOEQUAL, &CDotProcessView::OnHistoequal)
	ON_COMMAND(ID_STRETCH, &CDotProcessView::OnStretch)
	ON_COMMAND(ID_BINARY, &CDotProcessView::OnBinary)
	ON_COMMAND(ID_Otuz, &CDotProcessView::OnOtuz)
	ON_COMMAND(ID_Niblack, &CDotProcessView::OnNiblack)
	ON_COMMAND(ID_HISIN_VER, &CDotProcessView::OnHisinVer)
	ON_COMMAND(ID_HISOUT_VER, &CDotProcessView::OnHisoutVer)
	ON_COMMAND(ID_LOWPASS1, &CDotProcessView::OnLowpass1)
	ON_COMMAND(ID_MEDIAN, &CDotProcessView::OnMedian)
	ON_COMMAND(ID_PREWITT, &CDotProcessView::OnPrewitt)
	ON_COMMAND(ID_CANNY, &CDotProcessView::OnCanny)
	ON_COMMAND(ID_GaussLap, &CDotProcessView::OnGausslap)
	ON_COMMAND(ID_Sobel, &CDotProcessView::OnSobel)
	ON_COMMAND(ID_Embossing, &CDotProcessView::OnEmbossing)
	ON_COMMAND(ID_Roberts, &CDotProcessView::OnRoberts)
	ON_COMMAND(ID_Laplacian, &CDotProcessView::OnLaplacian)
	ON_COMMAND(ID_Sharpening, &CDotProcessView::OnSharpening)
END_MESSAGE_MAP()

// CDotProcessView 생성/소멸

CDotProcessView::CDotProcessView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CDotProcessView::~CDotProcessView()
{
}

BOOL CDotProcessView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CDotProcessView 그리기

void CDotProcessView::OnDraw(CDC* pDC)
{
	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	int x, y;
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			pDC->SetPixel(x, y, RGB(pDoc->m_OpenImg[y][x],
				pDoc->m_OpenImg[y][x], pDoc->m_OpenImg[y][x]));
		}
	}

	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			pDC->SetPixel(x + 600, y, RGB(pDoc->m_ResultImg[y][x],
				pDoc->m_ResultImg[y][x], pDoc->m_ResultImg[y][x]));
		}
	}

	if (hin == 1) {
		pDC->MoveTo(0, 260);
		pDC->LineTo(0, 350); // Y축
		pDC->MoveTo(0, 350);
		pDC->LineTo(257, 350); // X축
		for (x = 0; x < 256; x++) {
			y = pDoc->histoin[x] / 20;
			if (y > 90) y = 260;
			else y = 350 - y;
			pDC->MoveTo(x, 350);
			pDC->LineTo(x, y);
		}
	}

	if (hout == 1) {
		// 출력 히스토그램 영역 클리어
		/*
		for (y = 256; y < 360; y++) {
			for (x = 300; x < 560; x++) {
				pDC->SetPixel(x, y, RGB(255, 255, 255));
			}
		}
		*/
		// 축 그리기
		pDC->MoveTo(600, 260);
		pDC->LineTo(600, 350); // Y축
		pDC->MoveTo(600, 350);
		pDC->LineTo(857, 350); // X축
		// 분포도 그리기
		for (x = 0; x < 256; x++) {
			y = pDoc->histoout[x] / 20;
			if (y > 90) y = 260;
			else y = 350 - y;
			pDC->MoveTo(x + 600, 350);
			pDC->LineTo(x + 600, y);
		}
	}
	///////////////////////////////////////////////////////
	if (hinV == 1) {
		pDC->MoveTo(260, 0);
		pDC->LineTo(260+350-260, 0); // Y축
		pDC->MoveTo(260, 0);
		pDC->LineTo(260, 257); // X축
		for (x = 0; x < 256; x++) {
			y = pDoc->histoinV[x] / 20;
			//if (y > 90) y = 260;
			//else y = 350 - y;
			pDC->MoveTo(260, x);
			pDC->LineTo(y+260, x);
		}
	}

	if (houtV == 1) {
		// 출력 히스토그램 영역 클리어
		for (y = 256; y < 360; y++) {
			for (x = 300; x < 560; x++) {
				pDC->SetPixel(x, y, RGB(255, 255, 255));
			}
		}
		
		pDC->MoveTo(260+600, 0);
		pDC->LineTo(260+300+300 + 350 - 260, 0); // Y축
		pDC->MoveTo(260+600, 0);
		pDC->LineTo(260+600, 257); // X축
		for (x = 0; x < 256; x++) {
			y = pDoc->histooutV[x] / 20;
			//if (y > 90) y = 260;
			//else y = 350 - y;
			pDC->MoveTo(260+600, x);
			pDC->LineTo(y + 260+600, x);
		}

	}
}


// CDotProcessView 인쇄


void CDotProcessView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDotProcessView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CDotProcessView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CDotProcessView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CDotProcessView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDotProcessView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDotProcessView 진단

#ifdef _DEBUG
void CDotProcessView::AssertValid() const
{
	CView::AssertValid();
}

void CDotProcessView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDotProcessDoc* CDotProcessView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDotProcessDoc)));
	return (CDotProcessDoc*)m_pDocument;
}
#endif //_DEBUG


// CDotProcessView 메시지 처리기




void CDotProcessView::OnConstsum2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int x, y, data;
	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			data = pDoc->m_OpenImg[y][x] + 100;
			if (data > 255) pDoc->m_ResultImg[y][x] = 255;
			else pDoc->m_ResultImg[y][x] = data;
		}
	}
	Invalidate(FALSE); // 화면 갱신
}


void CDotProcessView::OnImagesum()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int x, y, data;
	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->DoubleLoad();
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			data = pDoc->m_ImageBuf1[y][x] + pDoc->m_ImageBuf2[y][x];
			// Saturation Operating
			// 256이면 오버플로우 생겨서 255로 세츄레이션
			if (data > 255) pDoc->m_ResultImg[y][x] = 255;
			else pDoc->m_ResultImg[y][x] = data;
			// Wrap Operating
			pDoc->m_OpenImg[y][x] = data;
		}
	}
	Invalidate(FALSE);// 화면 갱신
}


void CDotProcessView::OnSumVarconst()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int x, y, data;
	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CCONST* pCONST = new CCONST;
	if (pCONST->DoModal() == IDOK) {
		m_ViewConst = pCONST->m_Const;
	}
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			data = pDoc->m_OpenImg[y][x] + m_ViewConst;
				// Saturation Operating
				if (data > 255) pDoc->m_ResultImg[y][x] = 255;
				else pDoc->m_ResultImg[y][x] = data;
		}
	}
	Invalidate(FALSE); // 화면 갱신
}


void CDotProcessView::OnSlideSum()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	// TODO: 여기에 명령 처리기 코드를 추가합니다. 
	CConstCntrDlg psumCntrDlg; // 슬라이드 컨트롤 클래스 변수 선언
	psumCntrDlg.DoModal(); // 슬라이드 컨트롤 박스 호
}


void CDotProcessView::OnConstAnd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int x, y, data;
	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->DoubleLoad();
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			data = pDoc->m_ImageBuf1[y][x] & pDoc->m_ImageBuf2[y][x];
			// Saturation Operating
			if (data > 255) pDoc->m_ResultImg[y][x] = 255;
			else pDoc->m_ResultImg[y][x] = data;
			// Wrap Operating
			pDoc->m_OpenImg[y][x] = data;
		}
	}
	Invalidate(FALSE);// 화면 갱신

}


void CDotProcessView::OnConstOr()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int x, y, data;
	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->DoubleLoad();
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			data = pDoc->m_ImageBuf1[y][x] | pDoc->m_ImageBuf2[y][x];
			// Saturation Operating
			if (data > 255) pDoc->m_ResultImg[y][x] = 255;
			else pDoc->m_ResultImg[y][x] = data;
			// Wrap Operating
			pDoc->m_OpenImg[y][x] = data;
		}
	}
	Invalidate(FALSE);// 화면 갱신
}


void CDotProcessView::OnConstXor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int x, y, data;
	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->DoubleLoad();
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			data = pDoc->m_ImageBuf1[y][x] ^ pDoc->m_ImageBuf2[y][x];
			// Saturation Operating
			if (data > 255) pDoc->m_ResultImg[y][x] = 255;
			else pDoc->m_ResultImg[y][x] = data;
			// Wrap Operating
			pDoc->m_OpenImg[y][x] = data;
		}
	}
	Invalidate(FALSE);// 화면 갱신
}


void CDotProcessView::OnHistoin()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->Histoin();
	hin = 1; // 히스토그램 그래픽 표시 플래그
	Invalidate(FALSE);
}

void CDotProcessView::OnHistoOut()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->HistoOut();
	hout = 1; // 히스토그램 그래픽 표시 플래그
	Invalidate(FALSE);
}

void CDotProcessView::OnHistoequal()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다. 
	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->Histoequal();
	Invalidate(FALSE);
}


void CDotProcessView::OnStretch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	// TODO: 여기에 명령 처리기 코드를 추가합니다. 
	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->Stretch();
	Invalidate(FALSE);
}


void CDotProcessView::OnBinary()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int x, y;
	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CTHIRD* pTHRED = new CTHIRD;
	if (pTHRED->DoModal() == IDOK) {
		m_ViewThird = pTHRED->m_Third;
	}
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			if (pDoc->m_OpenImg[y][x] > m_ViewThird)
				pDoc->m_ResultImg[y][x] = 255;
			else pDoc->m_ResultImg[y][x] = 0;
		}
	}
	Invalidate(FALSE); // 화면 갱신
}


void CDotProcessView::OnOtuz()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->AutoBin1();
	Invalidate(FALSE);

}


void CDotProcessView::OnNiblack()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->AutoBin2();
	Invalidate(FALSE);
}


void CDotProcessView::OnHisinVer()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->HistoinVer();
	hinV = 1; // 히스토그램 그래픽 표시 플래그
	Invalidate(FALSE);
}


void CDotProcessView::OnHisoutVer()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->HistoOutVer();
	houtV = 1; // 히스토그램 그래픽 표시 플래그
	Invalidate(FALSE);
}


void CDotProcessView::OnLowpass1(void)
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	int x, y, p, q, div;
	int sum, filter1[3][3] = { {1, 1, 1}, {1, 1, 1}, {1, 1, 1} };
	div = 0;

	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	for (q = 0; q <= 2; q++) {
		for (p = 0; p <= 2; p++) div = div + filter1[q][p];
	}
	for (y = 1; y < 255; y++) {
		for (x = 1; x < 255; x++) {
			sum = 0;
			for (q = 0; q <= 2; q++) {
				for (p = 0; p <= 2; p++) {
					sum += filter1[q][p] * pDoc->m_OpenImg[y + q - 1][x + p - 1];
				}
			}
			pDoc->m_ResultImg[y][x] = sum / div;
		}
	}

	Invalidate(FALSE);
}


void CDotProcessView::OnMedian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	int x, y, p, q, div;
	int sum, filter1[3][3] = { {1, 1, 1}, {1, 1, 1}, {1, 1, 1} };
	int mid;
	int midd[9];
	int cc;
	div = 0;

	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	for (q = 0; q <= 2; q++) {
		for (p = 0; p <= 2; p++) div = div + filter1[q][p];
	}

	
	

	for (y = 1; y < 255; y++) {
		for (x = 1; x < 255; x++) {
			
			for (int i = 0; i < 9; i++)
			{
				midd[i] = 0;
			}
			int i = 0;
			for (q = 0; q <= 2; q++) {
				
				for (p = 0; p <= 2; p++) {
					midd[i] =  pDoc->m_OpenImg[y + q - 1][x + p - 1];
					i++;
				}
			}
			int t,tt = 0;
			for (t = 0; t < 9; t++) {
				for (int tt = 1; tt < 9; tt++)
				{
					if (midd[tt - 1] > midd[tt])
					{

						int tmp;

						tmp = midd[tt-1];
						midd[tt-1] = midd[tt];
						midd[tt] = midd[tt-1];
					}
					
				}

			}
	
			



			pDoc->m_ResultImg[y][x] = (midd[5]);
		}
	}

	Invalidate(FALSE);
}

void CDotProcessView::OnPrewitt()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.


	int x, y, p, q, div;
	//int sum, filter1[3][3] = { {-1, 0, 1}, {-1, 0, 1}, {-1, 0, 1} };
	int sum, filter1[3][3] = { {-1, -1, -1}, {0, 0, 0}, {1, 1, 1} };

	div = 0;

	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	for (q = 0; q <= 2; q++) {
		//for (p = 0; p <= 2; p++) div = div + filter1[q][p];
	}
	for (y = 1; y < 255; y++) {
		for (x = 1; x < 255; x++) {
			sum = 0;
			for (q = 0; q <= 2; q++) {
				for (p = 0; p <= 2; p++) {
					sum += filter1[q][p] * pDoc->m_OpenImg[y + q - 1][x + p - 1];
				}
			}

			sum = abs(sum);
			if(sum > 255) pDoc->m_ResultImg[y][x] = 255;
			else pDoc->m_ResultImg[y][x] = sum;
		}
	}

	Invalidate(FALSE);
}


void CDotProcessView::OnCanny()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	int x, y, p, q, div;
	int sum, Gaussian[3][3] = { {1, 2, 1}, {2, 4, 2}, {1, 2, 1} };
	int sx, ft_x[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
	int sy, ft_y[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };

	div = 0;

	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	for (q = 0; q <= 2; q++) {
		for (p = 0; p <= 2; p++) div = div + Gaussian[q][p];
	}
	// 평활화 처리
	for (y = 1; y < 255; y++) {
		for (x = 1; x < 255; x++) {
			sum = 0;
			for (q = 0; q <= 2; q++) {
				for (p = 0; p <= 2; p++) {
					sum += Gaussian[q][p] * pDoc->m_OpenImg[y + q - 1][x + p - 1];
				}
			}
			pDoc->m_ImageBuf1[y][x] = sum / div;
		}
	}

	for (y = 1; y < 255; y++) { // Sobol 처리
		for (x = 1; x < 255; x++) {
			sx = 0;
			for (q = 0; q <= 2; q++) {
				for (p = 0; p <= 2; p++)
					sx += ft_x[q][p] * pDoc->m_ImageBuf1[y + q - 1][x + p - 1];
			}
			sy = 0;
			for (q = 0; q <= 2; q++) {
				for (p = 0; p <= 2; p++)
					sy += ft_y[q][p] * pDoc->m_ImageBuf1[y + q - 1][x + p - 1];
			}
			sy = abs(sx) + abs(sy);
			if (sy > 255) sy = 255;
			pDoc->m_ResultImg[y][x] = sy;
		}
	}


	Invalidate(FALSE);

}


void CDotProcessView::OnGausslap()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int x, y, p, q;
	int sum, filter[9][9] = {
	{ 0, 0, 0, 0, -1, 0, 0, 0, 0},
	{ 0, 0, -1, -2, -2, -2, -1, 0, 0},
	{ 0, -1, -2, -2, -1, -2, -2, -1, 0},
	{ 0, -2, -2, 4, 8, 4, -2, -2, 0},
	{-1, -2, -1, 8, 16, 8, -1, -2, -1},
	{ 0, -2, -2, 4, 8, 4, -2, -2, 0},
	{ 0, -1, -2, -2, -1, -2, -2, -1, 0},
	{ 0, 0, -1, -2, -2, -2, -1, 0, 0},
	{ 0, 0, 0, 0, -1, 0, 0, 0, 0} };

	for (y = 4; y < 252; y++) {
		for (x = 4; x < 252; x++) {
			sum = 0;
			for (q = 0; q < 9; q++) {
				for (p = 0; p < 9; p++) {
					sum += filter[q][p] * pDoc->m_OpenImg[y + q - 4][x + p - 4];
				}
			}
			if (sum > 0) pDoc->m_ImageBuf1[y][x] = 255; // +
			else if (sum < 0) pDoc->m_ImageBuf1[y][x] = 128; // -
			else pDoc->m_ImageBuf1[y][x] = 0; // 0
		}
	}
	for (y = 4; y < 252; y++) {
		for (x = 5; x < 251; x++) {
			if (pDoc->m_ImageBuf1[y][x] != 255) { // +가 아니면
				pDoc->m_ResultImg[y][x] = 0;
				continue;
			}
			if (pDoc->m_ImageBuf1[y][x + 1] == 128 || // 좌 또는 우 -이면
				pDoc->m_ImageBuf1[y][x - 1] == 128) pDoc->m_ResultImg[y][x] = 255;
			else pDoc->m_ResultImg[y][x] = 0;
		}
	}
	for (x = 4; x < 252; x++) {
		for (y = 5; y < 251; y++) {
			if (pDoc->m_ImageBuf1[y][x] != 255) continue; // +가 아니면
			if (pDoc->m_ImageBuf1[y - 1][x] == 128 || // 위 또는 아래가 -이면
				pDoc->m_ImageBuf1[y + 1][x] == 128) pDoc->m_ResultImg[y][x] = 255;
		}
	}
}


void CDotProcessView::OnSobel()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	int x, y, p, q, div;
	int sum, Gaussian[3][3] = { {1, 2, 1}, {2, 4, 2}, {1, 2, 1} };
	int sx, ft_x[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
	int sy, ft_y[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };
	int SS;
	div = 0;

	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	for (q = 0; q <= 2; q++) {
	//	for (p = 0; p <= 2; p++) div = div + Gaussian[q][p];
	}

	// 평활화 처리
	/*
	for (y = 1; y < 255; y++) {
		for (x = 1; x < 255; x++) {
			sum = 0;
			for (q = 0; q <= 2; q++) {
				for (p = 0; p <= 2; p++) {
					sum += Gaussian[q][p] * pDoc->m_OpenImg[y + q - 1][x + p - 1];
				}
			}
			pDoc->m_ImageBuf1[y][x] = sum / div;
		}
	}
	*/
	for (y = 1; y < 255; y++) { // Sobol 처리
		for (x = 1; x < 255; x++) {
			sx = 0;
			for (q = 0; q <= 2; q++) {
				for (p = 0; p <= 2; p++)
					sx += ft_x[q][p] * pDoc->m_OpenImg[y + q - 1][x + p - 1];
			}
			sy = 0;
			for (q = 0; q <= 2; q++) {
				for (p = 0; p <= 2; p++)
					sy += ft_y[q][p] * pDoc->m_OpenImg[y + q - 1][x + p - 1];
			}

			SS = abs(sx) + abs(sy);
			if (SS > 255) SS = 255;
			pDoc->m_ResultImg[y][x] = SS;
		}
	}


	Invalidate(FALSE);

}


void CDotProcessView::OnEmbossing()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	int x, y, p, q, div;
	//int sum, filter1[3][3] = { {-1, 0, 1}, {-1, 0, 1}, {-1, 0, 1} };
	int sum, filter1[3][3] = { {-1, 0, 0}, {0, 0, 0}, {0, 0, 1} };

	div = 0;

	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	for (q = 0; q <= 2; q++) {
		//for (p = 0; p <= 2; p++) div = div + filter1[q][p];
	}
	for (y = 1; y < 255; y++) {
		for (x = 1; x < 255; x++) {
			sum = 0;
			for (q = 0; q <= 2; q++) {
				for (p = 0; p <= 2; p++) {
					sum += filter1[q][p] * pDoc->m_OpenImg[y + q - 1][x + p - 1];
				}
			}

			sum += 128;
			if (sum > 255) pDoc->m_ResultImg[y][x] = 255;
			else pDoc->m_ResultImg[y][x] = sum;
		}
	}

	Invalidate(FALSE);
}


void CDotProcessView::OnRoberts()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.


	int x, y, p, q, div;
	int sum, Gaussian[3][3] = { {1, 2, 1}, {2, 4, 2}, {1, 2, 1} };
	int Rx, ft_x[3][3] = { {0, 0, -1}, {0, 1, 0}, {0, 0, 0} };
	int Ry, ft_y[3][3] = { {-1, 0, 0}, {0, 1, 0}, {0, 0, 0} };
	int RR;
	div = 0;

	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	for (q = 0; q <= 2; q++) {
		//	for (p = 0; p <= 2; p++) div = div + Gaussian[q][p];
	}

	// 평활화 처리
	/*
	for (y = 1; y < 255; y++) {
		for (x = 1; x < 255; x++) {
			sum = 0;
			for (q = 0; q <= 2; q++) {
				for (p = 0; p <= 2; p++) {
					sum += Gaussian[q][p] * pDoc->m_OpenImg[y + q - 1][x + p - 1];
				}
			}
			pDoc->m_ImageBuf1[y][x] = sum / div;
		}
	}
	*/
	for (y = 1; y < 255; y++) { // Sobol 처리
		for (x = 1; x < 255; x++) {
			Rx = 0;
			for (q = 0; q <= 2; q++) {
				for (p = 0; p <= 2; p++)
					Rx += ft_x[q][p] * pDoc->m_OpenImg[y + q - 1][x + p - 1];
			}
			Ry = 0;
			for (q = 0; q <= 2; q++) {
				for (p = 0; p <= 2; p++)
					Ry += ft_y[q][p] * pDoc->m_OpenImg[y + q - 1][x + p - 1];
			}

			RR = abs(Rx) + abs(Ry);
			if (RR > 255) RR = 255;
			pDoc->m_ResultImg[y][x] = RR;
		}
	}


	Invalidate(FALSE);

}


void CDotProcessView::OnLaplacian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.


	int x, y, p, q, div;
	int sum, Gaussian[3][3] = { {1, 2, 1}, {2, 4, 2}, {1, 2, 1} };
	int Rx, ft_x[3][3] = { {0, 1, 0}, {1, -4, 1}, {0, 1, 0} };
	int Ry, ft_y[3][3] = { {1, 1, 1}, {1, -8, 1}, {1, 1, 1} };
	int RR;
	div = 0;

	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	for (q = 0; q <= 2; q++) {
		//	for (p = 0; p <= 2; p++) div = div + Gaussian[q][p];
	}

	// 평활화 처리
	/*
	for (y = 1; y < 255; y++) {
		for (x = 1; x < 255; x++) {
			sum = 0;
			for (q = 0; q <= 2; q++) {
				for (p = 0; p <= 2; p++) {
					sum += Gaussian[q][p] * pDoc->m_OpenImg[y + q - 1][x + p - 1];
				}
			}
			pDoc->m_ImageBuf1[y][x] = sum / div;
		}
	}
	*/
	for (y = 1; y < 255; y++) { // Sobol 처리
		for (x = 1; x < 255; x++) {
			Rx = 0;
			for (q = 0; q <= 2; q++) {
				for (p = 0; p <= 2; p++)
					Rx += ft_x[q][p] * pDoc->m_OpenImg[y + q - 1][x + p - 1];
			}
			Ry = 0;
			for (q = 0; q <= 2; q++) {
				for (p = 0; p <= 2; p++)
					Ry += ft_y[q][p] * pDoc->m_OpenImg[y + q - 1][x + p - 1];
			}

			RR = abs(Rx) + abs(Ry);
			if (RR > 255) RR = 255;
			pDoc->m_ResultImg[y][x] = RR;
		}
	}


	Invalidate(FALSE);
}


void CDotProcessView::OnSharpening()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.


	int x, y, p, q, div;
	int sum, Gaussian[3][3] = { {1, 2, 1}, {2, 4, 2}, {1, 2, 1} };
	int Rx, ft_x[3][3] = { {0, -1, 0}, {-1, 4, 1}, {0, 1, 0} };
	int Ry, ft_y[3][3] = { {0, 0, 0}, {0, 1, 0}, {0, 0, 0} };
	int RR;
	div = 0;

	CDotProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	for (q = 0; q <= 2; q++) {
		//	for (p = 0; p <= 2; p++) div = div + Gaussian[q][p];
	}

	// 평활화 처리
	/*
	for (y = 1; y < 255; y++) {
		for (x = 1; x < 255; x++) {
			sum = 0;
			for (q = 0; q <= 2; q++) {
				for (p = 0; p <= 2; p++) {
					sum += Gaussian[q][p] * pDoc->m_OpenImg[y + q - 1][x + p - 1];
				}
			}
			pDoc->m_ImageBuf1[y][x] = sum / div;
		}
	}
	*/
	for (y = 1; y < 255; y++) { // Sobol 처리
		for (x = 1; x < 255; x++) {
			Rx = 0;
			for (q = 0; q <= 2; q++) {
				for (p = 0; p <= 2; p++)
					Rx += ft_y[q][p] * pDoc->m_OpenImg[y + q - 1][x + p - 1];
			}
			Ry = 0;
			for (q = 0; q <= 2; q++) {
				for (p = 0; p <= 2; p++)
					Ry += ft_y[q][p] * pDoc->m_OpenImg[y + q - 1][x + p - 1];
			}

			RR = (Rx + Ry)/2;
			if (RR > 255) RR = 255;
			pDoc->m_ResultImg[y][x] = RR;
		}
	}


	Invalidate(FALSE);
}
