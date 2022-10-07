//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFWriteManagerC.cpp                    �쐬���F2000.04.18
//
//	�P�D�N���X�T�v
//      �o�͎��̃A�Z���u���Ԃ̎Q�Ɗ֌W���Ǘ�����
//
//	�Q�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.18    ��
//
//------------------------------------------------------------

#include "stdafx.h"
#include "SXFWriteManagerC.h"
#include "SXFErrorMsgC.h"
#include "SXFPart21FileWriteC.h"
#include "SXFInstanceIDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFWriteManagerC.cpp                    �쐬���F2000.04.18
//
//  �P�D�@�\�T�v
//      �N���X�\�z
//
//  �Q�D�C���^�[�t�F�[�X
//		void	SXFWriteManagerC::SXFWriteManagerC()
//		
//	����	�F	�^		������				���e
//		�Ȃ�
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.18    ��
//
//------------------------------------------------------------
SXFWriteManagerC::SXFWriteManagerC()
{
    //initialization
    m_ChildrenArray = NULL;
    m_CurrentAssembly = NULL;
    m_SheetAssemblyFlag=FALSE;
	m_CurrentChild = NULL;
    m_FirstAssemblyFlag=TRUE;
	m_AssemType = -1;
	m_SfigFlag = -1;
	m_SfigTableIndex = 0;
	m_AssemblyCode = 1;
	m_CurveFlag = 0;
	m_ErrorFlag = FALSE;
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFWriteManagerC.cpp                    �쐬���F2000.04.18
//
//  �P�D�@�\�T�v
//      �N���X�\�z
//
//  �Q�D�C���^�[�t�F�[�X
//		void	SXFWriteManagerC::SXFWriteManagerC(
//								SXFPart21FileWriteC* IN_WriteFile,
//								SXFInstanceIDC* IN_InstanceIDManager)
//
//		
//	�����F�^					������					���e
//		  SXFPart21FileWriteC*	IN_WriteFile			̧�ُo�͵�޼ު��
//		  SXFInstanceIDC*		IN_InstanceIDManager	�ݽ�ݽID��޼ު��
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.18    ��
//
//------------------------------------------------------------
SXFWriteManagerC::SXFWriteManagerC(SXFPart21FileWriteC* IN_WriteFile,
									SXFInstanceIDC* IN_InstanceIDManager)
{
    //initialization
    m_ChildrenArray = NULL;
    m_CurrentAssembly = NULL;
	m_SheetAssemblyFlag=FALSE;
	m_CurrentChild = NULL;
    m_FirstAssemblyFlag=TRUE;
	m_WriteFile = IN_WriteFile;
	m_InstanceIDManager = IN_InstanceIDManager;
	m_AssemType = -1;
	m_SfigFlag = -1;
	m_SfigTableIndex = 0;
	m_AssemblyCode = 1;
	m_CurveFlag = 0;
	m_ErrorFlag = FALSE;
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFWriteManagerC.cpp                    �쐬���F2000.04.18
//
//  �P�D�@�\�T�v
//      �N���X����
//
//  �Q�D�C���^�[�t�F�[�X
//		void	SXFWriteManagerC::~SXFWriteManagerC()
//		
//	����	�F	�^		������				���e
//		�Ȃ�
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.18    ��
//
//------------------------------------------------------------
SXFWriteManagerC::~SXFWriteManagerC()
{
	if (m_CurrentAssembly != NULL)
		delete m_CurrentAssembly;
	if (m_ChildrenArray != NULL)
		delete m_ChildrenArray;
	if (m_CurrentChild != NULL)
		delete m_CurrentChild;
	for( POSITION pos = m_SfigorgTable.GetHeadPosition(); pos; ) {
		SXFSFIGORGCHECK*	pSfigOrg = m_SfigorgTable.GetNext(pos) ;
		delete pSfigOrg ;
	}
}


//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFWriteManagerC.cpp                    �쐬���F2000.04.18
//
//  �P�D�@�\�T�v
//      Assembly�v�f�̓o�^
//
//  �Q�D�C���^�[�t�F�[�X
//      int RegisterAssembly(int IN_AssemblyType,LPVOID IN_Struct)
//
//	    ����: �^			  ������			    ���e
//            int             IN_AssemblyType      Assembly Type
//            LPVOID          IN_Struct            Assembly�v�f��
//                                                 �\���̂̃A�h���X
//      
//	    ���A�l	
//            ���펞�FAssembly�v�f��Code
//			  �ُ펞�F��(�G���[�R�[�h)
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.18    ��
//
//------------------------------------------------------------
int SXFWriteManagerC::RegisterAssembly(int IN_AssemblyType,LPVOID IN_Struct)
{
	int error_code;

	/** ���łɗp��������ꍇ **/
    if( m_SheetAssemblyFlag == TRUE){
		m_AssemType = -1;	/* �A�Z���u���͊J����Ă��Ȃ� */
		/* �p�� */
		if (IN_AssemblyType == 1){
			/* �p���͂P�����ݒ�ł��Ȃ� */
			SXFErrorMsgC::RecordError(SXFSHEETONE,
										"SHEET",
										0);
			return SXFSHEETONE;
		}
		else if (IN_AssemblyType == 2){
			/* �����}�`��ɗp���͔z�u�ł��Ȃ� */
			SXFErrorMsgC::RecordError(SXFSFIGLOCERR,
										"SFIG_ORG",
										0);
			return SXFSFIGLOCERR;
		}
		else if (IN_AssemblyType == 3){
			/* �����Ȑ���ɂ͗p���͔z�u�ł��Ȃ� */
			SXFErrorMsgC::RecordError(SXFCURVELOCERR,
										"COMPOSITE_CURVE_ORG",
										0);
			return SXFCURVELOCERR;
		}
    }
	/** �p�� **/
    if(IN_AssemblyType == 1)
        m_SheetAssemblyFlag=TRUE;
	/** �����}�` **/
    else if(IN_AssemblyType == 2){
		/*
        SXFSFIGORGCHECK sfigorgcheck;
        sfigorgcheck.name = ((Sfigorg_Struct*)IN_Struct)->name;
        sfigorgcheck.type = ((Sfigorg_Struct*)IN_Struct)->flag;
		sfigorgcheck.locate_flag = -1;
		sfigorgcheck.error = -1;
		// �����}�`ð��قɒǉ�
        m_SfigorgTable.Add(sfigorgcheck );
		*/
		SXFSFIGORGCHECK*	pSfigOrg = new SXFSFIGORGCHECK ;
		pSfigOrg->name = ((Sfigorg_Struct*)IN_Struct)->name ;
		pSfigOrg->type = ((Sfigorg_Struct*)IN_Struct)->flag ;
		m_SfigorgTable.AddTail(pSfigOrg) ;
		m_mapSfigOrg.SetAt(pSfigOrg->name, pSfigOrg) ;
    }
	//AssemblyType set
	m_AssemType = IN_AssemblyType;
	/** �ŏ��̃A�Z���u���v�f�̏ꍇ **/
    if(m_FirstAssemblyFlag){ //first assembly
		/** WriteMapping�Ǘ��I�u�W�F�N�g���� **/
		m_CurrentAssembly = new SXFWriteMappingManagerC(m_AssemType,
														m_WriteFile,
														m_InstanceIDManager);
		/** FirstAssemblyFlag ��OFF **/
        m_FirstAssemblyFlag=!m_FirstAssemblyFlag;
		/** ChildrenArray�𐶐� **/
		m_ChildrenArray = new CUIntArray();
    }
	else{ //not the first assembly
		//assembly must have children
		if (m_ChildrenArray->GetSize() <= 0){
			/* �O��Ă��������ؗv�f���װ */
			if (m_ErrorFlag)
				m_ErrorFlag = FALSE;
			else{
				/** �����}�`��`���G���[ **/
				if (m_SfigFlag == 1){
					/* �����}�`ð��ق̴װ�׸ނ�ON */
					// m_SfigorgTable[m_SfigTableIndex].error = -1;	/* error flg��ON */
					POSITION	pos = m_SfigorgTable.FindIndex(m_SfigTableIndex) ;
					if( pos != NULL ) {
						SXFSFIGORGCHECK*	pSfigOrg = m_SfigorgTable.GetAt(pos) ;
						pSfigOrg->error = -1 ;
					}
					m_SfigTableIndex++;
				}
				/* �����Ȑ����G���[ */
				if (m_CurveFlag == 1)
					/* �����Ȑ��e�[�u������G���[�̃A�Z���u���R�[�h���폜 */
					m_CurveTable.RemoveAt(m_CurveTable.GetSize()-1);
				/* �A�Z���u���v�f��ɗv�f���Ȃ� */
				SXFErrorMsgC::RecordError(SXFNOTFEATURE,"",0);
			}
		}
		else{
			/** �A�Z���u���v�f��Mapping **/
			error_code = m_CurrentAssembly->MappingAssembly();
			/* Mapping�Ɏ��s */
			if (error_code){
				/** �����}�`��` **/
				if (m_SfigFlag == 1){
					/* �����}�`ð��ق̴װ�׸ނ�ON */
					// m_SfigorgTable[m_SfigTableIndex].error = -1;
					POSITION	pos = m_SfigorgTable.FindIndex(m_SfigTableIndex) ;
					if( pos != NULL ) {
						SXFSFIGORGCHECK*	pSfigOrg = m_SfigorgTable.GetAt(pos) ;
						pSfigOrg->error = -1 ;
					}
					m_SfigTableIndex++;
				}
				/* �����Ȑ� */
				if (m_CurveFlag == 1)
					/* �����Ȑ��e�[�u������G���[�̃A�Z���u���R�[�h���폜 */
					m_CurveTable.RemoveAt(m_CurveTable.GetSize()-1);
			}
			/* Mapping���� */
			else{
				if (m_SfigFlag == 1){
					/* �����}�`ð��ق̴װ�׸ނ�OFF */
					// m_SfigorgTable[m_SfigTableIndex].error = 1;
					POSITION	pos = m_SfigorgTable.FindIndex(m_SfigTableIndex) ;
					if( pos != NULL ) {
						SXFSFIGORGCHECK*	pSfigOrg = m_SfigorgTable.GetAt(pos) ;
						pSfigOrg->error = 1 ;
					}
					m_SfigTableIndex++;
				}
				/** �A�Z���u���R�[�h���{�P **/
				m_AssemblyCode++;
			}
		}
		/* �f�[�^�̃N���A */
		m_ChildrenArray->RemoveAll();	
		m_CurrentAssembly->ClearData();
    }
	/** �����Ȑ���` **/
	if(IN_AssemblyType == 3){
		/* �����Ȑ��׸�ON */
		m_CurveFlag = 1;
		/* �����Ȑ��e�[�u���ɃA�Z���u���R�[�h�ǉ� */
		m_CurveTable.Add(m_AssemblyCode);
	}
	else{
		/* �����Ȑ��׸�OFF */
		m_CurveFlag = 0;	
	}
	/** �����}�` **/
	if (IN_AssemblyType == 2)
		m_SfigFlag = 1;		/* SfigFlag ��ON */
	else
		m_SfigFlag = 0;		/* SfigFlag ��OFF */
	/** �A�Z���u���\���̂��Z�b�g **/
	m_CurrentAssembly->SetStructData(IN_AssemblyType,IN_Struct);
    return m_AssemblyCode;
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFWriteManagerC.cpp                    �쐬���F2000.04.18
//
//  �P�D�@�\�T�v
//      Feature�v�f�\���̂̓o�^
//
//  �Q�D�C���^�[�t�F�[�X
//      int RegisterFeature(char* IN_FeatureType,LPVOID IN_Struct)
//
//	    ����: �^			  ������			    ���e
//            char*          IN_FeatureType        Feature�v�f��
//                                                 TypeName
//            LPVOID          IN_Struct            Feature�v�f��
//                                                 �\���̂̃A�h���X
//      
//	    ���A�l	
//            ���펞�F�v�f��ID
//			  �ُ펞�F��(�G���[�R�[�h)
//      
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.18    ��
//
//------------------------------------------------------------
int SXFWriteManagerC::RegisterFeature(char* IN_FeatureType,LPVOID IN_Struct)
{
	int error_code,childid1;

	/* �A�Z���u���v�f���J����Ă��Ȃ� */
	if (m_AssemType == -1){
		SXFErrorMsgC::RecordError(SXFNOTASSEMBLY,IN_FeatureType,0);
		return SXFNOTASSEMBLY;
	}
	/* Mapping�Ǘ���޼ު�Ă𐶐� */
	m_CurrentChild = new SXFWriteMappingManagerC(m_AssemType,
												m_WriteFile,
												m_InstanceIDManager);
	/* �t�B�[�`���\���̂��Z�b�g&�o�� */
    error_code = m_CurrentChild->MappingFeature(IN_FeatureType,IN_Struct,childid1);
	if (!error_code)
	    m_ChildrenArray->Add(childid1);
	else
		childid1 = error_code;
	delete	m_CurrentChild;
	m_CurrentChild = NULL;
    return childid1;
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFWriteManagerC.cpp                    �쐬���F2000.04.18
//
//  �P�D�@�\�T�v
//      Sheet Assembly �v�f�̏o��
//
//  �Q�D�C���^�[�t�F�[�X
//      int CloseAssembly()
//
//	    ����: �^			  ������			    ���e
//			  �Ȃ�
//	
//	    ���A�l	
//            ���펞�F0
//			  �ُ펞�F��(�G���[�R�[�h)
//      
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.18     ��
//
//------------------------------------------------------------
int SXFWriteManagerC::CloseAssembly()
{
	int error_code;
	/* �p�����ݒ肳��Ă��Ȃ� */
    if( m_SheetAssemblyFlag != TRUE){
		SXFErrorMsgC::RecordError(SXFNOTSETSHEET,"SHEET",0);
        return SXFNOTSETSHEET;//no sheet assembly
    }
	//assembly have not child error
	if (m_ChildrenArray->GetSize() <= 0){
		SXFErrorMsgC::RecordError(SXFNOTFEATURE,"",0);
		return SXFNOTFEATURE;
	}
	/* �A�Z���u���v�f��Mapping */
	error_code = m_CurrentAssembly->MappingAssembly( );
    return error_code;
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFWriteManagerC.cpp                    �쐬���F2000.04.18
//
//  �P�D�@�\�T�v
//      Assembly Type�̎擾
//
//  �Q�D�C���^�[�t�F�[�X
//      int GetAssemType()
//
//	    ����: �^			  ������			    ���e
//			  �Ȃ�
//
//	    ���A�l	
//            ���펞�FAssembly Type
//			  �ُ펞�F
//      
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.18    ��
//
//------------------------------------------------------------
int SXFWriteManagerC::GetAssemType()
{
	return m_AssemType;
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFWriteManagerC.cpp                    �쐬���F2000.04.18
//
//  �P�D�@�\�T�v
//      �����}�`�������łɒ�`����Ă��邩�`�F�b�N����
//
//  �Q�D�C���^�[�t�F�[�X
//      BOOL SfigNameCheck( LPCTSTR IN_Name)
//
//	    ����: �^			  ������			    ���e
//            LPCTSTR         IN_Name              Sfig Name
//
//	    ���A�l	
//            ���펞�FTRUE		��`�ς�
//			  �ُ펞�FFALSE		��`����Ă��Ȃ�
//      
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.18    ��
//
//------------------------------------------------------------
BOOL SXFWriteManagerC::SfigNameCheck( LPCTSTR IN_Name)
{
/*
	for(int i=0;i<m_SfigorgTable.GetSize();i++){
		if ( m_SfigorgTable[i].name == IN_Name 
			&& m_SfigorgTable[i].error == 1){ 
			return TRUE;
        }
	}
*/
	SXFSFIGORGCHECK*	pSfigOrg = NULL ;
	if( m_mapSfigOrg.Lookup(IN_Name, (void*&)pSfigOrg) ) {
		if( pSfigOrg->error == 1 ) {
			return TRUE ;
		}
	}

	return FALSE;
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFWriteManagerC.cpp                    �쐬���F2000.04.18
//
//  �P�D�@�\�T�v
//      �A�Z���u���v�f�̍\���̂��G���[�������ꍇ�̏���
//      �r��������Ă���A�Z���u����Mapping����B
//
//  �Q�D�C���^�[�t�F�[�X
//      void ErrorAssembly()
//
//	    ����: �^			  ������			    ���e
//			  �Ȃ�
//
//	    ���A�l:	
//            �Ȃ�
//      
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.18     ��
//
//------------------------------------------------------------
void SXFWriteManagerC::ErrorAssembly()
{
	int error_code;

	//�A�Z���u���͊J���Ȃ�
	m_AssemType = -1;
	//assembly must have children
    if ( m_ChildrenArray !=NULL && m_ChildrenArray->GetSize() > 0){
		/* Mapping */
		error_code = m_CurrentAssembly->MappingAssembly( );	/* �װ���ނ͕Ԃ��Ȃ� */
		/* Mapping�Ɏ��s */
		if (error_code){
			/** �����}�`��` **/
			if (m_SfigFlag == 1){
				/* �����}�`ð��ق̴װ�׸ނ�ON */
				// m_SfigorgTable[m_SfigTableIndex].error = -1;
				POSITION	pos = m_SfigorgTable.FindIndex(m_SfigTableIndex) ;
				if( pos != NULL ) {
					SXFSFIGORGCHECK*	pSfigOrg = m_SfigorgTable.GetAt(pos) ;
					pSfigOrg->error = -1 ;
				}
				m_SfigTableIndex++;
			}
			/* �����Ȑ� */
			if (m_CurveFlag == 1)
				/* �����Ȑ��e�[�u������G���[�̃A�Z���u���R�[�h���폜 */
				m_CurveTable.RemoveAt(m_CurveTable.GetSize()-1);
		}
		else{
			/** �����}�`��` **/
			if (m_SfigFlag == 1){
				/* �����}�`ð��ق̴װ�׸ނ�OFF */
				// m_SfigorgTable[m_SfigTableIndex].error = 1;
				POSITION	pos = m_SfigorgTable.FindIndex(m_SfigTableIndex) ;
				if( pos != NULL ) {
					SXFSFIGORGCHECK*	pSfigOrg = m_SfigorgTable.GetAt(pos) ;
					pSfigOrg->error = 1 ;
				}
				m_SfigTableIndex++;
			}
			/* �A�Z���u���R�[�h�{�P */
			m_AssemblyCode++;
		}
		/* ��ʗv�f�e�[�u�����N���A */
		m_ChildrenArray->RemoveAll();	
	}
	else{
		if (!m_FirstAssemblyFlag && !m_ErrorFlag)
			/* �A�Z���u���v�f��ɗv�f���Ȃ� */
			SXFErrorMsgC::RecordError(SXFNOTFEATURE,"",0);
	}
	/* �A�Z���u���f�[�^���N���A */
	if(m_CurrentAssembly != NULL)
        m_CurrentAssembly->ClearData();
	/* ErrorFlag��ON */
	m_ErrorFlag = TRUE;
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFWriteManagerC.cpp                    �쐬���F2001.2.23
//
//  �P�D�@�\�T�v
//      �����}�`���ɑΉ����镡���}�`��ʂ��擾����
//
//  �Q�D�C���^�[�t�F�[�X
//      BOOL GetSfigFlg( LPCTSTR IN_Name,
//							int* OUT_Type,
//							int* OUT_LocFlg)
//
//	    ����: �^			  ������	    ���e
//            LPCTSTR         IN_Name       Sfig Name
//			  int*			  OUT_Type		�����}�`���
//			  int*			  OUT_LocFlg	�z�u�t���O
//											(0�F���z�u 1:�z�u��)
//
//	    ���A�l	
//            ���펞�FTRUE		�Ή������ʂ���
//			  �ُ펞�FFALSE		�Ή������ʂȂ�
//      
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2001.2.23	   �{��(FQS)
//
//------------------------------------------------------------
BOOL SXFWriteManagerC::GetSfigFlg( LPCTSTR IN_Name,
									int* OUT_Type,
									int* OUT_LocFlg)
{
	*OUT_Type = -1;
	*OUT_LocFlg = -1;
/*
	for(int i=0;i<m_SfigorgTable.GetSize();i++){
		if ( m_SfigorgTable[i].name == IN_Name 
					&& m_SfigorgTable[i].error == 1){ 
			*OUT_Type = m_SfigorgTable[i].type;
			*OUT_LocFlg = m_SfigorgTable[i].locate_flag;
			return TRUE;
        }
	}
*/
	SXFSFIGORGCHECK*	pSfigOrg = NULL ;
	if( m_mapSfigOrg.Lookup(IN_Name, (void*&)pSfigOrg) ) {
		if( pSfigOrg->error == 1 ) {
			*OUT_Type	= pSfigOrg->type ;
			*OUT_LocFlg	= pSfigOrg->locate_flag ;
			return TRUE ;
		}
	}
	return FALSE;  
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFWriteManagerC.cpp                    �쐬���F2001.2.23
//
//  �P�D�@�\�T�v
//      �����}�`���ɑΉ����镡���}�`��ʂ�ݒ肷��
//
//  �Q�D�C���^�[�t�F�[�X
//      BOOL SetLocFlg( LPCTSTR IN_Name)
//
//	    ����: �^			  ������	    ���e
//            LPCTSTR         IN_Name       Sfig Name
//
//	    ���A�l	
//            ���펞�FTRUE		�Ή�����t���O����
//			  �ُ펞�FFALSE		�Ή�����t���O�Ȃ�
//      
//  �R�D����
//	    ����ԍ�    ���t��         �S����		�T�v
//      �쐬		2001.2.23		�{��(FQS)
//
//------------------------------------------------------------
BOOL SXFWriteManagerC::SetLocFlg( LPCTSTR IN_Name)
{
/*
	for(int i=0;i<m_SfigorgTable.GetSize();i++){
		if ( m_SfigorgTable[i].name == IN_Name 
			&& m_SfigorgTable[i].error == 1){ 
			m_SfigorgTable[i].locate_flag = 1;
			return TRUE;
        }
	}    
*/
	SXFSFIGORGCHECK*	pSfigOrg = NULL ;
	if( m_mapSfigOrg.Lookup(IN_Name, (void*&)pSfigOrg) ) {
		if( pSfigOrg->error == 1 ) {
			pSfigOrg->locate_flag = 1 ;
			return TRUE ;
		}
	}
	return FALSE;  
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFWriteManagerC.cpp                    �쐬���F2001.2.23
//
//  �P�D�@�\�T�v
//      �n�b�`���O�̊O�`�E������ID����`����Ă��邩�`�F�b�N����
//
//  �Q�D�C���^�[�t�F�[�X
//      BOOL CheckHatchID( int IN_ID)
//
//	    ����: �^	������	    ���e
//            int   IN_ID       ʯ�ݸނ̊O�`��������ID
//								(�����Ȑ��̱����غ���)
//
//	    ���A�l	
//            ���펞�FTRUE		ʯ�ݸނ̊O�`����`����Ă���
//			  �ُ펞�FFALSE		ʯ�ݸނ̊O�`����`����Ă��Ȃ�
//      
//  �R�D����
//	    ����ԍ�    ���t��         �S����		�T�v
//      �쐬		2001.2.23		�{��(FQS)
//
//------------------------------------------------------------
BOOL SXFWriteManagerC::CheckHatchID( unsigned int IN_ID){
	for (int i = 0; i < m_CurveTable.GetSize(); i++){
		if (m_CurveTable[i] == IN_ID)
			return TRUE;
	}
	return FALSE;
}
