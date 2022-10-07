//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFUserDefFontC.h                    �쐬���F2000.04.16
//
//	�P�D�N���X�T�v
//      UserDefFont Instance Table Data���Ǘ�����  
//
//	�Q�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.16     ��  
//
//------------------------------------------------------------
#ifndef _SXFUSERDEFFONTC_H_
#define _SXFUSERDEFFONTC_H_

#include <afx.h>
#include <afxtempl.h>

class SXFTableMapManagerC;

class SXFUserDefFontC  
{
public:
	SXFUserDefFontC(  );
	virtual ~SXFUserDefFontC();
	SXFUserDefFontC& operator=(const SXFUserDefFontC& IN_Userfont);

    int						m_Code;				/* ������ */
    int						m_ID;				/* �ݽ�ݽID */
    int						m_Segment;			/* ������ */
    CString					m_Name;				/* ���햼 */
    CArray<double,double>	m_Pitch;			/* �߯� */
    SXFTableMapManagerC*	m_MappingManager;	/* ��`ð��ٗv�fMapping�Ǘ���޼ު�� */
};

#endif

