//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFPreDefColorC.h                     �쐬���F2000.04.16
//
//	�P�D�N���X�T�v
//		PreDefColor Instance Table Data���Ǘ�����
//
//	�Q�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.16     ��
//
//------------------------------------------------------------
#ifndef _SXFPREDEFCOLORC_H_
#define _SXFPREDEFCOLORC_H_

#include <afx.h>

class SXFTableMapManagerC;

class SXFPreDefColorC  
{
public:
	SXFPreDefColorC(  );
	virtual ~SXFPreDefColorC();
	BOOL SetName(LPCTSTR IN_Name);

    int						m_Code;				/* �F���� */
    int						m_ID;				/* �ݽ�ݽID */
    CString					m_Name;				/* �F�� */
    SXFTableMapManagerC*	m_MappingManager;	/* ��`ð��ٗv�fMapping�Ǘ���޼ު�� */

};

#endif
