/**
	All Rights Reserved,(c) JACIC 2001
	SXFTableMapManagerC.cpp								�쐬���F2000.4.14

	�P�D�N���X�T�v
	��`�e�[�u���t�B�[�`���I�u�W�F�N�g��Mapping�I�u�W�F�N�g���Ǘ�����N���X

	�Q�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.14			�{��(FQS)			�Ȃ��B

**/

#include "stdafx.h"
#include "SXFTableManagerC.h"
#include "SXFTableMapManagerC.h"
#include "SXFTableFeatureC.h"
#include "SXFPreDefColorC.h"
#include "SXFLayerC.h"
#include "SXFPart21FileWriteC.h"
#include "SXFInstanceIDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/**
	All Rights Reserved,(c) JACIC 2001
	SXFTableMapManagerC.cpp								�쐬���F2000.4.14

	�P�D�@�\�T�v
	�R���X�g���N�^

	�Q�D�C���^�[�t�F�[�X
		void	SXFTableMapManagerC::SXFTableMapManagerC()
		
	����	�F	�^		������				���e
		�Ȃ�

	�R�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.14			�{��(FQS)			�Ȃ��B

**/
SXFTableMapManagerC::SXFTableMapManagerC()
{
	m_TableFeature = NULL;
	m_LayerFeature = NULL;
	m_WriteFile = NULL;
	m_InstanceIDManager = NULL;
}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFTableMapManagerC.cpp								�쐬���F2000.4.14

	�P�D�@�\�T�v
	�R���X�g���N�^

	�Q�D�C���^�[�t�F�[�X

	�R�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.14			�{��(FQS)			�Ȃ��B

**/
SXFTableMapManagerC::SXFTableMapManagerC(SXFPart21FileWriteC* IN_WriteFile,
											SXFInstanceIDC* IN_InstanceIDManager)
{
	m_TableFeature = NULL;
	m_LayerFeature = NULL;
	m_WriteFile = IN_WriteFile;
	m_InstanceIDManager = IN_InstanceIDManager;
}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFTableMapManagerC.cpp								�쐬���F2000.4.14

	�P�D�@�\�T�v
		�f�X�g���N�^

	�Q�D�C���^�[�t�F�[�X

	�R�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.14			�{��(FQS)			�Ȃ��B

**/
SXFTableMapManagerC::~SXFTableMapManagerC()
{
	if (m_TableFeature != NULL)
		delete m_TableFeature;
	if (m_LayerFeature != NULL)
		delete m_LayerFeature;
}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFTableMapManagerC.cpp								�쐬���F2000.4.14

	�P�D�@�\�T�v
	�\���̂̐���

	�Q�D�C���^�[�t�F�[�X
	void SetStructData(int IN_type, LPVOID IN_Struct)

	����:	�^				������				���e
			int				IN_type				�e�[�u���^
			LPVOID			IN_Struct			�\����
	���A�l:
			�Ȃ�

	�R�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.14			�{��(FQS)			�Ȃ��B

**/
void SXFTableMapManagerC::SetStructData(int IN_type, LPVOID IN_Struct)
{
	/* ��`ð���̨�����޼ު�Đ��� */
	m_TableFeature = new SXFTableFeatureC(m_InstanceIDManager);
	/* ��`ð��ٍ\���̾�� */
	m_TableFeature->SetFeatureData(IN_type,IN_Struct);
}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFTableMapManagerC.cpp								�쐬���F2000.4.14

	�P�D�@�\�T�v
	�C���X�^���X���t�@�C���֏o�͂���

	�Q�D�C���^�[�t�F�[�X
	int WriteInstance(int* OUT_InstanceID)

	����:	�^		������			���e
			int*	OUT_InstanceID	�ݽ�ݽID

	���A�l	���펞�F0
			�ُ펞�F��(error_code)

	�R�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.14			�{��(FQS)			�Ȃ��B

**/
int SXFTableMapManagerC::WriteInstance(int* OUT_InstanceID)
{
	INSTANCEDATA* tablefeature;
	*OUT_InstanceID = -1;
	int error_code;

	/* �ݽ�ݽ�ް��擾 */
	tablefeature = m_TableFeature->GetFeatureData();
	/* �ݽ�ݽ�o�� */
	error_code = m_WriteFile->WriteFeatureInstance(tablefeature);
	if (error_code)
		return error_code;
	/* �ݽ�ݽID�擾 */
	*OUT_InstanceID = tablefeature->InstanceID;
	return 0;
}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFTableMapManagerC.cpp								�쐬���F2000.4.14

	�P�D�@�\�T�v
	����`�F�̍\���̂̐���(READ)

	�Q�D�C���^�[�t�F�[�X
	void SetStructPrecolor(int IN_Type, LPVOID IN_Struct, SXFPreDefColorC IN_Precolor)

	����:	�^				������			���e
			int				IN_Type			�e�[�u���^
			LPVOID			IN_Struct		�\����
			SXFPreDefColorC IN_Precolor		����`�F�N���X

	���A�l	���펞�FTRUE
			�ُ펞�FFALSE

	�R�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.14			�{��(FQS)			�Ȃ��B

**/
void SXFTableMapManagerC::SetStructPrecolor(int IN_Type, 
											LPVOID IN_Struct, 
											SXFPreDefColorC IN_Precolor)
{
	/* ��`ð���̨�����޼ު�Đ��� */
	m_TableFeature = new SXFTableFeatureC(m_InstanceIDManager);
	/* ��`ð��ٍ\���̾�� */
	m_TableFeature->SetFeatureData(IN_Type,IN_Struct);
}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFTableMapManagerC.cpp								�쐬���F2000.4.14

	�P�D�@�\�T�v
	���C���t�B�[�`���̍\���̂̐���(WRITE)

	�Q�D�C���^�[�t�F�[�X
	BOOL SXFTableMapManagerC::SetStructLayer(SXFLayerC *IN_Layer,int* OUT_InstanceID)

	����:	�^				������			���e
			SXFLayerC*		IN_Layer		���C���N���X
			int*			OUT_InstanceID	�C���X�^���XID
	���A�l:
			���펞�FTRUE
			�ُ펞�FFALSE

	�R�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.14			�{��(FQS)			�Ȃ��B

**/
BOOL SXFTableMapManagerC::SetStructLayer(SXFLayerC *IN_Layer,int* OUT_InstanceID){
	INSTANCEDATA* layerfeature;
	*OUT_InstanceID = -1;

	/* ڲ�̨�����޼ު�Đ��� */
	m_LayerFeature = new SXFTableFeatureC(m_InstanceIDManager);
	/* ڲԏ��� */
	m_LayerFeature->SetLayerFeature(IN_Layer);
	/* ڲԲݽ�ݽ�ް��擾 */
	layerfeature = m_LayerFeature->GetFeatureData();
	/* ڲԲݽ�ݽ�o�� */
	if (!m_WriteFile->WriteFeatureInstance(layerfeature))
		return FALSE;
	/* �ݽ�ݽID�擾 */
	*OUT_InstanceID = layerfeature->InstanceID;
	return TRUE;
}


/**
	All Rights Reserved,(c) JACIC 2001
	SXFTableMapManagerC.cpp								�쐬���F2000.4.14

	�P�D�@�\�T�v
	�\���̂̐���(READ)

	�Q�D�C���^�[�t�F�[�X
	void SetFeatureData(int IN_Type, LPVOID IN_Class)

	����:	�^				������		���e
			int				IN_Type		��`�e�[�u���^
			LPVOID			IN_Class	�\����

	���A�l	���펞�FTRUE
			�ُ펞�FFALSE

	�R�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.14			�{��(FQS)			�Ȃ��B

**/
void SXFTableMapManagerC::SetFeatureData(int IN_Type, LPVOID IN_Class)
{
	/* ��`ð���̨�����޼ު�Đ��� */
	m_TableFeature = new SXFTableFeatureC();
	/* ��`ð��ٍ\���̾�� */
	m_TableFeature->SetStructData(IN_Type,IN_Class);
}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFTableMapManagerC.cpp								�쐬���F2000.4.14

	�P�D�@�\�T�v
	�\���̂̎擾(READ)

	�Q�D�C���^�[�t�F�[�X
	LPVOID GetStructData()

	����:	�^				������		���e
			�Ȃ�

	���A�l	�\����

	�R�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.14			�{��(FQS)			�Ȃ��B

**/
LPVOID SXFTableMapManagerC::GetStructData()
{
	return m_TableFeature->GetStructData();
}
