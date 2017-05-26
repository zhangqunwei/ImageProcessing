#include "stdafx.h"
#include "Dib.h"

CDib::CDib()
{
	m_IsUseOBJ = FALSE;
	m_pixelValue = 0;
}


CDib::~CDib()
{
}

/************************************************************************
 *	ֱ��ͼ���⻯
 ************************************************************************/
void CDib::Histeq()
{
	long lWidth, lHeight;	
	// ����ͼ��ĳ��Ϳ�
	lWidth = GetWidth();
	lHeight = GetHeight();
	
	// ����ͼƬ�и����Ҷȼ������صĸ���
	UINT pixelNum[256] = { 0 };

	// ͳ��ͼƬ��ÿ���Ҷȼ����صĸ���
	for (int i = 0; i < lHeight; i++)	// ÿ��
	for (int j = 0; j < lWidth; j++)	// ÿ��
	{
		// �������ص㣨j��i���ĻҶ�ֵ
		m_pixelValue = (BYTE)GetPixel(j, i);
		// ���Ҷ�ֵ��Ϊ�����������������
		pixelNum[m_pixelValue] = pixelNum[m_pixelValue] + 1;
	}

	// **1 ԭʼֱ��ͼ ��Original histogram �� [ ��һ�� ����������Ҷȼ��ĸ��� ]
	double Sk[256] = { 0 };
	for (int i = 0; i < 256; i++)
		Sk[i] = pixelNum[i] / (lHeight*lWidth*1.0);

	// **2 �ۼ�ֱ��ͼ ��Cumulative histogram��
	double Tk[256] = { 0 };
	for (int i = 0; i < 256; i++)
	if (i == 0)
		Tk[i] = Sk[i];
	else
		Tk[i] = Tk[i - 1] + Sk[i];

	// **3 ȡ����չ��Integral expansion��[ ��ʽ��pixelCumu = int[(L-1)*pixelCumu+0.5]��LΪ�Ҷȼ���]
	for (int i = 0; i < 256; i++)
		Tk[i] = UINT8((256 - 1)*Tk[i] + 0.5);

	// **4 �ԻҶ�ֵ����ӳ�䲢д��
	for (int i = 0; i < lHeight; i++)	// ÿ��
	for (int j = 0; j < lWidth; j++)	// ÿ��
	{
		m_pixelValue = (BYTE)GetPixel(j, i);
		m_pixelValue = (BYTE)Tk[m_pixelValue];
		SetPixel(j, i, RGB(m_pixelValue, m_pixelValue, m_pixelValue));
	}
}// !void CDib::histeq()

/************************************************************************
 *	ʹ��3x3ģ������ͼ��
 *  ע�⣺1.����ʱ��Ӧϵ����ˣ����Ѿ�������������ֵд��ͼ��
 *		  2.ģ��ϵ������������Ϊfloat��
 ************************************************************************/
void CDib::Template3x3(int arr[],double coef)
{
	// ����ͼ��ĳ��Ϳ�
	lWidth = GetWidth();
	lHeight = GetHeight();

	double sum = 0;
	for (DWORD i = 0; i < lHeight - 3; i++)	// ÿ��
	for (DWORD j = 0; j < lHeight - 3; j++)	// ÿ��
	{	// ʹ��ģ����о������
		sum = arr[0] * (BYTE)GetPixel(j, i + 2) + arr[1] * (BYTE)GetPixel(j + 1, i + 2) + arr[2] * (BYTE)GetPixel(j + 2, i + 2) + sum;
		sum = arr[3] * (BYTE)GetPixel(j, i + 1) + arr[4] * (BYTE)GetPixel(j + 1, i + 1) + arr[5] * (BYTE)GetPixel(j + 2, i + 1) + sum;
		sum = arr[6] * (BYTE)GetPixel(j, i) + arr[7] * (BYTE)GetPixel(j + 1, i) + arr[8] * (BYTE)GetPixel(j + 2, i) + sum;
		sum = (int)(sum*coef);
		//�������ֵ
		sum = fabs(sum);

		//���С��0��ǿ�Ƹ�ֵΪ0
		if (sum<0)
			sum = 0;

		//�������255��ǿ�Ƹ�ֵΪ255
		if (sum>255)
			sum = 255;
		SetPixel(j + 1, i + 1, RGB(sum, sum, sum));
	}
}

/************************************************************************
*	ʹ��5x5ģ������ͼ��
*	ע�⣺1.����ʱ��Ӧϵ����ˣ����Ѿ�������������ֵд��ͼ��
*		  2.ģ��ϵ������������Ϊfloat��
 ************************************************************************/
void CDib::Template5x5(int arr[],double coef)
{
	// ����ͼ��ĳ��Ϳ�
	lWidth = GetWidth();
	lHeight = GetHeight();

	double sum = 0;
	for (DWORD i = 0; i < lHeight - 4; i++)		// ÿ��
	for (DWORD j = 0; j < lWidth - 4; j++)		// ÿ��
	{	// ʹ��ģ����о������
		sum = arr[0] * (BYTE)GetPixel(j, i + 4) + arr[1] * (BYTE)GetPixel(j + 1, i + 4) + arr[2] * (BYTE)GetPixel(j + 2, i + 4) +
			  arr[3] * (BYTE)GetPixel(j + 3, i + 4) + arr[4] * (BYTE)GetPixel(j + 4, i + 4) + sum;
		sum = arr[5] * (BYTE)GetPixel(j, i + 3) + arr[6] * (BYTE)GetPixel(j + 1, i + 3) + arr[7] * (BYTE)GetPixel(j + 2, i + 3) +
			  arr[8] * (BYTE)GetPixel(j + 3, i + 3) + arr[9] * (BYTE)GetPixel(j + 4, i + 3) + sum;
		sum = arr[10] * (BYTE)GetPixel(j, i + 2) + arr[11] * (BYTE)GetPixel(j + 1, i + 2) + arr[12] * (BYTE)GetPixel(j + 2, i + 2) +
			  arr[13] * (BYTE)GetPixel(j + 3, i + 2) + arr[14] * (BYTE)GetPixel(j + 4, i + 2) + sum;
		sum = arr[15] * (BYTE)GetPixel(j, i + 1) + arr[16] * (BYTE)GetPixel(j + 1, i + 1) + arr[17] * (BYTE)GetPixel(j + 2, i + 1) +
			  arr[18] * (BYTE)GetPixel(j + 3, i + 1) + arr[19] * (BYTE)GetPixel(j + 4, i + 1) + sum;
		sum = arr[20] * (BYTE)GetPixel(j, i) + arr[21] * (BYTE)GetPixel(j + 1, i) + arr[22] * (BYTE)GetPixel(j + 2, i) +
			  arr[23] * (BYTE)GetPixel(j + 3, i) + arr[24] * (BYTE)GetPixel(j + 4, i) + sum;

		//sum = (int)(1 / 273 * sum);	// ��ʾȫ��
		//sum = (int)1 / 273 * sum;		// ��ʾȫ��
		sum = (int)(sum*coef);
		//�������ֵ
		sum = fabs(sum);

		//���С��0��ǿ�Ƹ�ֵΪ0
		if (sum<0)
			sum = 0;

		//�������255��ǿ�Ƹ�ֵΪ255
		if (sum>255)
			sum = 255;
		SetPixel(j+2, i+2, RGB(sum, sum, sum));
	}
}

/************************************************************************
 *	��˹ƽ��3x3
 ************************************************************************/
void CDib::Gauss3x3()
{
	// �趨ģ��ϵ��
	int arr[9] = { 1, 2, 1,
				   2, 4, 2,
				   1, 2, 1 };
	// ʹ��3x3����ģ��
	//Template3x3(arr,1/16);
	Template3x3(arr, (double)1 / 16);
}

/************************************************************************
 *	��˹ƽ��5x5
 ************************************************************************/
void CDib::Gauss5x5()
{
	//	�趨ģ��ϵ����
	int arr[25] = { 1,  4,  7,  4, 1,
					4, 16, 26, 16, 4,
					7, 26, 41, 26, 7,
					4, 16, 26, 16, 4,
					1,  4,  7,  4,  1 };
	// ʹ��5x5����ģ��
	//Template5x5(arr,1/273);
	//Template3x3(arr,float(1 / 273));
	Template5x5(arr, (double)1 / 273);
}

/************************************************************************
 *	������˹���ӣ�4��
 *	˵����4 ָ����ϵ��Ϊ4������
 ************************************************************************/
void CDib::Laplace4()
{
	// �趨����ϵ��
	int arr[9] = { 0, -1, 0,
				   -1, 4, -1,
				   0, -1, 0  };

	// ʹ��3x3����ģ��
	Template3x3(arr,1);
}

/************************************************************************
*	������˹���ӣ�8��
*	˵����8 ָ����ϵ��Ϊ8������
************************************************************************/
void CDib::Laplace8()
{
	// �趨����ϵ��
	int arr[9] = { -1, -1, -1,
				   -1,  12, -1,
				   -1, -1, -1 };

	// ʹ��3x3����ģ��
	Template3x3(arr,1);
}

/************************************************************************
 *	�ж��Ƿ��ǻҶ�ͼ��
 *	��		����TRUE
 *	����	����FALSE
 ************************************************************************/		
BOOL CDib::IsGray()
{
	COLORREF col;
	// �������أ�2��2������ɫֵ����ͼ��ߴ����ƣ�ֵ���˹���
	col = GetPixel(2, 2);
	// ����������ɫ����
	BYTE r, g, b;
	r = GetRValue(col);
	g = GetGValue(col);
	b = GetBValue(col);
	// ÿ�����ص�λ��Ϊ8λ��ȡ���ĸ�����ɫ���������Ϊ�Ҷ�ͼ
	//if ((8 == GetBPP()) && (r == g == b)) // ����
	if ((8 != GetBPP()) || (r != g))
		return FALSE;
	else
		return TRUE;
}//!BOOL CDib::isGray()
