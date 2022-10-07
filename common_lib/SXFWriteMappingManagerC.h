/**
	All Rights Reserved,(c) JACIC 2001
	SXFWriteMappingManagerC.h								�쐬���F2000.4.14

	�P�D�N���X�T�v
	Write���̃t�B�[�`���I�u�W�F�N�g��Mapping�I�u�W�F�N�g�̊Ǘ����s���N���X

	�Q�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.14			�{��(FQS)			�Ȃ��B

**/

#if !defined(AFX_SXFWRITEMAPPINGMANAGERC_H__A623AA20_11F2_11D4_A76E_00000EB03267__INCLUDED_)
#define AFX_SXFWRITEMAPPINGMANAGERC_H__A623AA20_11F2_11D4_A76E_00000EB03267__INCLUDED_

#include "SXFStruct.h"	// ClassView �ɂ���Ēǉ�����܂����B
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afx.h>
#include "SXFStruct.h"
#include "SXFWriteManagerC.h"

class SXFPart21FileWriteC;
class SXFInstanceIDC;
class SXFFeatureC;

class SXFWriteMappingManagerC  
{
public:
	int MappingFeature(char *IN_FeatureType, LPVOID IN_Struct,int &OUT_Id1);
	int MappingAssembly();
	void SetStructData(int IN_Asem_Type,LPVOID IN_Struct);
	SXFWriteMappingManagerC();
	SXFWriteMappingManagerC(int IN_AssemType,
							SXFPart21FileWriteC* IN_WriteFile,
							SXFInstanceIDC* IN_InstanceIDManager);
	void ClearData();
	virtual ~SXFWriteMappingManagerC();

private:
	SXFFeatureC*			m_AsemFeature;			/* ������̨�����޼ު�� */
	SXFFeatureC*			m_Feature;				/* ��ʗv�f̨�����޼ު�� */
	SXFPart21FileWriteC*	m_WriteFile;			/* ̧�ُo�͵�޼ު�� */
	SXFInstanceIDC*			m_InstanceIDManager;	/* �ݽ�ݽID��޼ު�� */
	int						m_AssemType;			/* �����،^ */
	Sheet_Struct			m_Sheet_Str;			/* �p���\���� */
	Sfigorg_Struct			m_Sfigorg_Str;			/* �����}�`��`�\���� */
	Ccurve_Org_Struct		m_CompCurve_Str;		/* �����Ȑ���` */
};

#endif // !defined(AFX_SXFWRITEMAPPINGMANAGERC_H__A623AA20_11F2_11D4_A76E_00000EB03267__INCLUDED_)
