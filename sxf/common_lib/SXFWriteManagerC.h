//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFWriteManagerC.h                    �쐬���F2000.04.18
//
//	�P�D�N���X�T�v
//      �o�͎��̃A�Z���u���Ԃ̎Q�Ɗ֌W���Ǘ�����
//
//	�Q�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.18    ��
//
//------------------------------------------------------------
#ifndef _SXFWRITEMANAGERC_H_
#define _SXFWRITEMANAGERC_H_

#include <afx.h>
#include <afxtempl.h>

typedef struct sfigorgcheck{
    int type;			//�����}�`���
							//1,2:�����}
							//3:��}�O���[�v
							//4:��}���i
    CString name;		//�����}�`��
	int locate_flag ;	//���z�u:-1 �z�u��:1
	int error;			//��`���G���[�̂Ƃ���-1
	sfigorgcheck() {
		type		= -1 ;
		locate_flag	= -1 ;
		error		= -1 ;
	}
}SXFSFIGORGCHECK;

//typedef CArray<SXFSFIGORGCHECK,SXFSFIGORGCHECK&> SXFSFIGORGTABLE;
typedef CList<SXFSFIGORGCHECK*,SXFSFIGORGCHECK*&> SXFSFIGORGTABLE;
#include "SXFWriteMappingManagerC.h"

class SXFWriteMappingManagerC;
class SXFPart21FileWriteC;
class SXFInstanceIDC;

class SXFWriteManagerC  
{
public:
	SXFWriteManagerC();
	SXFWriteManagerC(SXFPart21FileWriteC* IN_WriteFile,
					SXFInstanceIDC* IN_InstanceIDManager);
	virtual ~SXFWriteManagerC();
	void ErrorAssembly();
	int GetAssemType();
	int CloseAssembly();
    int RegisterAssembly(int IN_AssemblyType,LPVOID IN_Struct);
    int RegisterFeature(char* IN_FeatureType,LPVOID IN_Struct);
	BOOL SfigNameCheck( LPCTSTR IN_Name);
	BOOL GetSfigFlg( LPCTSTR IN_Name,
					int* OUT_Type,
					int* OUT_LocFlg);
	BOOL SetLocFlg( LPCTSTR IN_Name);
	BOOL CheckHatchID( unsigned int IN_ID);

private:
    CUIntArray					m_CurveTable;			/** �����Ȑ�ð��� **/
	int							m_CurveFlag;			/** �����Ȑ��׸� **/
	SXFPart21FileWriteC*		m_WriteFile;			/** ̧�ُo�͵�޼ު�� **/
	SXFInstanceIDC*				m_InstanceIDManager;	/** �ݽ�ݽID��޼ު�� **/
	int							m_SfigTableIndex;		/** �����}�`ð�����ޯ�� **/
	int							m_SfigFlag;				/** �����}�`�׸� **/
	int							m_AssemType;			/** �����،^ **/
	BOOL						m_SheetAssemblyFlag;	/** �p���׸� **/
    SXFWriteMappingManagerC*	m_CurrentAssembly;		/** �����ؗpMapping�Ǘ���޼ު�� **/
    SXFWriteMappingManagerC*	m_CurrentChild;			/** ��ʗv�f�pMapping�Ǘ���޼ު�� **/
    CUIntArray*					m_ChildrenArray;		/** ��ʗv�f���X�g **/
    BOOL						m_FirstAssemblyFlag;	/** �������׸� **/
	int							m_AssemblyCode;			/** �����غ��� **/
	SXFSFIGORGTABLE				m_SfigorgTable;			/** �����}�`ð��� **/
	BOOL						m_ErrorFlag;			/** �����شװ�׸� **/
	CMapStringToPtr				m_mapSfigOrg ;
};

#endif
