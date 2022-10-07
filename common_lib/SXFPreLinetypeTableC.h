/**
	All Rights Reserved,(c) JACIC 2001
	SXFPreLineTypeTableC.h                �쐬���F2000.04.29

	�P�D�N���X�T�v
		����`����e�[�u�������Ǘ�����

	�Q�D����
	    ����ԍ�    ���t��         �S����		�T�v
		�쐬		2000.4.29     �{��(FQS)
**/
#ifndef _SXFPRELINETYPETABLEC_H_
#define _SXFPRELINETYPETABLEC_H_

#include <string.h>
#include <afxtempl.h>
#include "SXFDefaultPreLineTypeC.h"

typedef CArray<SXFDefaultPreLineTypeC, SXFDefaultPreLineTypeC&> SXFDEFAULTPRELINETYPE;

class SXFPreLineTypeTableC{  

public:
	SXFPreLineTypeTableC();
	~SXFPreLineTypeTableC();
	BOOL GetPreLinetype(int in_code, char*& out_name);
	int GetPreCode(const char* in_name);
private:
	SXFDEFAULTPRELINETYPE m_DefaultPreLineTypeTable;	/* �Fð��� */
};

#endif // _SXFPRELINETYPETABLEC_H_
