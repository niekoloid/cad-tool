/**
	All Rights Reserved,(c) JACIC 2001
	SXFDefaultPreLineTypeC.cpp                �쐬���F2000.04.29

	�P�D�N���X�T�v
		����e�[�u�������Ǘ�����

	�Q�D����
	    ����ԍ�    ���t��         �S����		�T�v
		�쐬		2000.4.29     �{��(FQS)
**/
#include "stdafx.h"
#include <string.h>
#include "SXFDefaultPreLineTypeC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/**
	All Rights Reserved,(c) JACIC 2001
	SXFDefaultPreLineTypeC.cpp                �쐬���F2000.04.29

  �P�D�@�\�T�v
      �N���X�\�z

  �Q�D�C���^�[�t�F�[�X
		void	SXFDefaultPreLineTypeC::SXFDefaultPreLineTypeC()
		
	����	�F	�^		������				���e
				�Ȃ�

  �R�D����
	    ����ԍ�    ���t��			�S����		 �T�v
	    �쐬		2000.04.29      �{��(FQS)
**/
SXFDefaultPreLineTypeC::SXFDefaultPreLineTypeC()
{

}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFDefaultPreLineTypeC.cpp                �쐬���F2000.04.29

  �P�D�@�\�T�v
      �N���X�\�z

  �Q�D�C���^�[�t�F�[�X
	void	SXFDefaultPreLineTypeC::SXFDefaultPreLineTypeC(int in_code,
														const char* in_name)
		
	����	�F	�^		������		���e
				int		in_code		����R�[�h
				char*	in_name		���햼

  �R�D����
	    ����ԍ�    ���t��			�S����		 �T�v
	    �쐬		2000.04.29      �{��(FQS)
**/
SXFDefaultPreLineTypeC::SXFDefaultPreLineTypeC(int in_code, const char *in_name)
{
	m_Code = in_code;
//	JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
//	strcpy(m_Name,in_name);
	strcpy_s(m_Name,_countof(m_Name),in_name);
}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFDefaultPreLineTypeC.cpp                �쐬���F2000.04.29

  �P�D�@�\�T�v
      �f�X�g���N�^

  �Q�D�C���^�[�t�F�[�X
		void	SXFDefaultPreLineTypeC::~SXFDefaultPreLineTypeC()
		
	����	�F	�^		������				���e
		�Ȃ�

  �R�D����
	    ����ԍ�    ���t��			�S����		 �T�v
	    �쐬		2000.04.29      �{��(FQS)
**/
SXFDefaultPreLineTypeC::~SXFDefaultPreLineTypeC()
{

}
    
/**
	All Rights Reserved,(c) JACIC 2001
	SXFDefaultPreLineTypeC.cpp                �쐬���F2000.04.29

  �P�D�@�\�T�v
      ���햼�̎擾

  �Q�D�C���^�[�t�F�[�X
		void	SXFDefaultPreLineTypeC::GetName(char*& out_name)
		
	����	�F	�^		������		���e
				char*	out_name	���햼

  �R�D����
	    ����ԍ�    ���t��			�S����		 �T�v
	    �쐬		2000.04.29      �{��(FQS)
**/
void SXFDefaultPreLineTypeC::GetName(char*& out_name)
{
	out_name = m_Name;
}    

/**
	All Rights Reserved,(c) JACIC 2001
	SXFDefaultPreLineTypeC.cpp                �쐬���F2000.04.29

  �P�D�@�\�T�v
      ����R�[�h�̎擾

  �Q�D�C���^�[�t�F�[�X
		int	SXFDefaultPreLineTypeC::GetCode()
		
	����	�F	�^		������		���e
				�Ȃ�
	���A�l
		int		m_Code		����R�[�h

  �R�D����
	    ����ԍ�    ���t��			�S����		 �T�v
	    �쐬		2000.04.29      �{��(FQS)
**/
int SXFDefaultPreLineTypeC::GetCode()
{
	return m_Code;
}
