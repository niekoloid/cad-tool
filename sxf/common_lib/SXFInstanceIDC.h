//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFInstanceIDC.h                     �쐬���F2000.04.07
//
//	�P�D�N���X�T�v
//		�C���X�^���XID�̎擾���s��
//      
//	�Q�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.07    ��
//
//------------------------------------------------------------
#ifndef _SXFINSTANCEIDC_H_
#define _SXFINSTANCEIDC_H_

#include "SXFFetIDC.h"
#include "SXFDataStructC.h"

class SXFInstanceIDC  
{
public:
	SXFInstanceIDC();
	virtual ~SXFInstanceIDC();
    int GetNewInstanceID();

    SXFFetIDC m_FeatureIDManager;	/* �ݽ�ݽID�Ǘ���޼ު�� */

};

#endif

