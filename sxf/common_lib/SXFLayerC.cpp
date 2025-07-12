//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFLayerC.cpp                           �쐬���F2000.04.16
//
//	�P�D�N���X�T�v
//      Layer Instance Table Data���Ǘ�����
//
//	�Q�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.16     ��
//
//------------------------------------------------------------
#include "stdafx.h"
#include "SXFLayerC.h"
#include "SXFTableMapManagerC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFLayerC.cpp                           �쐬���F2000.04.16
//
//  �P�D�@�\�T�v
//      �N���X�\�z
//
//  �Q�D�C���^�[�t�F�[�X
//		void	SXFLayerC::SXFLayerC()
//		
//	����	�F	�^		������				���e
//		�Ȃ�
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.16     ��
//
//------------------------------------------------------------
SXFLayerC::SXFLayerC()
{
	//initialization 
	m_Code = -1;
	m_ID = -1;
	m_Name.Empty();
	m_LfFlag = -1;
	m_MappingManager = NULL;
}
//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFLayerC.cpp                           �쐬���F2000.04.16
//
//  �P�D�@�\�T�v
//      �N���X����
//
//  �Q�D�C���^�[�t�F�[�X
//		void	SXFLayerC::~SXFLayerC()
//		
//	����	�F	�^		������				���e
//		�Ȃ�
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.16     ��
//
//------------------------------------------------------------
SXFLayerC::~SXFLayerC()
{
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFLayerC.cpp                           �쐬���F2000.04.16
//
//  �P�D�@�\�T�v
//      Overload the preprocessor symbol "="
//
//  �Q�D�C���^�[�t�F�[�X
//		SXFLayerC& SXFLayerC::operator=(const SXFLayerC &IN_Layer)
//		
//	����	�F	�^			������		���e
//				SXFLayerC&  IN_Layer	���C���I�u�W�F�N�g�̃A�h���X
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.16     ��
//
//------------------------------------------------------------
SXFLayerC& SXFLayerC::operator=(const SXFLayerC &IN_Layer)
{
	m_Code = IN_Layer.m_Code;
	m_ID = IN_Layer.m_ID;
	m_Name = IN_Layer.m_Name;
	m_LfFlag = IN_Layer.m_LfFlag;
	m_MappingManager = IN_Layer.m_MappingManager;
	return *this;

}
