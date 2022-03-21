
// DotProcessDoc.cpp: CDotProcessDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "DotProcess.h"
#endif

#include "DotProcessDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDotProcessDoc

IMPLEMENT_DYNCREATE(CDotProcessDoc, CDocument)

BEGIN_MESSAGE_MAP(CDotProcessDoc, CDocument)
	
END_MESSAGE_MAP()


// CDotProcessDoc 생성/소멸

CDotProcessDoc::CDotProcessDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CDotProcessDoc::~CDotProcessDoc()
{
}

BOOL CDotProcessDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CDotProcessDoc serialization

void CDotProcessDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		ar.Write(m_ResultImg, 256 * 256);
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		CFile* fp = ar.GetFile();

		if (fp->GetLength() != 256 * 256) { // 에러 메시지 출력
			AfxMessageBox(_T("256 * 256 이미지가 아님!"));
			return;
		}
		ar.Read(m_OpenImg, fp->GetLength());
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CDotProcessDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CDotProcessDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CDotProcessDoc::SetSearchContent(const CString& value)
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

// CDotProcessDoc 진단

#ifdef _DEBUG
void CDotProcessDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDotProcessDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDotProcessDoc 명령


void CDotProcessDoc::DoubleLoad()
{
	// TODO: 여기에 구현 코드 추가.

	// 첫 번째 파일 열기
	CFileDialog dlg1(TRUE);
	AfxMessageBox(_T("Select First Image"));
	if (dlg1.DoModal() == IDOK) {
		CFile file;
		file.Open(dlg1.GetPathName(), CFile::modeRead); // 파일 열기
		file.Read(m_ImageBuf1, 256 * 256); // 파일 읽기
		file.Close();
	}
	// 두 번째 파일 열기
	CFileDialog dlg2(TRUE);
	AfxMessageBox(_T("Select Second Image"));
	if (dlg2.DoModal() == IDOK) {
		CFile file;
		file.Open(dlg2.GetPathName(), CFile::modeRead); // 파일 열기
		file.Read(m_ImageBuf2, sizeof(m_ImageBuf2)); // 파일 읽기
		file.Close();
	}
}


void CDotProcessDoc::m_slideSum(int slideconst)
{
	// TODO: 여기에 구현 코드 추가.
	int x, y, data;
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			data = m_OpenImg[y][x] + slideconst;
			if (data > 255) m_ResultImg[y][x] = 255;
			else m_ResultImg[y][x] = data;
		}
	}
	UpdateAllViews(FALSE); // 화면 출력 갱신
}


void CDotProcessDoc::Histoin()
{
	// TODO: 여기에 구현 코드 추가.
	int x, y, d;
	for (y = 0; y < 256; y++) histoin[y] = 0;
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			d = (int)m_OpenImg[y][x];
			histoin[d]++;
		}
	}
}





void CDotProcessDoc::HistoOut()
{
	// TODO: 여기에 구현 코드 추가.

	int x, y, d;
	for (y = 0; y < 256; y++) histoout[y] = 0;
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			d = (int)m_ResultImg[y][x];
			histoout[d]++;
		}
	}
}


void CDotProcessDoc::Histoequal()
{
	// TODO: 여기에 구현 코드 추가.
	int x, y, d, nn;
	int k = 0, sum = 0, total_pix = 0;
	int hist[256];
	int sum_hist[256];
	
	for (x = 0; x < 256; x++) {
		hist[x] = 0;
		sum_hist[x] = 0;
	}
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			k = m_OpenImg[y][x];
			hist[k]++;
		}
	}
	for (x = 0; x < 256; x++) {
		sum = sum + hist[x];
		sum_hist[x] = sum;
	}
	total_pix = 256 * 256;
	nn = total_pix / 256;
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			k = m_OpenImg[y][x];
			if (sum_hist[k] == 0) d = 0;
			else d = (sum_hist[k] - 1) / nn;
			m_ResultImg[y][x] = (unsigned char)d;
		}
	}
}



void CDotProcessDoc::Stretch()
{
	// TODO: 여기에 구현 코드 추가.
	int x, y, d;
	int hist[256];
	unsigned char LUT[256];
	int low, high;
	float scale;
	for (x = 0; x < 256; x++) hist[x] = 0;

	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			d = m_OpenImg[y][x];
			hist[d]++;
		}
	}
	// 히스토그램에서 가장 낮은 농도값 추출
	for (x = 0; x < 256; x++) {
		if (hist[x] != 0) {
			low = x;
			break;
		}
	}
	// 히스토그램에서 가장 높은 농도값 추출
	for (x = 255; x >= 0; x--) {
		if (hist[x] != 0) {
			high = x;
			break;
		}
	}
	// 룩업테이블 작성
	for (x = 0; x < low; x++) LUT[x] = 0;

	for (x = high; x < 256; x++) LUT[x] = 255;

	scale = 255.0 / (float)(high - low);

	for (x = low; x < high; x++) {
		LUT[x] = (unsigned char)((x - low) * scale);
	}

	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			d = m_OpenImg[y][x];
			m_ResultImg[y][x] = LUT[d];
		}
	}
}


void CDotProcessDoc::m_slideBinary(int slideBin)
{
	// TODO: 여기에 구현 코드 추가.
}


void CDotProcessDoc::AutoBin1()
{
	// TODO: 여기에 구현 코드 추가.
	int x, y, i, t;
	float prob[256];
	for (i = 0; i < 256; i++) {
		histoin[i] = 0;
		prob[i] = 0.0f;
	}
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			t = m_OpenImg[y][x];
			histoin[t]++;
		}
	}
	for (i = 0; i < 256; i++) prob[i] = (float)histoin[i] / 65536.0F;
	float wsv_min = 1000000.0f;
	float wsv_u1, wsv_u2, wsv_s1, wsv_s2;
	int wsv_t;
	for (t = 0; t < 256; t++) {
		// q1, q2 계산 
		float q1 = 0.0f, q2 = 0.0f;
		for (i = 0; i < t; i++) q1 += prob[i];
		for (i = t; i < 256; i++) q2 += prob[i];
		if (q1 == 0 || q2 == 0) continue;
		// u1, u2 계산 
		float u1 = 0.0f, u2 = 0.0f;
		for (i = 0; i < t; i++) u1 += i * prob[i];
		u1 /= q1;
		for (i = t; i < 256; i++) u2 += i * prob[i];
		u2 /= q2;
		// s1, s2 계산 
		float s1 = 0.0f, s2 = 0.0f;
		for (i = 0; i < t; i++) s1 += (i - u1) * (i - u1) * prob[i];
		s1 /= q1;
		for (i = t; i < 256; i++) s2 += (i - u2) * (i - u2) * prob[i];
		s2 /= q2;
		float wsv = q1 * s1 + q2 * s2;
		if (wsv < wsv_min) {
			wsv_min = wsv;
			wsv_t = t;
			wsv_u1 = u1;
			wsv_u2 = u2;
			wsv_s1 = s1;
			wsv_s2 = s2;
		}
	}
	// Display the result values
	CString strTemp;
	strTemp.Format(_T("Optimal Threshold: %3d\nMean: %7.3f, % 7.3f\nVariance: % 7.3f, % 7.3f"), wsv_t,wsv_u1,wsv_u2,wsv_s1,wsv_s2);
		AfxMessageBox(strTemp);
	// 2치화
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			if (m_OpenImg[y][x] < wsv_t) m_ResultImg[y][x] = 0;
			else m_ResultImg[y][x] = 255;
		}
	}
}

void CDotProcessDoc::AutoBin2()
{
	// TODO: 여기에 구현 코드 추가.
	register int x, y, xx, yy;
	float mean, vari, thres;
	int W = 20, ith;
	CString strTemp;
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			float gsum = 0.0f;
			float ssum = 0.0f;
			int count = 0;
			for (yy = y - W; yy <= y + W; yy++) {
				if (yy < 0 || yy >= 256) continue;
				for (xx = x - W; xx <= x + W; xx++) {
					if (xx < 0 || xx >= 256) continue;
					gsum += (float)m_OpenImg[yy][xx];
					ssum += (float)(m_OpenImg[yy][xx] * m_OpenImg[yy][xx]);
					count++;
				}
			}
			mean = gsum / (float)count;
			vari = ssum / (float)count - mean * mean;

			if (vari < 0) vari = 0.0f;
			thres = mean * (1.0f - 0.02f * (1.0F - (float)sqrt(vari) / 128.0F));
			ith = (int)thres;
			if (m_OpenImg[y][x] < ith) m_ResultImg[y][x] = 0;
			else m_ResultImg[y][x] = 255;
		}
	}
}


void CDotProcessDoc::HistoinVer()
{
	// TODO: 여기에 구현 코드 추가.

		// TODO: 여기에 구현 코드 추가.
	int x, y, d;
	for (y = 0; y < 256; y++) histoinV[y] = 0;
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			d = (int)m_OpenImg[y][x];
			histoinV[d]++;
		}
	}
}


void CDotProcessDoc::HistoOutVer()
{
	// TODO: 여기에 구현 코드 추가.

	int x, y, d;
	for (y = 0; y < 256; y++) histooutV[y] = 0;
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			d = (int)m_ResultImg[y][x];
			histooutV[d]++;
		}
	}
}
