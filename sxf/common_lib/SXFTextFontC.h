//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFTextFontC.h                        �쐬���F2000.04.16
//
//	�P�D�N���X�T�v
//		TextFont Instance Table Data���Ǘ�����
// 
//	�Q�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.16     ��
//
//------------------------------------------------------------
#ifndef _SXFTEXTFONTC_H_
#define _SXFTEXTFONTC_H_

#include <afx.h>

class SXFTableMapManagerC;

class SXFTextFontC
{
public:
	SXFTextFontC(  );
	virtual ~SXFTextFontC();

    int						m_Code;				/* ����̫�ĺ��� */
    int						m_ID;				/* �ݽ�ݽID */
    CString					m_Name;				/* ����̫�Ė� */
    SXFTableMapManagerC*	m_MappingManager;	/* ��`ð��ٗv�fMapping�Ǘ���޼ު�� */
};

#endif
