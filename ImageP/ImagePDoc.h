
// ImagePDoc.h : CImagePDoc ��Ľӿ�
//


#pragma once
#include "Dib.h"

class CImagePDoc : public CDocument
{
protected: // �������л�����
	CImagePDoc();
	DECLARE_DYNCREATE(CImagePDoc)

// ����
public:
	CDib m_dib;
	BOOL AfreshLoad();			// ���¼���ͼ��
// ����
public:
	CDib* getDib();
// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CImagePDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
