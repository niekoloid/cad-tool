//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFPreDefColorC.cpp                    �쐬���F2000.04.16
//
//	�P�D�N���X�T�v
//      PreDefColor Instance Table Data���Ǘ�����
//
//	�Q�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.16     ��
//
//------------------------------------------------------------
#include "stdafx.h"
#include "SXFRGBTableC.h"
#include "SXFPreDefColorC.h"
#include "SXFTableMapManagerC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFPreDefColorC.cpp                    �쐬���F2000.04.16
//
//  �P�D�@�\�T�v
//      �N���X�\�z
//
//  �Q�D�C���^�[�t�F�[�X
//		void	SXFPreDefColorC::SXFPreDefColorC( )
//		
//	����	�F	�^		������				���e
//		�Ȃ�
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.16     ��
//
//------------------------------------------------------------
SXFPreDefColorC::SXFPreDefColorC( )
{
    //initialization 
    m_Code = -1;
    m_ID = -1;
    m_Name.Empty();
	m_MappingManager = NULL;
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFPreDefColorC.cpp                    �쐬���F2000.04.16
//
//  �P�D�@�\�T�v
//      �N���X����
//
//  �Q�D�C���^�[�t�F�[�X
//	void	SXFPreDefColorC::~SXFPreDefColorC()
//	
//	����:	�^						������				���e
//			�Ȃ�
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.16     ��
//
//------------------------------------------------------------
SXFPreDefColorC::~SXFPreDefColorC()
{
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFPreDefColorC.cpp                    �쐬���F2000.04.16
//
//  �P�D�@�\�T�v
//      Color Name�̐ݒ�iColor Code�����߂܂��j
//
//  �Q�D�C���^�[�t�F�[�X
//      BOOL SetName(LPCTSTR IN_Name)
//
//	    ����: �^			  ������			    ���e
//            LPCTSTR        IN_Name               ����`�F��
//
//	    ���A�l	
//            ���펞�FTRUE
//			  �ُ펞�FFALSE
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.16     ��
//
//------------------------------------------------------------
BOOL SXFPreDefColorC::SetName(LPCTSTR IN_Name)
{
	SXFRGBTableC RGBtable;
	if (!RGBtable.GetColorCode(IN_Name, m_Code ))
		return FALSE;
	m_Name = IN_Name;
	return TRUE;
}