/**
	All Rights Reserved,(c) JACIC 2001
	SXFWriteMappingManagerC.cpp								�쐬���F2000.4.14

	�P�D�N���X�T�v
	Write���̃t�B�[�`���I�u�W�F�N�g��Mapping�I�u�W�F�N�g�̊Ǘ����s���N���X�B

	�Q�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.14			�{��(FQS)			�Ȃ��B

**/

#include "stdafx.h"
#include "SXFWriteMappingManagerC.h"
#include "SXFWriteManagerC.h"
#include "SXFFeatureC.h"
#include "SXFPart21FileWriteC.h"
#include "SXFInstanceIDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/**
	All Rights Reserved,(c) JACIC 2001
	SXFWriteMappingManagerC.cpp								�쐬���F2000.4.14

	�P�D�@�\�T�v
	�R���X�g���N�^

	�Q�D�C���^�[�t�F�[�X
		void	SXFWriteMappingManagerC::SXFWriteMappingManagerC()
		
	����	�F	�^		������				���e
		�Ȃ�

	�R�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.14			�{��(FQS)			�Ȃ��B

**/
SXFWriteMappingManagerC::SXFWriteMappingManagerC()
{
	m_AssemType = -1;
	m_Feature = NULL;
	m_AsemFeature = NULL;
	m_WriteFile = NULL;
	m_InstanceIDManager = NULL;
}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFWriteMappingManagerC.cpp								�쐬���F2000.4.14

	�P�D�@�\�T�v
	�R���X�g���N�^

	�Q�D�C���^�[�t�F�[�X
		void	SXFWriteMappingManagerC::SXFWriteMappingManagerC(
											int IN_AssemType,
											 SXFPart21FileWriteC* IN_WriteFile,
											 SXFInstanceIDC* IN_InstanceIDManager)
		
	�����F�^					������					���e
		  int					IN_AssemType			�A�Z���u���^
		  SXFPart21FileWriteC*	IN_WriteFile			̧�ُo�͵�޼ު��
		  SXFInstanceIDC*		IN_InstanceIDManager	�ݽ�ݽID��޼ު��

	�R�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.14			�{��(FQS)			�Ȃ��B

**/
SXFWriteMappingManagerC::SXFWriteMappingManagerC(int IN_AssemType,
												 SXFPart21FileWriteC* IN_WriteFile,
												 SXFInstanceIDC* IN_InstanceIDManager)
{
	m_AssemType = IN_AssemType;
	m_WriteFile = IN_WriteFile;
	m_InstanceIDManager = IN_InstanceIDManager;
	m_AsemFeature = NULL;
	m_Feature = NULL;
}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFWriteMappingManagerC.cpp								�쐬���F2000.4.14

	�P�D�@�\�T�v
	�f�X�g���N�^

	�Q�D�C���^�[�t�F�[�X
		void	SXFWriteMappingManagerC::~SXFWriteMappingManagerC()
		
	����	�F	�^		������				���e
		�Ȃ�

	�R�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.14			�{��(FQS)			�Ȃ��B

**/
SXFWriteMappingManagerC::~SXFWriteMappingManagerC()
{
	if (m_AsemFeature != NULL)
		delete m_AsemFeature;
	if (m_Feature != NULL)
		delete 	m_Feature;
}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFWriteMappingManagerC.cpp								�쐬���F2000.4.14

	�P�D�@�\�T�v
	�\���̂�SET����

	�Q�D�C���^�[�t�F�[�X
	void SetStructData(int IN_Asem_Type, LPVOID IN_Struct)

	����:	�^				������				���e
			int				IN_Asem_Type		�A�Z���u���^
			LPVOID			IN_Struct			�\����

	���A�l:
			�Ȃ�

	�R�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.14			�{��(FQS)			�Ȃ��B

**/
void SXFWriteMappingManagerC::SetStructData(int IN_Asem_Type, LPVOID IN_Struct)
{
	//�A�Z���u���^�C�v�̃Z�b�g
	m_AssemType = IN_Asem_Type;
	switch(IN_Asem_Type){
		case 1://SHEET
			//�\���̂̃Z�b�g
		//	JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
			//strcpy(m_Sheet_Str.name,((Sheet_Struct*)IN_Struct)->name);
			strcpy_s(m_Sheet_Str.name,_countof(m_Sheet_Str.name),((Sheet_Struct*)IN_Struct)->name);
			m_Sheet_Str.orient = ((Sheet_Struct*)IN_Struct)->orient;
			m_Sheet_Str.type = ((Sheet_Struct*)IN_Struct)->type;
			m_Sheet_Str.x = ((Sheet_Struct*)IN_Struct)->x;
			m_Sheet_Str.y = ((Sheet_Struct*)IN_Struct)->y;
			break;
		case 2://subfigure
			//�\���̂̃Z�b�g
		//	JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
			//strcpy(m_Sfigorg_Str.name,((Sfigorg_Struct*)IN_Struct)->name);
			strcpy_s(m_Sfigorg_Str.name,_countof(m_Sfigorg_Str.name),((Sfigorg_Struct*)IN_Struct)->name);
			m_Sfigorg_Str.flag = ((Sfigorg_Struct*)IN_Struct)->flag;
			break;
		case 3://composite_curve
			//�\���̂̃Z�b�g
			m_CompCurve_Str.color = ((Ccurve_Org_Struct*)IN_Struct)->color;
			m_CompCurve_Str.type = ((Ccurve_Org_Struct*)IN_Struct)->type;
			m_CompCurve_Str.line_width = ((Ccurve_Org_Struct*)IN_Struct)->line_width;
			m_CompCurve_Str.flag = ((Ccurve_Org_Struct*)IN_Struct)->flag;
			break;
	}
}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFWriteMappingManagerC.cpp								�쐬���F2000.4.14

	�P�D�@�\�T�v
	�A�Z���u���v�f��Mapping

	�Q�D�C���^�[�t�F�[�X
	int MappingAssembly()

	����:	�^				������				���e
			�Ȃ�

	���A�l:
			���펞�F0
			�ُ펞�F��(error_code)

	�R�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.14			�{��(FQS)			�Ȃ��B

**/
int SXFWriteMappingManagerC::MappingAssembly()
{
	INSTANCEDATA* assemfeature;
	int error_code;

	/* ������̨�����޼ު�Đ��� */
	m_AsemFeature = new SXFFeatureC(m_InstanceIDManager);
	switch(m_AssemType){
		/** �p�� **/
		case 1:
			/* �����؍\���̾�� */
			m_AsemFeature->SetAssemblyData(m_AssemType,&m_Sheet_Str);
			break;
		/** �����}�` **/
		case 2:
			/* �����؍\���̾�� */
			m_AsemFeature->SetAssemblyData(m_AssemType,&m_Sfigorg_Str);
			break;
		/** �����Ȑ� **/
		case 3:
			/* �����؍\���̾�� */
			m_AsemFeature->SetAssemblyData(m_AssemType,&m_CompCurve_Str);
			break;
	}
	/* �ݽ�ݽ�ް��擾 */
	assemfeature = m_AsemFeature->GetFeatureData();
	/* ������̨����ݽ�ݽ�o�� */
	error_code = m_WriteFile->WriteFeatureInstance(assemfeature);
	return error_code;
}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFWriteMappingManagerC.cpp								�쐬���F2000.4.14

	�P�D�@�\�T�v
	�����o�̃f�[�^�N���A

	�Q�D�C���^�[�t�F�[�X
	void ClearData()
	����:	�^				������				���e
			�Ȃ��B
	���A�l	�Ȃ��B

	�R�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.14			�{��(FQS)			�Ȃ��B

**/
void SXFWriteMappingManagerC::ClearData()
{
	//////////////////
	//data clear
	//////////////////
	m_AssemType = -1;
	if (m_Feature){
		delete m_Feature;
		m_Feature=NULL;
	}
	if (m_AsemFeature){
		delete m_AsemFeature;
		m_AsemFeature=NULL;
	}
}
/**
	All Rights Reserved,(c) JACIC 2001
	SXFWriteMappingManagerC.cpp								�쐬���F2000.4.14

	�P�D�@�\�T�v
		�t�B�[�`���v�f��Mapping

	�Q�D�C���^�[�t�F�[�X
	int MappingFeature(char *IN_FeatureType, LPVOID IN_Struct,int &OUT_Id1)
	����:	�^		������				���e
			char*	IN_FeatureType		�t�B�[�`���^
			LPVOID	IN_Struct			�\����
			int&	OUT_Id1				��ʗv�f�̃C���X�^���XID

	���A�l:
			���펞:0
			�ُ펞:��(error_code)

	�R�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.14			�{��(FQS)			�Ȃ��B

**/
int SXFWriteMappingManagerC::MappingFeature(char *IN_FeatureType, LPVOID IN_Struct,int &OUT_Id1)
{
	INSTANCEDATA* feature;
	int error_code;

	/* �t�B�[�`���I�u�W�F�N�g���� **/
	m_Feature = new SXFFeatureC(m_InstanceIDManager);
	/* �\���̂̃Z�b�g */
	m_Feature->SetFeatureData(IN_FeatureType,IN_Struct);
	/* �ݽ�ݽ�ް��擾 */
	feature = m_Feature->GetFeatureData();
	/* ������̨����ݽ�ݽ�o�� */
	error_code = m_WriteFile->WriteFeatureInstance(feature);
	/* �ݽ�ݽID�擾 */
	OUT_Id1 = feature->InstanceID;
	return error_code;
}
