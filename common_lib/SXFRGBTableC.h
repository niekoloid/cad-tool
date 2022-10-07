/**
	All Rights Reserved,(c) JACIC 2001
	SXFRGBTableC.cpp                �쐬���F2000.04.29

	�P�D�N���X�T�v
		�F�e�[�u�������Ǘ�����

	�Q�D����
	    ����ԍ�    ���t��         �S����		�T�v
		�쐬		2000.4.29     �{��(FQS)
**/
#ifndef _SXFRGBTABLEC_H_
#define _SXFRGBTABLEC_H_

#include <math.h>
#include <string.h>
#include <afxtempl.h>
#include "SXFDefaultRGBC.h"

typedef CArray<SXFDefaultRGBC,SXFDefaultRGBC&> SXFDEFAULTCOLORTABLE;

class SXFRGBTableC{
public:
	SXFRGBTableC();
	~SXFRGBTableC();
	BOOL GetColorCode(const char*,int&);
private:
	SXFDEFAULTCOLORTABLE m_DefaultColorTable;		/* �Fð��� */

};

#endif//_SXFRGBTABLEC_H_
