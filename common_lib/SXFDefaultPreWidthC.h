// SXFDefaultPreWidthC.h: SXFDefaultPreWidthC �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////
/**
	All Rights Reserved,(c) JACIC 2001
	SXFWidthTableC.cpp                �쐬���F2000.04.29

	�P�D�N���X�T�v
		�����e�[�u�������Ǘ�����

	�Q�D����
	    ����ԍ�    ���t��         �S����		�T�v
		�쐬		2000.4.29     �{��(FQS)
**/

#if !defined(AFX_SXFDEFAULTPREWIDTHC_H__1F511811_020C_11D5_A3BC_009027565E9B__INCLUDED_)
#define AFX_SXFDEFAULTPREWIDTHC_H__1F511811_020C_11D5_A3BC_009027565E9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SXFDefaultPreWidthC  
{
public:
	SXFDefaultPreWidthC();
	virtual ~SXFDefaultPreWidthC();
	SXFDefaultPreWidthC(int in_code,double in_width);
	void GetWidth(double& out_width);

	int m_Code;			/* �������� */
	double m_Width;		/* ���� */
};

#endif // !defined(AFX_SXFDEFAULTPREWIDTHC_H__1F511811_020C_11D5_A3BC_009027565E9B__INCLUDED_)
