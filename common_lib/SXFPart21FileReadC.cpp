//---------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFPart21FileReadC.cpp	              �쐬���F2000.03.26
//
//	�P�D�N���X�T�v
//      �t�@�C���̓��͂��Ǘ�����
//
//	�Q�D����
//		����ԍ�	���t��		 �S����	    �T�v
//		�쐬		2000.03.26   ��
//		�X�V		2002.02.20	K.Naono		�w�b�_��͏����̉��P�Ή�
//
//---------------------------------------------------------

#include "stdafx.h"
#include "SXFDataStructC.h"
//	MOD(S)	�w�b�_��͏����̉��P�Ή�	K.Naono		02.02.20
//#include "SXFPart21FileC.h"
#include "SXFPart21FileExC.h"
//	MOD(E)	�w�b�_��͏����̉��P�Ή�	K.Naono		02.02.20
#include "SXFPart21FileReadC.h"
#include "SXFTableManagerC.h"
#include "SXFReadFeatureManagerC.h"
#include "SXFErrorMsgC.h"
#include "SXFComInfoC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------
//	All Rights Reserved,(c)JACIC 2001
//	SXFPart21FileReadC.cpp	              �쐬���F2000.03.26
//
//	�P�D�@�\�T�v
//		�R���X�g���N�^
//
//	�Q�D�C���^�[�t�F�C�X
//		void	SXFPart21FileReadC::SXFPart21FileReadC()
//		
//	����	�F	�^		������				���e
//		�Ȃ�
//      
//	���A�l�F�Ȃ�
//
//	�R�D����
//		����ԍ�	���t��		 �S����	    �T�v
//		�쐬		2000.03.26   ��
//---------------------------------------------------------
SXFPart21FileReadC::SXFPart21FileReadC()
{
    //initialization
    m_HeadSection.Level=-1;
    m_HeadSection.Mode=-1;
    m_HeadSection.Author.Empty();
    m_HeadSection.FileName.Empty();
    m_HeadSection.Organization.Empty();
    m_HeadSection.Version.Empty();
    m_HeadSection.OriginatingSystem.Empty();
    ClearInstanceData();
    m_File = NULL;
    m_TableManager = NULL;
	m_ReadFeatureManager = NULL;
	m_ComInfo = NULL;
  
}

//---------------------------------------------------------
//	All Rights Reserved,(c)JACIC 2001
//	SXFPart21FileReadC.cpp	              �쐬���F2000.03.26
//
//	�P�D�@�\�T�v
//		�R���X�g���N�^
//
//	�Q�D�C���^�[�t�F�C�X
//		void	SXFPart21FileReadC::SXFPart21FileReadC(
//								SXFTableManagerC* IN_TableManager,
//								SXFReadFeatureManagerC* IN_ReadFeatureManager,
//								SXFComInfoC* IN_ComInfo)
//
//	�����F�^				������				���e
//		SXFTableManagerC*	IN_TableManager		��`ð��يǗ���޼ު�Ă̱��ڽ
//		SXFReadFeatureManagerC* IN_ReadFeatureManager	Read�Ǘ���޼ު�Ă̱��ڽ
//		SXFComInfoC*		IN_ComInfo			���ʏ���޼ު�Ă̱��ڽ
//      
//	���A�l�F�Ȃ�
//
//	�R�D����
//		����ԍ�	���t��		 �S����	    �T�v
//		�쐬		2000.03.26   ��
//---------------------------------------------------------
SXFPart21FileReadC::SXFPart21FileReadC(SXFTableManagerC* IN_TableManager,
							   SXFReadFeatureManagerC* IN_ReadFeatureManager,
                               SXFComInfoC* IN_ComInfo)
{
    //initialization
    m_HeadSection.Level=-1;
    m_HeadSection.Mode=-1;
    m_HeadSection.Author.Empty();
    m_HeadSection.FileName.Empty();
    m_HeadSection.Organization.Empty();
    m_HeadSection.Version.Empty();
    m_HeadSection.OriginatingSystem.Empty();
    ClearInstanceData();
    m_File = NULL;
    m_TableManager = IN_TableManager; 
	m_ReadFeatureManager = IN_ReadFeatureManager;
	m_ComInfo = IN_ComInfo;
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFPart21FileReadC.cpp	              �쐬���F2000.03.26
//
//  �P�D�@�\�T�v
//      �f�X�g���N�^
//
//  �Q�D�C���^�[�t�F�[�X
//		void	SXFPart21FileReadC::~SXFPart21FileReadC()
//		
//	����	�F	�^		������				���e
//		�Ȃ�
//      
//	���A�l�F�Ȃ�
//
//  �R�D����
//		����ԍ�	���t��		 �S����	    �T�v
//		�쐬		2000.03.26   ��
//
//------------------------------------------------------------

SXFPart21FileReadC::~SXFPart21FileReadC()
{
    if(m_File != NULL)
        delete m_File;
}
//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFPart21FileReadC.cpp	              �쐬���F2000.03.26
//
//  �P�D�@�\�T�v
//      �t�@�C���̃I�[�v��
//
//  �Q�D�C���^�[�t�F�[�X
//      int OpenPart21ReadFile( LPCTSTR IN_FileName )
//	    ����: �^			  ������			    ���e
//            LPCTSTR         IN_FileName          FileName
//      
//	    ���A�l	
//            ���펞�F 1: OK
//			  �ُ펞�F ��(�G���[�R�[�h)
//
//  �R�D����
//		����ԍ�	���t��		 �S����	    �T�v
//		�쐬		2000.03.26   ��
//		�X�V		2002.02.20	K.Naono		�w�b�_��͏����̉��P�Ή�
//
//------------------------------------------------------------
int SXFPart21FileReadC::OpenPart21ReadFile( LPCTSTR IN_FileName )
{
	int result_readinstance;

    TRY
    {
//	MOD(S)	�w�b�_��͏����̉��P�Ή�	K.Naono		02.02.20
//		m_File = new SXFPart21FileC(IN_FileName,
		m_File = new SXFPart21FileExC(IN_FileName,
//	MOD(E)	�w�b�_��͏����̉��P�Ή�	K.Naono		02.02.20
								CFile::modeRead | CFile::shareExclusive);
    }
    CATCH( CFileException, e )
    {
		/* �w�肳�ꂽ�t�@�C���܂��̓f�B���N�g����������܂��� */
        if (e->m_cause == CFileException::fileNotFound ){
			SXFErrorMsgC::RecordError(SXFFILEDIRECTORY,"",1,IN_FileName);
			return SXFFILEDIRECTORY;
        }
		/* STEP�t�@�C���̃I�[�v���Ɏ��s���܂��� */
		else{
			SXFErrorMsgC::RecordError(SXFNOTOPENSTEPFILE,"",1,IN_FileName);
			return SXFNOTOPENSTEPFILE;
        }

    }
    END_CATCH
    
    int result_readhead = m_File->ReadHeadSection(&m_HeadSection);
    if (result_readhead == -3){
		////can not find header
		SXFErrorMsgC::RecordError(SXFNOTHEADER,"",1,IN_FileName);
		return SXFNOTHEADER;
    }
	if (result_readhead < 0 ){
		////,�t�@�C���̃w�b�_��񂪓ǎ��܂���B
		SXFErrorMsgC::RecordError(SXFHEADERERR,"",0);
		result_readhead = 0;
    }

	/* SCADEC�ȊO��̧�� */
	if (result_readhead == 0){
		m_HeadSection.Author="";
		m_HeadSection.FileName=IN_FileName;
		m_HeadSection.Level = 2;
		m_HeadSection.Mode = 2;
		m_HeadSection.Organization="";
		m_HeadSection.OriginatingSystem="";
		m_HeadSection.Version="";
		m_HeadSection.scadec_flg = -1;
	}
	/** �t�@�C���̏���o�^ **/
	int ret = m_ComInfo->SetFileInfo(m_HeadSection);
	if (ret < 0)
		return ret;
    while(1){
        result_readinstance = m_File->ReadInstance(&m_InstanceData);
        if ( result_readinstance ==1 ){
			switch (m_InstanceData.InstanceMode){
				case SXF_IM_FT_ENTITY:
					RegisterFeatureEntity(&m_InstanceData);
					break;
				case SXF_IM_FT_TABLE:
					RegisterFeatureTable(&m_InstanceData);
					break;
				case SXF_IM_FT_ASSEMBLY:
					RegisterFeatureAssembly(&m_InstanceData);
					break;
				default:
					break;
			}
			ClearInstanceData();//init instance data
		}
        else if(result_readinstance == -2)
			//found syntax error
			continue;			//next line 
		else if(  result_readinstance == -4  ){
			//can not to find a feature instance in this file
			SXFErrorMsgC::RecordError(SXFERRORFILE,"",0);
			return SXFERRORFILE;
		}
		else if(result_readinstance == -1)
			//if end of file then break while(1) and return TRUE
			break;
		else
			break;
    }
    return 1;
}
//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFPart21FileReadC.cpp	              �쐬���F2000.03.26
//
//  �P�D�@�\�T�v
//      �t�@�C���̃N���[�Y
//
//  �Q�D�C���^�[�t�F�[�X
//      void ClosePart21ReadFile(  )
//
//	    ����:	�^			  ������			    ���e
//				�Ȃ�
//      
//	    ���A�l	
//				�Ȃ�
//
//  �R�D����
//		����ԍ�	���t��		 �S����	    �T�v
//		�쐬		2000.03.26   ��
//
//------------------------------------------------------------
void SXFPart21FileReadC::ClosePart21ReadFile(  )
{
    m_File->Close();
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFPart21FileReadC.cpp	              �쐬���F2000.03.26
//
//  �P�D�@�\�T�v
//      Feature Comment Entity�̓o�^
//
//  �Q�D�C���^�[�t�F�[�X
//      BOOL RegisterFeatureEntity(INSTANCEDATA *IN_Instance)
//
//	    ����: �^			  ������			    ���e
//            INSTANCEDATA*   IN_Instance          Instance��
//                                                 �\���̂̃A�h���X 
//	    ���A�l	
//            ���펞�F TRUE
//			  �ُ펞�F FALSE
//
//  �R�D����
//		����ԍ�	���t��		 �S����	    �T�v
//		�쐬		2000.03.26   ��
//
//------------------------------------------------------------
BOOL SXFPart21FileReadC::RegisterFeatureEntity(INSTANCEDATA *IN_Instance)
{
    if(! m_ReadFeatureManager->RegisterFeatureEntity(IN_Instance))
        return FALSE;
    return TRUE;
}
//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFPart21FileReadC.cpp	              �쐬���F2000.03.26
//
//  �P�D�@�\�T�v
//      Feature Comment Table�̓o�^
//
//  �Q�D�C���^�[�t�F�[�X
//      BOOL RegisterFeatureTable(INSTANCEDATA *IN_Instance)
//
//	    ����: �^			  ������			    ���e
//            INSTANCEDATA*   IN_Instance          Instance��
//                                                 �\���̂̃A�h���X 
//	    ���A�l	
//            ���펞�F TRUE
//			  �ُ펞�F FALSE
//
//  �R�D����
//		����ԍ�	���t��		 �S����	    �T�v
//		�쐬		2000.03.26   ��
//
//------------------------------------------------------------
BOOL SXFPart21FileReadC::RegisterFeatureTable(INSTANCEDATA *IN_Instance)
{
    if(! m_TableManager->RegisterFeatureTable(IN_Instance))
        return FALSE;
    return TRUE;
}
//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFPart21FileReadC.cpp	              �쐬���F2000.03.26
//
//  �P�D�@�\�T�v
//      Feature Assembly Instance�̓o�^
//
//  �Q�D�C���^�[�t�F�[�X
//      BOOL RegisterFeatureAssembly(INSTANCEDATA *IN_Instance)
//
//	    ����: �^			  ������			    ���e
//            INSTANCEDATA*   IN_Instance          Instance��
//                                                 �\���̂̃A�h���X 
//	    ���A�l	
//            ���펞�F TRUE
//			  �ُ펞�F FALSE
//
//  �Q�D�C���^�[�t�F�[�X
//
//  �R�D����
//		����ԍ�	���t��		 �S����	    �T�v
//		�쐬		2000.03.26   ��
//
//------------------------------------------------------------
BOOL SXFPart21FileReadC::RegisterFeatureAssembly(INSTANCEDATA *IN_Instance)
{
    if(! m_ReadFeatureManager->RegisterFeatureAssembly(IN_Instance))
        return FALSE;
    return TRUE;
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFPart21FileReadC.cpp	              �쐬���F2000.03.26
//
//  �P�D�@�\�T�v
//      Head Section Data�̎擾
//
//  �Q�D�C���^�[�t�F�[�X
//      void GetHeadData(int *OUT_Level,
//                       int *OUT_Mode,
//                       char *OUT_FileName,
//                       char *OUT_Author,
//                       char *OUT_Organization,
//                       char *OUT_Version,
//                       char *OUT_OriginatingSystem )
//
//	    ����: �^			  ������					���e
//            int*            OUT_Level					���x��
//            int*            OUT_Mode					���[�h
//            char*           OUT_FileName				�t�@�C����
//            char*           OUT_Author				�t�@�C���쐬��
//            char*           OUT_Organization			�쐬�ҏ���
//            char*           OUT_Version				���ʃ��C�u�����o�[�W����
//            char*           OUT_OriginatingSystem		�g�����X���[�^��
//
//	    ���A�l:	
//            �Ȃ�
//
//  �R�D����
//		����ԍ�	���t��		 �S����	    �T�v
//		�쐬		2000.03.26   ��
//
//------------------------------------------------------------
void SXFPart21FileReadC::GetHeadData(int *OUT_Level,
                                     int *OUT_Mode,
                                     char *OUT_FileName,
                                     char *OUT_Author,
                                     char *OUT_Organization,
                                     char *OUT_Version,
                                     char *OUT_OriginatingSystem )
{
    *OUT_Level = m_HeadSection.Level;
    *OUT_Mode = m_HeadSection.Mode;

//	MOD(S)	JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
	//strcpy(OUT_FileName,m_HeadSection.FileName);
	//strcpy(OUT_Author,m_HeadSection.Author);
	//strcpy(OUT_Organization,m_HeadSection.Organization);
	//strcpy(OUT_Version,m_HeadSection.Version);
	//strcpy(OUT_OriginatingSystem,m_HeadSection.OriginatingSystem);

	// �e���ڂ̃o�b�t�@�T�C�Y�͎d�l�����擾
	strcpy_s(OUT_FileName, 257,m_HeadSection.FileName);
	strcpy_s(OUT_Author, 257,m_HeadSection.Author);
	strcpy_s(OUT_Organization, 257,m_HeadSection.Organization);
	strcpy_s(OUT_Version, 257,m_HeadSection.Version);
	strcpy_s(OUT_OriginatingSystem, 257,m_HeadSection.OriginatingSystem);
//	MOD(E)	JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFPart21FileReadC.cpp	              �쐬���F2000.03.26
//
//  �P�D�@�\�T�v
//      Clear current instance data struct
//
//  �Q�D�C���^�[�t�F�[�X
//       void ClearInstanceData()
//
//		����	�F	�^		������				���e
//					�Ȃ�
//
//  �R�D����
//		����ԍ�	���t��		 �S����	    �T�v
//		�쐬		2000.03.26   ��
//
//------------------------------------------------------------
void SXFPart21FileReadC::ClearInstanceData()
{
    //init  m_InstanceData;
    m_InstanceData.InstanceMode = 0;
    m_InstanceData.InstanceID = 0;
    m_InstanceData.EntityName.Empty();
    m_InstanceData.EntityData.Empty();
}
