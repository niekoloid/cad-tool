/**
	All Rights Reserved,(c) JACIC 2001
	SXFWidthTableC.h                �쐬���F2000.04.29

	�P�D�N���X�T�v
		�����e�[�u�������Ǘ�����

	�Q�D����
	    ����ԍ�    ���t��         �S����		�T�v
		�쐬		2000.4.29     �{��(FQS)
**/
#ifndef _SXFPREWIDTHTABLEC_H_
#define _SXFPREWIDTHTABLEC_H_

#include <afxtempl.h>
#include "SXFDefaultPreWidthC.h"

typedef CArray<SXFDefaultPreWidthC, SXFDefaultPreWidthC&> SXFPREWIDTHTABLE;

class SXFPreWidthTableC  
{
public:
	SXFPreWidthTableC();
	~SXFPreWidthTableC();
    BOOL GetPreWidth(int in_code,double& out_width);
    int GetCode(double IN_Width,double IN_Eps);
private:
    SXFPREWIDTHTABLE m_DefaultPreWidthTable;		/* ����ð��� */
};

#endif // _SXFPREWIDTHTABLEC_H_
