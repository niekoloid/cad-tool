/**
	All Rights Reserved,(c) JACIC 2001
	SXFTableMapManagerC.h								�쐬���F2000.4.14

	�P�D�N���X�T�v
	��`�e�[�u���t�B�[�`���I�u�W�F�N�g��Mapping�I�u�W�F�N�g���Ǘ�����N���X

	�Q�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.14			�{��(FQS)			�Ȃ��B

**/

#if !defined(AFX_SXFTABLEMAPMANAGERC_H__16B30B22_0BAC_11D4_A76E_00000EB03267__INCLUDED_)
#define AFX_SXFTABLEMAPMANAGERC_H__16B30B22_0BAC_11D4_A76E_00000EB03267__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afx.h>
#include "SXFDataStructC.h"
#include "SXFStruct.h"

class SXFTableFeatureC;
class SXFPreDefColorC;
class SXFLayerC;
class SXFPart21FileWriteC;
class SXFInstanceIDC;
class SXFTableManagerC;
class SXFTableMapManagerC  
{
public:
    SXFTableMapManagerC();
	SXFTableMapManagerC(SXFPart21FileWriteC* IN_WriteFile,
						SXFInstanceIDC* m_InstanceIDManager);    
    virtual ~SXFTableMapManagerC();
	//WRITE
	void SetStructData(int IN_type,LPVOID IN_Struct);
	int WriteInstance(int* OUT_InstanceID);
	BOOL SetStructLayer(SXFLayerC* IN_Layer,int* OUT_InstanceID);
	//READ
	LPVOID GetStructData();
	void SetFeatureData(int IN_Type,LPVOID IN_Class);
	void SetStructPrecolor(int IN_Type,
							LPVOID IN_Struct,
							SXFPreDefColorC IN_Precolor);

private:
	SXFTableFeatureC*		m_LayerFeature;			/* ��`ð���̨�����޼ު�� */
	SXFInstanceIDC*			m_InstanceIDManager;	/* �ݽ�ݽID��޼ު�� */
	SXFPart21FileWriteC*	m_WriteFile;			/* ̧�ُo�͵�޼ު�� */
	SXFTableFeatureC*		m_TableFeature;			/* ��`ð���̨�����޼ު�� */
};

#endif // !defined(AFX_SXFTABLEMAPMANAGERC_H__16B30B22_0BAC_11D4_A76E_00000EB03267__INCLUDED_)
