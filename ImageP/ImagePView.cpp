
// ImagePView.cpp : CImagePView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "ImageP.h"
#endif

#include "ImagePDoc.h"
#include "ImagePView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImagePView

IMPLEMENT_DYNCREATE(CImagePView, CView)

BEGIN_MESSAGE_MAP(CImagePView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_OPEN, &CImagePView::OnFileOpen)
	ON_COMMAND(ID_32771, &CImagePView::OnHisteq)
	ON_COMMAND(ID_32772, &CImagePView::OnGauss5x5)
	ON_COMMAND(ID_32774, &CImagePView::OnGauss3x3)
	ON_COMMAND(ID_32777, &CImagePView::OnLaplace4)
	ON_COMMAND(ID_32778, &CImagePView::OnLaplace8)
END_MESSAGE_MAP()

// CImagePView ����/����

CImagePView::CImagePView()
{
	// TODO:  �ڴ˴���ӹ������
	m_font.CreateFontW(-20,			// �߼��߶�
		0,							// ƽ����ȣ�ȡĬ��ֵ
		0,							// �нǶ�Ϊ0��ˮƽ
		0,							// �ַ��Ƕ�0������
		FW_NORMAL,					// ������
		FALSE,						// ����б
		FALSE,						// �����»���
		FALSE,						// ����ɾ����
		GB2312_CHARSET,				// �����ַ���
		OUT_STROKE_PRECIS,
		CLIP_STROKE_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_MODERN,
		L"����_GB2312"); 

}

CImagePView::~CImagePView()
{
}

BOOL CImagePView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style &= ~WS_BORDER;
	return CView::PreCreateWindow(cs);
}

// CImagePView ����

void CImagePView::OnDraw(CDC* pDC)
{
	CImagePDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) 
		return;
	m_pDoc = pDoc;
	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	CRect rect;
	
	// ��ȡ�ͻ����Ĵ�С
	GetClientRect(rect);
	// ����Ϊ��ɫ����
	//pDC->FillSolidRect(rect, RGB(230, 230, 230));     
	// ���Ͻ�ʼ����ʾԭʼͼ��
	if (pDoc->m_dib.m_IsUseOBJ)
	{
		AutoShow(L"ԭʼͼ��");
	}
}


// CImagePView ��ӡ

BOOL CImagePView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CImagePView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CImagePView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CImagePView ���

#ifdef _DEBUG
void CImagePView::AssertValid() const
{
	CView::AssertValid();
}

void CImagePView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImagePDoc* CImagePView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImagePDoc)));
	return (CImagePDoc*)m_pDocument;
}
#endif //_DEBUG


// CImagePView ��Ϣ�������

/************************************************************************
 *	Ĭ�ϳ�ʼ��
 ************************************************************************/
void CImagePView::DefaultInitial()
{
	m_imageHeight = GetDocument()->m_dib.GetHeight();
	m_imageWidth = GetDocument()->m_dib.GetWidth();
	m_AutoShowNum = 0;
	
}

/************************************************************************
 *	�Զ���ʾ
 ************************************************************************/
void CImagePView::AutoShow(LPCTSTR title)
{
	int x, y;
	if (m_AutoShowNum < 3)
	{
		x = (m_imageWidth+20)*m_AutoShowNum;
		y = 0;
	}
	else
	{
		x = (m_imageWidth+20)*(m_AutoShowNum - 3);
		y = m_imageHeight + 30;
	}
	GetDC()->SelectObject(m_font);
	GetDC()->SetBkMode(TRANSPARENT);	// ���屳��ɫ͸��
	GetDC()->TextOut(x, y, title);
	GetDocument()->m_dib.Draw(GetDC()->m_hDC, x, y+20);
	m_AutoShowNum++;
}

/************************************************************************
 *	���ļ�
 ************************************************************************/
void CImagePView::OnFileOpen()
{
	// TODO:  �ڴ���������������
	// ���ļ��Ի���
	CFileDialog ImageFile(TRUE, _T("BMP"), _T("*.BMP"),
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("λͼ�ļ�(*.BMP)|*.BMP|"));
	// �ļ��Ƿ��
	if (ImageFile.DoModal() == IDOK)
	{
		// ���벢������ǰ��ͼ��
		m_pDoc->getDib()->Destroy();
		// ���ص�ǰ�򿪵�ͼ��
		m_pDoc->getDib()->Load(ImageFile.GetPathName());
		// �Ƿ���سɹ�
		if (!m_pDoc->getDib()->IsNull())
		{
			//  �ǻҶ�ͼ��
			if (!m_pDoc->getDib()->IsGray())
			{
				MessageBox(L"���ǻҶ�ͼ��");
			}	
			else
			{	// �ǻҶ�ͼ������ͼ��ɲ���
				m_pDoc->m_dib.m_IsUseOBJ = TRUE;
				// �����ļ���
				m_pDoc->m_dib.m_filename = ImageFile.GetPathName();
				// ��view�е�������Գ�ʼ��
				DefaultInitial();
			}	
		}
		else
		{
			AfxMessageBox(L"ͼƬ����ʧ�ܣ�");
		}
	}
	Invalidate();
}

/************************************************************************
 *	ֱ��ͼ���⻯
 ************************************************************************/
void CImagePView::OnHisteq()
{
	// TODO:  �ڴ���������������

	// ���¼���ͼ��
	m_pDoc->AfreshLoad();

	if (m_pDoc->m_dib.m_IsUseOBJ)
	{
		m_pDoc->m_dib.Histeq();
		AutoShow(L"ֱ��ͼ���⻯��:");
	}
	else
	{
		MessageBox(L"���ȴ�һ���Ҷ�ͼ��(.BMP��ʽ)��");
	}
}

/************************************************************************
 *	��˹ƽ��3x3
 ************************************************************************/
void CImagePView::OnGauss3x3()
{
	// TODO:  �ڴ���������������

	// ���¼���ͼ��
	m_pDoc->AfreshLoad();

	if (m_pDoc->m_dib.m_IsUseOBJ)
	{
		//clock_t start, finish;
		//start = clock(); //ʱ�����
		m_pDoc->m_dib.Gauss3x3();
		//finish = clock();
		//double ti =(finish - start) / CLOCKS_PER_SEC;
		//CString str;
		//str.Format(L"%d",ti);
		//MessageBox(str);
		AutoShow(L"��˹ƽ��3x3:");
	}
	else
	{
		MessageBox(L"���ȴ�һ���Ҷ�ͼ��(.BMP��ʽ)��");
	}
}

/************************************************************************
 *	��˹ƽ��5*5
 ************************************************************************/
void CImagePView::OnGauss5x5()
{
	// TODO:  �ڴ���������������
	
	// ���¼���ͼ��
	m_pDoc->AfreshLoad();
	
	if (m_pDoc->m_dib.m_IsUseOBJ)
	{
		m_pDoc->m_dib.Gauss5x5();
		AutoShow(L"��˹ƽ��5x5:");
	}
	else
	{
		MessageBox(L"���ȴ�һ���Ҷ�ͼ��(.BMP��ʽ)��");
	}
}

/************************************************************************
 *	������˹��4��
 *	4��������
 ************************************************************************/
void CImagePView::OnLaplace4()
{
	// TODO:  �ڴ���������������

	// ���¼���ͼ��
	m_pDoc->AfreshLoad();

	if (m_pDoc->m_dib.m_IsUseOBJ)
	{
		m_pDoc->m_dib.Laplace4();
		AutoShow(L"������˹����4-����:");
		//Invalidate();
	}
	else
	{
		MessageBox(L"���ȴ�һ���Ҷ�ͼ��(.BMP��ʽ)��");
	}
}

/************************************************************************
*	������˹��8��
*	8��������
************************************************************************/
void CImagePView::OnLaplace8()
{
	// TODO:  �ڴ���������������

	// ���¼���ͼ��
	m_pDoc->AfreshLoad();

	if (m_pDoc->m_dib.m_IsUseOBJ)
	{
		m_pDoc->m_dib.Laplace8();
		AutoShow(L"������˹����8����:");
	}
	else
	{
		MessageBox(L"���ȴ�һ���Ҷ�ͼ��(.BMP��ʽ)��");
	}
}
