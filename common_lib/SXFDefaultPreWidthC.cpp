/**
	All Rights Reserved,(c) JACIC 2001
	SXFDefaultPreWidthC.cpp                �쐬���F2000.04.29

	�P�D�N���X�T�v
		�����e�[�u�������Ǘ�����

	�Q�D����
	    ����ԍ�    ���t��         �S����		�T�v
		�쐬		2000.4.29     �{��(FQS)
**/
#include "stdafx.h"
#include "SXFDefaultPreWidthC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/**
	All Rights Reserved,(c) JACIC 2001
	SXFDefaultPreWidthC.cpp                �쐬���F2000.04.29

  �P�D�@�\�T�v
      �N���X�\�z

  �Q�D�C���^�[�t�F�[�X
		void	SXFPreWidthTableC::SXFPreWidthTableC()
		
	����	�F	�^		������				���e
		�Ȃ�

  �R�D����
	    ����ԍ�    ���t��			�S����		 �T�v
	    �쐬		2000.04.29      �{��(FQS)
**/
SXFDefaultPreWidthC::SXFDefaultPreWidthC()
{

}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFDefaultPreWidthC.cpp                �쐬���F2000.04.29

  �P�D�@�\�T�v
      �f�X�g���N�^

  �Q�D�C���^�[�t�F�[�X
		void	SXFPreWidthTableC::~SXFPreWidthTableC()
		
	����	�F	�^		������				���e
		�Ȃ�

  �R�D����
	    ����ԍ�    ���t��			�S����		 �T�v
	    �쐬		2000.04.29      �{��(FQS)
**/
SXFDefaultPreWidthC::~SXFDefaultPreWidthC()
{

}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFDefaultPreWidthC.cpp                �쐬���F2000.04.29

  �P�D�@�\�T�v
      �N���X�\�z

  �Q�D�C���^�[�t�F�[�X
		void	SXFPreWidthTableC::SXFPreWidthTableC(int in_code,
													double in_width)
		
	����	�F	�^		������		���e
				int		in_code		�����R�[�h
				double	in_width	����

  �R�D����
	    ����ԍ�    ���t��			�S����		 �T�v
	    �쐬		2000.04.29      �{��(FQS)
**/
SXFDefaultPreWidthC::SXFDefaultPreWidthC(int in_code,double in_width){
	m_Code = in_code;
    m_Width = in_width;
}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFDefaultPreWidthC.cpp                �쐬���F2000.04.29

  �P�D�@�\�T�v
      �����̎擾

  �Q�D�C���^�[�t�F�[�X
		void	SXFPreWidthTableC::GetWidth(double& out_width)
		
	����	�F	�^		������		���e
				double&	out_width	����

  �R�D����
	    ����ԍ�    ���t��			�S����		 �T�v
	    �쐬		2000.04.29      �{��(FQS)
**/
void SXFDefaultPreWidthC::GetWidth(double& out_width){
	out_width = m_Width;
}
