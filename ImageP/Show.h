#pragma once
#include "MainFrm.h"

class CShow:public CView,public CMainFrame
{
public:
	CShow();
	~CShow();

// ����
public:
	CPoint m_point[10];
// ����
public:
	void CShow::Subplot(UINT8 row, UINT8 column, UINT8 current);
	void Title(LPCTSTR lpszTitle);
	void bar(double OneDimensionalArray);
};

