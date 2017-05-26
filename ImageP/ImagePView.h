
// ImagePView.h : CImagePView ��Ľӿ�
//

#pragma once

class CImagePView : public CView
{
protected: // �������л�����
	CImagePView();
	DECLARE_DYNCREATE(CImagePView)

// ����
public:
	CImagePDoc* GetDocument() const;
	CImagePDoc* m_pDoc;
	CFile m_memImageFile;
	CFont m_font;
	int m_imageHeight;
	int m_imageWidth;
	UINT8 m_AutoShowNum;
// ����
public:
	void DefaultInitial();
	void AutoShow(LPCTSTR title);
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CImagePView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	afx_msg void OnHisteq();

	afx_msg void OnGauss5x5();
	afx_msg void OnGauss3x3();
	afx_msg void OnLaplace4();
	afx_msg void OnLaplace8();
};

#ifndef _DEBUG  // ImagePView.cpp �еĵ��԰汾
inline CImagePDoc* CImagePView::GetDocument() const
   { return reinterpret_cast<CImagePDoc*>(m_pDocument); }
#endif

