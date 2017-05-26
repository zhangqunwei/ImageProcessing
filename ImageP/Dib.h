#pragma once
#ifndef __CDIB_H_
#define __CDIB_H_

#include "atlimage.h"
class CDib :
	public CImage
{
public:
	CDib();
	~CDib();
// ����
public:
	CString m_filename;
	BOOL m_IsUseOBJ;	// ָʾͼ���Ƿ��ʹ��
	BOOL m_IsUseTEM;	// ָʾģ���Ƿ����
	BYTE m_pixelValue;	// �������ص�ĻҶ�ֵ
	DWORD  lWidth;
	DWORD lHeight;
// ����
public:
	BOOL IsGray();				// ���� TRUE �ǻҶ�ͼ��FALSE���ǻҶ�ͼ��
	void Template3x3(int arr[], double coef);// 3x3����ģ��
	void Template5x5(int arr[], double coef);// 5x5����ģ��
	void Histeq();				// ֱ��ͼ���⻯
	void Gauss3x3();			// ��˹ƽ��3x3
	void Gauss5x5();			// ��˹ƽ��5x5
	void Laplace4();			// ������˹���ӣ�4��
	void Laplace8();			// ������˹���ӣ�8��
};

 #endif // !__CDIB_H_
