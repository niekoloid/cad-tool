//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFInstanceIDC.cpp                    �쐬���F2000.04.07
//
//	�P�D�N���X�T�v
//		�C���X�^���XID�̎擾���s��
//      
//	�Q�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.07    ��
//
//------------------------------------------------------------
#include "stdafx.h"
#include "SXFDataStructC.h"
#include "SXFInstanceIDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFInstanceIDC.cpp                    �쐬���F2000.04.07
//
//  �P�D�@�\�T�v
//      �N���X�\�z
//
//  �Q�D�C���^�[�t�F�[�X
//		void	SXFInstanceIDC::SXFInstanceIDC()
//		
//	����	�F	�^		������				���e
//		�Ȃ�
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.07    ��
//
//------------------------------------------------------------
SXFInstanceIDC::SXFInstanceIDC()
{

}
//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFInstanceIDC.cpp                    �쐬���F2000.04.07
//
//  �P�D�@�\�T�v
//      �N���X����
//  �Q�D�C���^�[�t�F�[�X
//		void	SXFInstanceIDC::~SXFInstanceIDC()
//		
//	����	�F	�^		������				���e
//		�Ȃ�
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.07    ��
//
//------------------------------------------------------------
SXFInstanceIDC::~SXFInstanceIDC()
{

}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFInstanceIDC.cpp                    �쐬���F2000.04.07
//
//  �P�D�@�\�T�v
//      �V����Instance ID��Ԃ�
//  �Q�D�C���^�[�t�F�[�X
//		int SXFInstanceIDC::GetNewInstanceID()
//
//	����	�F	�^		������				���e
//		�Ȃ�
//
//	    ���A�l	
//            int	A New Entity ID
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.07    ��
//
//------------------------------------------------------------

int SXFInstanceIDC::GetNewInstanceID()
{
    int NewID=-1;
    NewID = m_FeatureIDManager.Get_ID();
    return NewID;
}
