//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFFeatureChildC.h                   �쐬���F2000.04.20
//
//	�P�D�N���X�T�v
//      Feature Child Data���Ǘ�����
//      
//	�Q�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.20    ��
//
//------------------------------------------------------------

#if !defined(AFX_SXFFEATURECHILDC_H__7A7CDA81_1A22_11D4_A76E_00000EB03267__INCLUDED_)
#define AFX_SXFFEATURECHILDC_H__7A7CDA81_1A22_11D4_A76E_00000EB03267__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SXFReadMapManagerC;

class SXFFeatureChildC  
{
public:
	SXFFeatureChildC();
	virtual ~SXFFeatureChildC();

    int					ChildID;		/* ��ʗv�f̨����̲ݽ�ݽID */
    SXFReadMapManagerC*	ChildMapManager;/* ��ʗv�f̨���Mapping�Ǘ���޼ު�� */
};

#endif // !defined(AFX_SXFFEATURECHILDC_H__7A7CDA81_1A22_11D4_A76E_00000EB03267__INCLUDED_)
