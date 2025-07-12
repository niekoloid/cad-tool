//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFReadFeatureManagerC.h               �쐬���F2000.04.23
//
//	�P�D�N���X�T�v
//      FeatureComment�A�Z���u���v�f�A
//      ��ʗv�f�̐e�q�֌W���Ǘ�����
//
//	�Q�D����
//		����ԍ�	���t��			�S����			 �T�v
//		�쐬		2000.04.23		��
//		�X�V		2015.04.27		T.Matsushima	JPCERT/CC �w�E �Ǝ㐫�Ή�
//
//------------------------------------------------------------
#ifndef _SXFFEATURECHILDC_H_
#define _SXFFEATURECHILDC_H_

#include <afx.h>
#include <afxtempl.h>
#include "SXFFeatureAssemblyC.h"
#include "SXFDataStructC.h"

class SXFReadMapManagerC;
class SXFFeatureChildC;

typedef CTypedPtrList<CPtrList,SXFFeatureAssemblyC*> SXFASSEMBLYLIST;

class SXFReadFeatureManagerC  
{
public:
	SXFReadFeatureManagerC();
	virtual ~SXFReadFeatureManagerC();
	BOOL RegisterFeatureAssembly(INSTANCEDATA *IN_Instance);
	BOOL RegisterFeatureEntity(INSTANCEDATA *IN_Instance);
//	JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
	int GetNextFeature(char* OUT_TypeName,
							size_t	TypeNameSize,	// �o�b�t�@�T�C�Y��n���悤�ɕύX
							LPVOID& OUT_Struct,
							int* OUT_EndFlg);
	int GetNextAssembly(int IN_Type, 
							LPVOID& OUT_Struct, 
							int* OUT_EndFlg,
							int& OUT_InstanceID);
	BOOL GetSfigFlg( LPCTSTR IN_Name,int* OUT_SfigFlg,int*OUT_LocFlg);
	BOOL SetLocFlg( LPCTSTR IN_Name);
	BOOL CheckHatchID( int IN_ID);
	void Delete_m_CurrentChildList();

private:
    SXFASSEMBLYLIST*     m_CurveAssemblyList;	/* �����Ȑ�̨���ð��� */
	SXFASSEMBLYLIST*     m_SymbolAssemblyList;	/* �����}�`̨���ð��� */
	CMapStringToPtr		 m_SymbolInfoTable;		// 2010.08
    SXFFeatureAssemblyC* m_SheetAssembly;		/* �p��̨����̵�޼ު�� */
    SXFASSEMBLYLIST*     m_AssemblyList;		/* ������ð��� */
    SXFFeatureAssemblyC* m_CurrentAssembly;		/* ���ݏ������̱����ؗv�f��޼ު�� */
    SXFCHILDLIST*        m_CurrentChildList;	/* ���ݏ������̈�ʗv�fð��� */
    SXFFeatureChildC*    m_CurrentChild;		/* ���ݏ������̈�ʗv�f��޼ު�� */
    SXFReadMapManagerC*  m_CurrentMapManager;	/* ���ݏ�������Mapping�Ǘ���޼ު�� */
    POSITION			 m_AssemblyPos;			/* ������ð��ق�Position */
    POSITION			 m_ChildPos;			/* ��ʗv�fð��ق�Position */
	int					 m_CurrentAssemblyType;	/* ���ݏ������̱��������� */
	int					 m_code;				/* �����غ��� */
};

#endif
