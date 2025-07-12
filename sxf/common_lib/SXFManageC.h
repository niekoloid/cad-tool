/**
	All Rights Reserved,(c) JACIC 2001
	SXFManageC.h								�쐬���F2000.3.29

	�P�D�N���X�T�v
	�ϊ��Ǘ��N���X

	�Q�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.3.29			�{��(FQS)			�Ȃ��B
	�X�V			2015.04.27			T.Matsushima		JPCERT/CC �w�E �Ǝ㐫�Ή�

**/

#if !defined(AFX_SXFMANAGEC_H__A3F5E7A2_049F_11D4_A76E_00000EB03267__INCLUDED_)
#define AFX_SXFMANAGEC_H__A3F5E7A2_049F_11D4_A76E_00000EB03267__INCLUDED_

#include "SXFComInfoC.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "SXFRuleCheckC.h"	// ClassView �ɂ���Ēǉ�����܂����B
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SXFComInfoC;
class SXFPart21FileWriteC;
class SXFTableManagerC;
class SXFWriteManagerC;
class SXFInstanceIDC;
class SXFPart21FileReadC;
class SXFReadFeatureManagerC;

class SXFManageC  
{
public:
	void Delete_assembly(int assem_type,void*& f_struct);
	void Delete_feature(char* feature_name,void*& f_struct);
//	int Read_next_feature(char* OUT_Type,LPVOID& OUT_Struct, int* OUT_EndFlag);						JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
	int Read_next_feature(char* OUT_Type,size_t TypeSize,LPVOID& OUT_Struct, int* OUT_EndFlag);		// �o�b�t�@�T�C�Y��n���悤�ɕύX
	int Read_assembly_name(int IN_Type,LPVOID& OUT_Struct,int* OUT_EndFlag);
	int Read_table(int IN_TableType,LPVOID OUT_Struct,int* OUT_EndFlag);
	int Write_next_feature(char* IN_FeatureType,void* IN_Struct);
	int Write_assembly_name(int IN_Assem_type,void* IN_Struct);
	int Write_table(int IN_table_type,void* IN_str);
	int Close();
	int Open(char IN_file_name[257],
				int IN_rw_flg, 
				double IN_tolerance1,
				double IN_tolerance2,
				double IN_divide, 
				int IN_level, 
				int IN_mode, 
				char INOUT_author[257], 
				char INOUT_org[257],
				char INOUT_translator_name[257],
				char OUT_version[257]);
	SXFManageC();
	virtual ~SXFManageC();

private:
	int Param_Check(int IN_rw_flg,int IN_level, int IN_mode);

	SXFReadFeatureManagerC* m_ReadFeatureManager;	/* Read�Ǘ���޼ު�� */
	SXFInstanceIDC*			m_InstanceIDManager;	/* �ݽ�ݽID��޼ު�� */
	int						m_Assem_type;			/* �����،^ */
	SXFWriteManagerC*		m_WriteManager;			/* Write�Ǘ���޼ު�� */
	SXFRuleCheckC			m_rulecheck;			/* ٰ�������޼ު�� */
	SXFTableManagerC*		m_TableManager;			/* ��`ð��يǗ���޼ު�� */
	SXFPart21FileWriteC*	m_WriteFile;			/* ̧�ُo�͵�޼ު�� */
	SXFPart21FileReadC*		m_ReadFile;				/* ̧�ٓ��͵�޼ު�� */
	SXFComInfoC				m_Info;					/* ���ʏ��Ǘ���޼ު�� */
};

#endif // !defined(AFX_SXFMANAGEC_H__A3F5E7A2_049F_11D4_A76E_00000EB03267__INCLUDED_)
