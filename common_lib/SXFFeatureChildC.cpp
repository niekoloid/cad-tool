//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFFeatureChildC.cpp                  �쐬���F2000.04.20
//
//	�P�D�N���X�T�v
//      Feature Child Data���Ǘ�����
//      
//	�Q�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.20    ��
//
//------------------------------------------------------------

#include "stdafx.h"
#include "SXFFeatureChildC.h"
#include "SXFReadMapManagerC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFFeatureChildC.cpp                  �쐬���F2000.04.20
//
//  �P�D�@�\�T�v
//      �R���X�g���N�^
//
//  �Q�D�C���^�[�t�F�[�X
//		void	SXFFeatureChildC::SXFFeatureChildC()
//		
//	����	�F	�^		������				���e
//		�Ȃ�
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.20    ��
//
//------------------------------------------------------------

SXFFeatureChildC::SXFFeatureChildC()
{
	ChildID=-1;
	ChildMapManager=NULL;

}
//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFFeatureChildC.cpp                  �쐬���F2000.04.20
//
//  �P�D�@�\�T�v
//      �f�X�g���N�^
//  �Q�D�C���^�[�t�F�[�X
//		void	SXFFeatureChildC::~SXFFeatureChildC()
//		
//	����	�F	�^		������				���e
//		�Ȃ�
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.20    ��
//
//------------------------------------------------------------
SXFFeatureChildC::~SXFFeatureChildC()
{
	if(ChildMapManager!=NULL)
		delete ChildMapManager;
}
