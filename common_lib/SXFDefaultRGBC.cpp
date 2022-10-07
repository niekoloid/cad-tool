/**
	All Rights Reserved,(c) JACIC 2001
	SXFDefaultRGBC.cpp                �쐬���F2000.04.29

	�P�D�N���X�T�v
		�F�e�[�u�������Ǘ�����

	�Q�D����
	    ����ԍ�    ���t��         �S����		�T�v
		�쐬		2000.4.29     �{��(FQS)
**/
#include "stdafx.h"
#include <math.h>
#include <string.h>
#include "SXFDefaultRGBC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/**
	All Rights Reserved,(c) JACIC 2001
	SXFDefaultRGBC.cpp                �쐬���F2000.04.29

  �P�D�@�\�T�v
      �N���X�\�z

  �Q�D�C���^�[�t�F�[�X
		void	SXFDefaultRGBC::SXFDefaultRGBC()
		
	����	�F	�^		������				���e
		�Ȃ�

  �R�D����
	    ����ԍ�    ���t��			�S����		 �T�v
	    �쐬		2000.04.29      �{��(FQS)
**/
SXFDefaultRGBC::SXFDefaultRGBC()
{

}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFDefaultRGBC.cpp                �쐬���F2000.04.29

  �P�D�@�\�T�v
      �f�X�g���N�^

  �Q�D�C���^�[�t�F�[�X
		void	SXFDefaultRGBC::~SXFDefaultRGBC()
		
	����	�F	�^		������				���e
		�Ȃ�

  �R�D����
	    ����ԍ�    ���t��			�S����		 �T�v
	    �쐬		2000.04.29      �{��(FQS)
**/
SXFDefaultRGBC::~SXFDefaultRGBC()
{

}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFDefaultRGBC.cpp                �쐬���F2000.04.29

  �P�D�@�\�T�v
      �N���X�\�z

  �Q�D�C���^�[�t�F�[�X
   void	SXFDefaultRGBC::SXFDefaultRGBC(int code,
										char *name, 
										int red,
										int green,
										int blue);
		
	����	�F	�^		������		���e
				int		code		�F�R�[�h
				char*	name		�F�� 
				int		red			R�l
				int		green		G�l
				int		blue		B�l

  �R�D����
	    ����ԍ�    ���t��			�S����		 �T�v
	    �쐬		2000.04.29      �{��(FQS)
**/
SXFDefaultRGBC::SXFDefaultRGBC(int code,
								char *name, 
								int red,
								int green,
								int blue){
	m_Code = code;
//	JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
//	strcpy(m_Name,name);
	strcpy_s(m_Name,_countof(m_Name),name);
	m_Red  = red;
	m_Green = green;
	m_Blue = blue;
}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFDefaultRGBC.cpp                �쐬���F2000.04.29

  �P�D�@�\�T�v
      �F�R�[�h�擾

  �Q�D�C���^�[�t�F�[�X
		int	SXFDefaultRGBC::GetCode()
		
	����	�F	�^		������				���e
			�Ȃ�
	���A�l
			int		m_Code		�F�R�[�h

  �R�D����
	    ����ԍ�    ���t��			�S����		 �T�v
	    �쐬		2000.04.29      �{��(FQS)
**/
int SXFDefaultRGBC::GetCode(){
	return m_Code;
}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFDefaultRGBC.cpp                �쐬���F2000.04.29

  �P�D�@�\�T�v
      �F���̎擾

  �Q�D�C���^�[�t�F�[�X
		void	SXFDefaultRGBC::GetName(char*& name)
		
	����	�F	�^		������		���e
				char*&	name		�F��

  �R�D����
	    ����ԍ�    ���t��			�S����		 �T�v
	    �쐬		2000.04.29      �{��(FQS)
**/
void SXFDefaultRGBC::GetName(char*& name){
	name = m_Name;
}
