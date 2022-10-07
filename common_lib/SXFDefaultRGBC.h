/**
	All Rights Reserved,(c) JACIC 2001
	SXFDefaultRGBC.h                  �쐬���F2000.04.29

	�P�D�N���X�T�v
		�F�e�[�u�������Ǘ�����

	�Q�D����
	    ����ԍ�    ���t��         �S����		�T�v
		�쐬		2000.4.29     �{��(FQS)
**/

#if !defined(AFX_SXFDEFAULTRGBC_H__1F511813_020C_11D5_A3BC_009027565E9B__INCLUDED_)
#define AFX_SXFDEFAULTRGBC_H__1F511813_020C_11D5_A3BC_009027565E9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SXFDefaultRGBC  
{
public:
	SXFDefaultRGBC();
	SXFDefaultRGBC(int code,
					char *name, 
					int red,
					int green,
					int blue);
	virtual ~SXFDefaultRGBC();
	void GetName(char*& name);
	int GetCode();
private:
    int m_Code;			/* �F���� */
	char m_Name[16];	/* �F�� */
	int m_Red;			/* R�l */
	int m_Green;		/* G�l */
	int m_Blue;			/* B�l */
};

#endif // !defined(AFX_SXFDEFAULTRGBC_H__1F511813_020C_11D5_A3BC_009027565E9B__INCLUDED_)
