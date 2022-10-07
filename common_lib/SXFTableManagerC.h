//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFTableManagerC.h                    �쐬���F2000.04.10
// 
//	�P�D�N���X�T�v
//      ��`�e�[�u���f�[�^�l�ƒ�`�e�[�u��Mapping�Ǘ�
//      �I�u�W�F�N�g�̃A�h���X��ێ����A��`�e�[�u��
//      Mapping�Ǘ��I�u�W�F�N�g���Ǘ�����
//
//	�Q�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.10     ��
//
//------------------------------------------------------------
#ifndef _SXFTABLEMANAGERC_H_
#define _SXFTABLEMANAGERC_H_

#include <afxtempl.h>

#include "SXFLayerC.h"
#include "SXFPreDefFontC.h"
#include "SXFUserDefFontC.h"
#include "SXFPreDefColorC.h"
#include "SXFUserDefColorC.h"
#include "SXFWidthC.h"
#include "SXFTextFontC.h"
#include "SXFDataStructC.h"
#include "SXFComFunctionC.h"

class SXFComInfoC;
class SXFPart21FileWriteC;
class SXFInstanceIDC;

class SXFTableManagerC  : public SXFComFunctionC
{
public:
	SXFTableManagerC();
	SXFTableManagerC(SXFComInfoC* IN_CommonInfo);
	SXFTableManagerC(SXFComInfoC* IN_CommonInfo,
						SXFPart21FileWriteC* IN_WriteFile,
						SXFInstanceIDC* IN_InstanceIDManager);
	SXFTableManagerC(SXFComInfoC* IN_CommonInfo,SXFInstanceIDC* IN_InstanceIDManager);
	virtual ~SXFTableManagerC();
	int RegisterStructTable( int IN_Type, LPVOID IN_Struct);
    int GetID(int IN_Type, int IN_Code);
    BOOL CheckSameLayer( LPCTSTR IN_Name);
    BOOL CheckSamePreDefColor( LPCTSTR IN_Name);
    BOOL CheckSamePreDefFont( LPCTSTR IN_Name);
    BOOL CheckSameUserDefFont( LPCTSTR IN_Name);
    BOOL CheckSameWidth( double IN_Width);
    BOOL CheckSameTextFont( LPCTSTR IN_Name);
    void LayerMapping();
	BOOL RegisterFeatureTable( INSTANCEDATA *IN_Instance );
 	BOOL GetTableElement(int IN_Type, LPVOID OUT_Struct, int* OUT_EndFlg);

private:
    CArray<SXFLayerC,SXFLayerC&>                m_LayerTable;				/* ڲ�ð��� */
    SXFPreDefFontC                              m_PreDefFontTable[16];		/* ����`����ð��� */
    CArray<SXFUserDefFontC, SXFUserDefFontC&>   m_UserDefFontTable;			/* հ�ޒ�`����ð��� */
    SXFPreDefColorC                             m_PreDefColorTable[16];		/* ����`�Fð��� */
    CArray<SXFUserDefColorC, SXFUserDefColorC&> m_UserDefColorTable;		/* հ�ޒ�`�Fð��� */
    SXFWidthC                                   m_WidthTable[16];			/* ����ð��� */
	CArray<SXFTextFontC, SXFTextFontC&>         m_TextFontTable;			/* ����̫��ð��� */
	SXFPart21FileWriteC*						m_WriteFile;				/* ̧�ُo�͵�޼ު�� */
    SXFComInfoC*								m_ComInfo;					/* ���ʏ��Ǘ���޼ު�� */
    SXFInstanceIDC*								m_InstanceIDManager;		/* �ݽ�ݽID��޼ު�� */
	BOOL										m_LayerFirstFlag;			/* ڲ��׸� */
    int											m_CurrentType;				/* ���ݏ�������ð��ٌ^ */
    int											m_CurrentNumber;			/* ���ݏ�������ð��ٲ��ޯ�� */
    int											m_PreDefWidthFlagTable[10];	/* �����׸�ð��� */
	int											userdefwidthcode;			/* �������� */
};

#endif
