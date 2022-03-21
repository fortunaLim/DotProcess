
// DotProcessDoc.h: CDotProcessDoc 클래스의 인터페이스
//


#pragma once


class CDotProcessDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CDotProcessDoc() noexcept;
	DECLARE_DYNCREATE(CDotProcessDoc)

// 특성입니다.
public:

	
// 작업입니다.
public:
	unsigned char m_OpenImg[256][256];
	unsigned char m_ResultImg[256][256];
	unsigned char m_ImageBuf1[256][256]; // 추가
	unsigned char m_ImageBuf2[256][256]; // 추가
	unsigned int histoin[256];
	unsigned int histoout[256];
	unsigned int histoinV[256];
	unsigned int histooutV[256];

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
	virtual ~CDotProcessDoc();
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
	void DoubleLoad();
	void m_slideSum(int slideconst);
	void Histoin();
	void HistoOut();
	void Histoequal();
	void Stretch();
	void m_slideBinary(int slideBin);
	void AutoBin1();
	void AutoBin2();
	void HistoinVer();
	void HistoOutVer();
};
