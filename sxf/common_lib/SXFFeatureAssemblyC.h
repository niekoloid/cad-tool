//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFFeatureAssemblyC.h                  �쐬���F2000.04.20
//
//	�P�D�N���X�T�v
//      Feature Assembly�̐e�q�֌W���Ǘ�����
//      
//	�Q�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.20     ��        �Ȃ�
//
//------------------------------------------------------------

#if !defined(AFX_SXFFEATUREASSEMBLYC_H__7A7CDA82_1A22_11D4_A76E_00000EB03267__INCLUDED_)
#define AFX_SXFFEATUREASSEMBLYC_H__7A7CDA82_1A22_11D4_A76E_00000EB03267__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

#include "SXFReadMapManagerC.h"
#include "SXFFeatureChildC.h"

typedef CTypedPtrList<CPtrList,SXFFeatureChildC*> SXFCHILDLIST;

class SXFFeatureAssemblyC  
{
public:
	SXFFeatureAssemblyC();
	virtual ~SXFFeatureAssemblyC();

	int					AssemCurveFlag;		/* �����Ȑ��\���^��\���׸� */
	int					AssemSheetX;		/* �p�����މ��� */
	int					AssemSheetY;		/* �p�����ޏc�� */
	int					AssemSheetOrient;	/* �c�^���敪 */
	int					AssemSheetType;		/* �p�����ގ�� */
	int					AssemSymbolType;	/* �����}�`��� */
    int					AssemblyID;			/* ������̨���ID */
    int					AssemblyCode;		/* �����غ��� */
	int					m_CurveColour;		/* �����Ȑ��F���� */
	int					m_CurveType;		/* �����Ȑ������� */
	int					m_CurveWidth;		/* �����Ȑ��������� */
	int					m_SfigLocateFlag;	/* �����}�`�z�u�׸� */
											/* (���z�u:-1 �z�u��:1) */
	BOOL				m_AssemblyErrFlag;	/* ������̨����װ�׸� */
											/* (����:TRUE �ُ�:FALSE) */
    CString				AssemblyName;		/* �����ؖ� */
    SXFReadMapManagerC*	AssemblyMapManager;	/* ������̨���Mapping�Ǘ���޼ު�� */
    SXFCHILDLIST*		ChildList;			/* ��ʗv�fð��� */
};

#endif // !defined(AFX_SXFFEATUREASSEMBLYC_H__7A7CDA82_1A22_11D4_A76E_00000EB03267__INCLUDED_)
