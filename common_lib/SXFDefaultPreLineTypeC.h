/**
	All Rights Reserved,(c) JACIC 2001
	SXFDefaultPreLineTypeC.h                  �쐬���F2000.04.29

	�P�D�N���X�T�v
		����e�[�u�������Ǘ�����

	�Q�D����
	    ����ԍ�    ���t��         �S����		�T�v
		�쐬		2000.4.29     �{��(FQS)
**/
#if !defined(AFX_SXFDEFAULTPRELINETYPEC_H__1F511812_020C_11D5_A3BC_009027565E9B__INCLUDED_)
#define AFX_SXFDEFAULTPRELINETYPEC_H__1F511812_020C_11D5_A3BC_009027565E9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SXFDefaultPreLineTypeC  
{
public:
	SXFDefaultPreLineTypeC();
	SXFDefaultPreLineTypeC(int in_code, const char *in_name);
	virtual ~SXFDefaultPreLineTypeC();
    void GetName(char*& out_name);
	int GetCode();
private:
    int m_Code;			/* ������ */
    char m_Name[128];	/* ���햼 */
};

#endif // !defined(AFX_SXFDEFAULTPRELINETYPEC_H__1F511812_020C_11D5_A3BC_009027565E9B__INCLUDED_)
