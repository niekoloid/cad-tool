/**
	All Rights Reserved,(c) JACIC 2001
	SXFReadMapManagerC.cpp								�쐬���F2000.4.25

	�P�D�N���X�T�v
	Read��(�t�B�[�`���R�����g�j�̃t�B�[�`���I�u�W�F�N�g��
						Mapping�I�u�W�F�N�g�̊Ǘ����s���N���X�B


	�Q�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.25			�{��(FQS)			�Ȃ��B

**/

#include "stdafx.h"
#include "SXFReadMapManagerC.h"
#include "SXFFeatureC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/**
	All Rights Reserved,(c) JACIC 2001
	SXFReadMapManagerC.cpp								�쐬���F2000.4.25

	�P�D�@�\�T�v
	�R���X�g���N�^

	�Q�D�C���^�[�t�F�[�X
		void	SXFReadMapManagerC::SXFReadMapManagerC()
		
	����	�F	�^		������				���e
		�Ȃ�

	�R�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.25			�{��(FQS)			�Ȃ��B

**/
SXFReadMapManagerC::SXFReadMapManagerC()
{
	m_Feature = NULL;
}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFReadMapManagerC.cpp								�쐬���F2000.4.25

	�P�D�@�\�T�v
	�f�X�g���N�^

	�Q�D�C���^�[�t�F�[�X
		void	SXFReadMapManagerC::~SXFReadMapManagerC()
		
	����	�F	�^		������				���e
		�Ȃ�

	�R�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.25			�{��(FQS)			�Ȃ��B

**/
SXFReadMapManagerC::~SXFReadMapManagerC()
{
	if (m_Feature != NULL)
		delete m_Feature;
}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFReadMapManagerC.cpp								�쐬���F2000.4.25

	�P�D�@�\�T�v
	�C���X�^���X�f�[�^�̐ݒ�

	�Q�D�C���^�[�t�F�[�X
	BOOL SXFReadMapManagerC::SetFeatureData(INSTANCEDATA *IN_Instance)

	����:	�^				������				���e
			INSTANCEDATA*	IN_Instance			�C���X�^���X�f�[�^

	���A�l	����I���FTRUE
			�ȏ�I���FFALSE

	�R�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.25			�{��(FQS)			�Ȃ��B

**/
BOOL SXFReadMapManagerC::SetFeatureData(INSTANCEDATA *IN_Instance)
{
	/* ̨�����޼ު�Đ��� */
	m_Feature = new SXFFeatureC();
	/* �ݽ�ݽ�ް���� */
	return m_Feature->SetStructData(IN_Instance);
}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFReadMapManagerC.cpp								�쐬���F2000.4.25

	�P�D�@�\�T�v
	��ʗv�f�t�B�[�`���̍\���̎擾

	�Q�D�C���^�[�t�F�[�X
	LPVOID GetStructData(char* &OUT_TypeName)

	����:	�^			������				���e
			char*&		OUT_TypeName		�t�B�[�`���^
			size_t		TypeNameSize		�o�b�t�@�T�C�Y

	���A�l	�\����

	�R�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.25			�{��(FQS)			�Ȃ��B
	�X�V			2015.04.27			T.Matsushima		JPCERT/CC �w�E �Ǝ㐫�Ή�

**/
//LPVOID SXFReadMapManagerC::GetStructData(char* &OUT_TypeName)
LPVOID SXFReadMapManagerC::GetStructData(char* &OUT_TypeName,size_t TypeNameSize)
{
	return m_Feature->GetStructData(OUT_TypeName,TypeNameSize);
}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFReadMapManagerC.cpp								�쐬���F2000.4.25

	�P�D�@�\�T�v
	�A�Z���u���t�B�[�`���̍\���̎擾

	�Q�D�C���^�[�t�F�[�X
	LPVOID GetAssemblyStructData()

	����:	�^				������				���e
			�Ȃ��B

	���A�l	�\����

	�R�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.25			�{��(FQS)			�Ȃ��B

**/
LPVOID SXFReadMapManagerC::GetAssemblyStructData()
{
	return m_Feature->GetAssemblyStructData();

}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFReadMapManagerC.cpp                   �쐬���F2001.03.21

  �P�D�@�\�T�v
      �t�B�[�`���\���̕ԋp�ς݃t���O��ON�ɂ���
      
  �Q�D�C���^�[�t�F�[�X
      void SetReturnFlag()

	    ����: �^		������		���e
			  �Ȃ�

	    ���A�l	
			  �Ȃ�

  �R�D����
	    ����ԍ�    ���t��         �S����    �T�v
      �쐬		2001.03.21     �{��

**/
void SXFReadMapManagerC::SetReturnFlag()
{
	m_Feature->SetReturnFlag();
}
