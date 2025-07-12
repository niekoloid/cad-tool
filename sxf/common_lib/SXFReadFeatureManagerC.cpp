//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFReadFeatureManagerC.cpp               �쐬���F2000.04.23
//
//	�P�D�N���X�T�v
//      �e������������ Comment�A�Z���u���v�f�A
//      ��ʗv�f�̐e�q�֌W���Ǘ�����
//
//	�Q�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.23     ��
//
//------------------------------------------------------------

#include "stdafx.h"
#include "SXFReadFeatureManagerC.h"
#include "SXFReadMapManagerC.h"
#include "SXFFeatureAssemblyC.h"
#include "SXFFeatureChildC.h"
#include "SXFSplitFeatureC.h"
#include "SXFErrorMsgC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFReadFeatureManagerC.cpp               �쐬���F2000.04.23
//
//  �P�D�@�\�T�v
//      �N���X�\�z
//
//  �Q�D�C���^�[�t�F�[�X
//		void	SXFReadFeatureManagerC::SXFReadFeatureManagerC()
//		
//	����	�F	�^		������				���e
//		�Ȃ�
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.23     ��
//
//------------------------------------------------------------
SXFReadFeatureManagerC::SXFReadFeatureManagerC()
{
    //initialization
    m_SheetAssembly = NULL;
    m_CurveAssemblyList = NULL;
    m_SymbolAssemblyList = NULL;
	m_SymbolInfoTable.InitHashTable(5000);
    m_CurrentAssembly = NULL;
    m_CurrentChildList = NULL;
    m_CurrentChild=NULL;
    m_CurrentMapManager=NULL;
    m_CurrentAssemblyType=0;
    m_AssemblyPos = NULL;
    m_ChildPos = NULL;
	m_code = 1;			/* �A�Z���u���R�[�h */
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFReadFeatureManagerC.cpp               �쐬���F2000.04.23
//
//  �P�D�@�\�T�v
//      �N���X����
//
//  �Q�D�C���^�[�t�F�[�X
//		void	SXFReadFeatureManagerC::~SXFReadFeatureManagerC()
//		
//	����	�F	�^		������				���e
//		�Ȃ�
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.23     ��
//
//------------------------------------------------------------
SXFReadFeatureManagerC::~SXFReadFeatureManagerC()
{
    if(m_SheetAssembly != NULL )
        delete m_SheetAssembly;
    if(m_CurveAssemblyList != NULL){
        m_AssemblyPos = m_CurveAssemblyList->GetHeadPosition();
        while(m_AssemblyPos!=NULL){
            m_CurrentAssembly = m_CurveAssemblyList->GetAt(m_AssemblyPos);
            if(m_CurrentAssembly!=NULL){
                delete m_CurrentAssembly;
            }
            m_CurveAssemblyList->GetNext(m_AssemblyPos);
        }
        if(m_CurveAssemblyList != NULL)
            delete  m_CurveAssemblyList;
    }
	
    if(m_SymbolAssemblyList != NULL){
        m_AssemblyPos = m_SymbolAssemblyList->GetHeadPosition();
        while(m_AssemblyPos!=NULL){
            m_CurrentAssembly = m_SymbolAssemblyList->GetAt(m_AssemblyPos);
            if(m_CurrentAssembly!=NULL){
                delete m_CurrentAssembly;
            }
            m_SymbolAssemblyList->GetNext(m_AssemblyPos);
        }
        if(m_SymbolAssemblyList != NULL)
            delete  m_SymbolAssemblyList;
    }
	/*
	CString					strKey ;
	SXFFeatureAssemblyC*	pSymValue ;
	for( POSITION pos = m_SymbolInfoTable.GetStartPosition(); pos; ) {
		m_SymbolInfoTable.GetNextAssoc(pos, strKey, (void*&)pSymValue) ;
		delete pSymValue ;
	}
	*/
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFReadFeatureManagerC.cpp               �쐬���F2000.04.23
//
//  �P�D�@�\�T�v
//      �v�f�Ǘ�Table�Ɉ��Feature Comment Assembly Instance��o�^����
//      
//  �Q�D�C���^�[�t�F�[�X
//      BOOL RegisterFeatureAssembly(INSTANCEDATA *IN_Instance)
//
//	    ����: �^			  ������			    ���e
//            INSTANCEDATA*  IN_Instance           Feature Comment Assembly
//                                                 Instance�\���̂̃A�h���X
//      
//	    ���A�l	
//            ���펞�FTRUE
//			  �ُ펞�FFALSE
//      
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.23     ��
//
//------------------------------------------------------------
BOOL SXFReadFeatureManagerC::RegisterFeatureAssembly(INSTANCEDATA *IN_Instance)
{

	/** �P�O�̃A�Z���u���I�u�W�F�N�g��ޔ� **/
	SXFFeatureAssemblyC* LastAssembly = m_CurrentAssembly;
	
	/** �����ص�޼ު�Đ��� */
    m_CurrentAssembly=new SXFFeatureAssemblyC;
    if(m_CurrentAssembly == NULL){
		Delete_m_CurrentChildList();
        return FALSE;//memory error
    }
	/** �C���X�^���XID�ݒ� **/
    m_CurrentAssembly->AssemblyID = IN_Instance->InstanceID;
	/** �A�Z���u���R�[�h�ݒ� **/
    m_CurrentAssembly->AssemblyCode = m_code;
	/** �t�B�[�`�����X�g�ݒ� **/
    m_CurrentAssembly->ChildList = m_CurrentChildList;
    m_CurrentChildList = NULL;

	/** Mapping�Ǘ���޼ު�Đ��� */
    m_CurrentMapManager =  new SXFReadMapManagerC;
    if(m_CurrentMapManager == NULL){
		delete m_CurrentAssembly;
		m_CurrentAssembly=NULL;
        return FALSE;//memory error
    }
	/** �C���X�^���X�f�[�^�ݒ� **/
    if (!m_CurrentMapManager->SetFeatureData(IN_Instance)){
		delete m_CurrentAssembly;
		m_CurrentAssembly=NULL;
		delete m_CurrentMapManager;
		m_CurrentMapManager=NULL;
        return FALSE;//memory error
	}
	/** Mapping�Ǘ���޼ު�ľ�� */
    m_CurrentAssembly->AssemblyMapManager = m_CurrentMapManager;

	/** �p�� **/
    if(IN_Instance->EntityName == "drawing_sheet_feature"){
		/* �p�������łɐݒ�ς� */
        if(m_SheetAssembly != NULL){
			/* �p���͈�̂� */
			SXFErrorMsgC::RecordError(SXFSHEETONE,"SHEET",0);
			delete m_CurrentAssembly;
			m_CurrentAssembly=NULL;
			return FALSE;
		}
        CStringArray* array;
        SXFSplitFeatureC split(IN_Instance->EntityData);
        array = split.Split();
        if(array == NULL){
			delete m_CurrentAssembly;
			m_CurrentAssembly=NULL;
            return FALSE;
		}
        if (array->GetSize() != 5){ // syntax err
			delete m_CurrentAssembly;
			m_CurrentAssembly=NULL;
            return FALSE;
		}
		/* �p���� */
        m_CurrentAssembly->AssemblyName = (*array)[0];
		/* �p���T�C�Y��� */
        m_CurrentAssembly->AssemSheetType = atoi((*array)[1]);
		//�p���T�C�Y��ʂ��O�`�S�܂��͂X�ł͂Ȃ��Ƃ�
		if ( (m_CurrentAssembly->AssemSheetType < 0) 
					|| (m_CurrentAssembly->AssemSheetType > 4) ){
			if (m_CurrentAssembly->AssemSheetType != 9){
				SXFErrorMsgC::RecordError(SXFSHEETSIZE,
											"SHEET",
											1,
											m_CurrentAssembly->AssemSheetType);
				delete m_CurrentAssembly;
				m_CurrentAssembly=NULL;
				return FALSE;
			}
		}
		/* �p���T�C�Y */
        m_CurrentAssembly->AssemSheetX = atoi((*array)[3]);
        m_CurrentAssembly->AssemSheetY = atoi((*array)[4]);
		//�p���T�C�Y��ʂ��X�Ŏ��R�p������,�c�����ݒ肳��ĂȂ��Ƃ�
		if (m_CurrentAssembly->AssemSheetType == 9){
			if (m_CurrentAssembly->AssemSheetX <= 0){
				SXFErrorMsgC::RecordError(SXFSHEETLENGTH,
											"SHEET",
											1,
											m_CurrentAssembly->AssemSheetX);
				delete m_CurrentAssembly;
				m_CurrentAssembly=NULL;
				return FALSE;
			}
			if (m_CurrentAssembly->AssemSheetY <= 0){
				SXFErrorMsgC::RecordError(SXFSHEETLENGTH,
											"SHEET",
											1,
											m_CurrentAssembly->AssemSheetY);
				delete m_CurrentAssembly;
				m_CurrentAssembly=NULL;
				return FALSE;
			}
		}
		/* �c�^���敪 */
        m_CurrentAssembly->AssemSheetOrient = atoi((*array)[2]);
		//�p���T�C�Y��ʂ��X�ł͂Ȃ��A�c/���敪���O�܂��͂P�ł͂Ȃ��Ƃ�
		//�p���T�C�Y��ʂ��X�̂Ƃ��A�c/���敪�͖���
		if (m_CurrentAssembly->AssemSheetType != 9){
			if ((m_CurrentAssembly->AssemSheetOrient < 0) 
					|| (m_CurrentAssembly->AssemSheetOrient > 1)){
				SXFErrorMsgC::RecordError(SXFORIENTERROR,
											"SHEET",
											1,
											m_CurrentAssembly->AssemSheetOrient);
				delete m_CurrentAssembly;
				m_CurrentAssembly=NULL;
				return FALSE;
			}
		}
		/* �p���A�Z���u���I�u�W�F�N�g�Z�b�g */
        m_SheetAssembly = m_CurrentAssembly;
    }
	/** �����Ȑ���` **/
	else if(IN_Instance->EntityName == "composite_curve_org_feature"){
        /** �P�ڂ̕����Ȑ��̏ꍇ**/
        if(m_CurveAssemblyList == NULL){
            m_CurveAssemblyList = new SXFASSEMBLYLIST;
        }
        /** �Q�ڈȍ~�̕����Ȑ��̂ɂāA�P�O�̃A�Z���u���v�f���p���������ꍇ **/
		if(LastAssembly==m_SheetAssembly && LastAssembly!=NULL ){
			/* �p���͕����Ȑ���`�ɔz�u�ł��Ȃ� */
			SXFErrorMsgC::RecordError(SXFCURVELOCERR,"COPOSITE_CURVE_ORG",0);
			delete m_CurrentAssembly;
			m_CurrentAssembly=NULL;
            return FALSE;
		}
        CStringArray* array;
        SXFSplitFeatureC split(IN_Instance->EntityData);
        array = split.Split();
        if(array == NULL){
			delete m_CurrentAssembly;
			m_CurrentAssembly=NULL;
            return FALSE;
		}
        if (array->GetSize() != 4){ // syntax err
			delete m_CurrentAssembly;
			m_CurrentAssembly=NULL;
            return FALSE;
		}
		/* ���� */
		m_CurrentAssembly->m_CurveColour = atoi((*array)[0]);
		m_CurrentAssembly->m_CurveType = atoi((*array)[1]);
		m_CurrentAssembly->m_CurveWidth = atoi((*array)[2]);
		/* �\���^��\���t���O */
        m_CurrentAssembly->AssemCurveFlag = atoi((*array)[3]);
        //�\���^��\���t���O���O�܂��͂P�ȊO�̂Ƃ�
        if ((m_CurrentAssembly->AssemCurveFlag < 0) 
				|| (m_CurrentAssembly->AssemCurveFlag > 1)){
            SXFErrorMsgC::RecordError(SXFCURVEFLAG,
										"COPOSITE_CURVE_ORG",
										1,
										m_CurrentAssembly->AssemCurveFlag);
			delete m_CurrentAssembly;
			m_CurrentAssembly=NULL;
            return FALSE;
        }
		/* �����Ȑ��e�[�u���ɒǉ� */
        m_CurveAssemblyList->AddTail(m_CurrentAssembly);
    }
	/** �����}�`��` **/
	else if(IN_Instance->EntityName == "sfig_org_feature"){
		/** �Q�ڈȍ~�̕����}�`�ɂāA�P�O�̃A�Z���u���v�f���p���������ꍇ **/
		if(LastAssembly==m_SheetAssembly && LastAssembly!=NULL ){
			/* �p���͕����}�`��`�ɔz�u�ł��Ȃ� */
			SXFErrorMsgC::RecordError(SXFSFIGLOCERR,"SFIG_ORG",0);
			delete m_CurrentAssembly;
			m_CurrentAssembly=NULL;
            return FALSE;
		}
		/** �P�ڂ̕����}�`�̏ꍇ **/
		
        if(m_SymbolAssemblyList == NULL){
            m_SymbolAssemblyList = new SXFASSEMBLYLIST;
        }
		
        CStringArray* array;
        SXFSplitFeatureC split(IN_Instance->EntityData);
        array = split.Split();
        if(array == NULL){
			delete m_CurrentAssembly;
			m_CurrentAssembly=NULL;
            return FALSE;
		}
        if (array->GetSize() != 2){ // syntax err
			delete m_CurrentAssembly;
			m_CurrentAssembly=NULL;
            return FALSE;
		}
		/* �����}�`�� */
        m_CurrentAssembly->AssemblyName = (*array)[0];
		//Name Unique check

		/*	2010.08
		for(POSITION pos = m_SymbolAssemblyList->GetHeadPosition();
						pos != NULL;m_SymbolAssemblyList->GetNext(pos)){
			// ���ɖ��O�����O���o�^�ς�
			if (m_SymbolAssemblyList->GetAt(pos)->AssemblyName == (*array)[0]){
				SXFErrorMsgC::RecordError(SXFSAMENAME,"SFIG_ORG",1,(*array)[0]);
				delete m_CurrentAssembly;
				m_CurrentAssembly=NULL;
				return FALSE;
			}
		}
		*/

		SXFFeatureAssemblyC* pValue ;	// 2010.08
		if( m_SymbolInfoTable.Lookup(m_CurrentAssembly->AssemblyName, (void*&)pValue) ) {
			// ���ɖ��O�����O���o�^�ς�
			SXFErrorMsgC::RecordError(SXFSAMENAME,"SFIG_ORG",1,(*array)[0]);
			delete m_CurrentAssembly;
			m_CurrentAssembly=NULL;
			return FALSE;
		}
		/* �����}�`��� */
		m_CurrentAssembly->AssemSymbolType = atoi((*array)[1]);
		if (m_CurrentAssembly->AssemSymbolType < 1 
				|| m_CurrentAssembly->AssemSymbolType > 4){
			CString AssemID;
			AssemID.Format("#%d",m_CurrentAssembly->AssemblyID);
			SXFErrorMsgC::RecordError(SXFSFIGFLAG,
										"SFIG_ORG",
										3,
										AssemID,
										m_CurrentAssembly->AssemSymbolType,
										"SFIG_ORG");
				delete m_CurrentAssembly;
				m_CurrentAssembly=NULL;
				return FALSE;
		}
		/* �����}�`ð��قɒǉ� */
        m_SymbolAssemblyList->AddTail(m_CurrentAssembly);
		m_SymbolInfoTable.SetAt(m_CurrentAssembly->AssemblyName, m_CurrentAssembly);	// 2010.08
    }
    m_code++;	/* �����غ��� */
    return TRUE;
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFReadFeatureManagerC.cpp               �쐬���F2000.04.23
//
//  �P�D�@�\�T�v
//      �v�f�Ǘ�Table�Ɉ��Feature Comment Entity Instance��o�^����
//      
//  �Q�D�C���^�[�t�F�[�X
//      BOOL RegisterFeatureEntity(INSTANCEDATA *IN_Instance)
//
//	    ����: �^			  ������			    ���e
//            INSTANCEDATA*  IN_Instance           Feature Comment Entity
//                                                 Instance�\���̂̃A�h���X
//      
//	    ���A�l	
//            ���펞�FTRUE
//			  �ُ펞�FFALSE
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.23     ��
//
//------------------------------------------------------------
BOOL SXFReadFeatureManagerC::RegisterFeatureEntity(INSTANCEDATA *IN_Instance)
{
    if(m_CurrentChildList == NULL){
		/* ��ʗv�fð��ِ��� */
        m_CurrentChildList = new SXFCHILDLIST; 
    }
	/* ��ʗv�f̨�����޼ު�Đ��� */
    m_CurrentChild = new SXFFeatureChildC;
    if(m_CurrentChild == NULL)
        return FALSE;//memory error
	/** �C���X�^���XID�ݒ� **/
    m_CurrentChild->ChildID = IN_Instance->InstanceID;
	/* ̨���Mapping�Ǘ���޼ު�Đ��� */
    m_CurrentMapManager =  new SXFReadMapManagerC;
    if(m_CurrentMapManager == NULL){
		delete m_CurrentChild;
		m_CurrentChild=NULL;
        return FALSE;//memory error
	}
	/** �C���X�^���X�f�[�^�ݒ� **/
    if (!m_CurrentMapManager->SetFeatureData(IN_Instance)){
		delete m_CurrentChild;
		m_CurrentChild=NULL;
		delete m_CurrentMapManager;
		m_CurrentMapManager=NULL;
		return FALSE;
	}
	/* ̨���Mapping�Ǘ���޼ު�Đݒ� */
    m_CurrentChild->ChildMapManager = m_CurrentMapManager;
	/* ��ʗv�fð��قɒǉ� */
    m_CurrentChildList->AddTail( m_CurrentChild );
    return TRUE;
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFReadFeatureManagerC.cpp               �쐬���F2000.04.23
//
//  �P�D�@�\�T�v
//      �v�f�Ǘ�Table�����̗v�f���o�͂���
//      
//  �Q�D�C���^�[�t�F�[�X
//      int GetNextFeature(char* OUT_TypeName,
//                         LPVOID& OUT_Struct,
//                        int& OUT_EndFlg)
//
//	    ����: �^			  ������			   ���e
//            char*			  OUT_TypeName         �\���̂�Type Name
//			  size_t		  TypeNameSize		   Type Name�o�b�t�@�T�C�Y
//            LPVOID&         OUT_Struct           �\���̂̃A�h���X
//            int&            OUT_EndFlg           �Ō�̗v�f��Flag
//                                                  1: �Ō�̗v�f
//                                                  0: ����
//      
//	    ���A�l	
//            ���펞�F Feature ID
//			  �ُ펞�F ��(�G���[�R�[�h)
//      
//
//  �R�D����
//		����ԍ�	���t��			�S����			�T�v
//		�쐬		2000.04.23		��
//		�X�V		2015.04.27		T.Matsushima	JPCERT/CC �w�E �Ǝ㐫�Ή�
//
//------------------------------------------------------------
int SXFReadFeatureManagerC::GetNextFeature(char* OUT_TypeName, 
										   size_t TypeNameSize,	// �o�b�t�@�T�C�Y��n���悤�ɕύX JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
										   LPVOID& OUT_Struct,
										   int* OUT_EndFlg)
{
    OUT_Struct = NULL;
    *OUT_EndFlg = 1;
	int ReturnID = -1;
    m_CurrentChild=NULL;
	/** �A�Z���u�����J����Ă��Ȃ� **/
    if(m_CurrentAssembly == NULL){
		SXFErrorMsgC::RecordError(SXFNOTASSEMBLY,OUT_TypeName,0);
		return SXFNOTASSEMBLY;
	}
	/** �A�Z���u����ɗv�f�����݂��Ȃ� **/
	if(m_CurrentChildList == NULL){
		SXFErrorMsgC::RecordError(SXFNOTFEATURE,"",0);
		return SXFNOTFEATURE;
	}
	/** �A�Z���u����ɗv�f�����݂��Ȃ� **/
    if(m_ChildPos == NULL){
		SXFErrorMsgC::RecordError(SXFNOTFEATURE,"",0);
		return SXFNOTFEATURE;
	}
	/** ��ʗv�f��޼ު�ľ�� */
    m_CurrentChild = m_CurrentChildList->GetAt(m_ChildPos);
    if(m_CurrentChild == NULL){
		/** �A�Z���u����ɗv�f�����݂��Ȃ� **/
		SXFErrorMsgC::RecordError(SXFNOTFEATURE,"",0);
		return SXFNOTFEATURE;
	}
	/** Mapping�Ǘ���޼ު�ľ�� */
    m_CurrentMapManager = m_CurrentChild->ChildMapManager;
    if(m_CurrentMapManager == NULL){
		/* �����G���[���������܂��� */
		SXFErrorMsgC::RecordError(SXFERROR,"",0);
		return SXFERROR;
	}
	/** �C���X�^���XID�ݒ� **/
	ReturnID = m_CurrentChild->ChildID;
	/** �t�B�[�`���\���̎擾 **/
	//	JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
	//OUT_Struct = m_CurrentMapManager->GetStructData( OUT_TypeName);
	OUT_Struct = m_CurrentMapManager->GetStructData( OUT_TypeName, TypeNameSize);
	if(OUT_Struct == NULL){
		/* �s���ȃG���e�B�e�B���ł� */
 		SXFErrorMsgC::RecordError(SXFERRENTITY,"",0);
		return SXFERRENTITY;
	}
	m_CurrentChildList->GetNext(m_ChildPos);
	/** �\���̕ԋp�ς݃t���O��ON **/
	m_CurrentMapManager->SetReturnFlag();
	/** ��ʗv�fð��ق̍Ō�̗v�f�̂Ƃ� **/
    if(m_ChildPos == NULL){
        *OUT_EndFlg = 1;		/* EndFlg ��ON */
    }
	else{
        *OUT_EndFlg = 0;		/* EndFlg ��OFF */
    }
    return ReturnID;
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFReadFeatureManagerC.cpp               �쐬���F2000.04.23
//
//  �P�D�@�\�T�v
//      Assembly�v�f�Ǘ�Table������Assembly�v�f���o�͂���
//      
//  �Q�D�C���^�[�t�F�[�X
//      int GetNextAssembly(int IN_Type,
//                          LPVOID& OUT_Struct,
//                          int& OUT_EndFlg,
//                          int& OUT_InstanceID)
//
//	    ����: �^			  ������			    ���e
//            int             IN_Type              Assembly�\���̂�Type
//                                                  1:sheet
//                                                  2:symbol
//                                                  3:curve
//            LPVOID&         OUT_Struct           Assembly�\���̂̃A�h���X
//            int&            OUT_EndFlg           �Ō��Assembly�v�f��Flag
//                                                  1: �Ō��Assembly�v�f
//                                                  0: ����
//            int&            OUT_InstanceID        Assembly Feature ID
//      
//	    ���A�l	
//            ���펞�FAssembly Code(Assembly Table�ɓo�^�����̔ԍ��j
//			  �ُ펞�F��(�G���[�R�[�h)
//      
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.23     ��
//
//------------------------------------------------------------
int SXFReadFeatureManagerC::GetNextAssembly(int IN_Type, 
												LPVOID& OUT_Struct, 
												int* OUT_EndFlg,
												int& OUT_InstanceID)
{
    OUT_Struct = NULL;
    *OUT_EndFlg = 1;
	OUT_InstanceID = -1;
    m_CurrentAssembly = NULL;
    m_CurrentChildList = NULL;    
    m_ChildPos = NULL;

	/* �����،^���ُ� */
	if (IN_Type != 1 && IN_Type != 2 && IN_Type != 3){
		SXFErrorMsgC::RecordError(SXFASSEMTYPEERR,"",1,IN_Type);
		return SXFASSEMTYPEERR;
	}
	/* �V�Kð��ق̓ǂݏo���w�� */
	if(m_CurrentAssemblyType != IN_Type){
		m_CurrentAssemblyType = 0;
	}
	/* �V�Kð��ق̓ǂݏo���w�� */
	if(m_CurrentAssemblyType != IN_Type){
		m_CurrentAssemblyType = 0;
	}

	/** �ŏ��̃A�Z���u���v�f�̂Ƃ� **/
    if(m_CurrentAssemblyType == 0){
		/** �p�� **/
        if(IN_Type == 1){
			/** �p�����Ȃ� **/
            if(m_SheetAssembly == NULL){
				SXFErrorMsgC::RecordError(SXFNOTSETSHEET,"SHEET",0);
                return SXFNOTSETSHEET;//no sheet assembly
			}
            m_CurrentAssembly = m_SheetAssembly;
            m_AssemblyPos = NULL;
			/* ���݂̱����،^���Z�b�g */
            m_CurrentAssemblyType = 1;
        }
		/** �����}�`��` **/
		else if(IN_Type == 2){//symbol

            if(m_SymbolAssemblyList == NULL){
				// �ǂݏo���A�Z���u���v�f������܂���
// MOD(S)	���b�Z�[�W�C��	K.Naono	04.03.05
//				SXFErrorMsgC::RecordError(SXFNOASSEMBLY,"SFIGORG",0);
				SXFErrorMsgC::RecordError2(SXFNOASSEMBLY,"SFIGORG",0);
				return SXFNOASSEMBLY;
// MOD(E)	���b�Z�[�W�C��	K.Naono	04.03.05
			}

			/** �����}�`���X�g�̐擪�A�h���X�ݒ� **/
			m_AssemblyPos=m_SymbolAssemblyList->GetHeadPosition();
            // m_AssemblyPos=m_SymbolInfoTable.GetStartPosition(); // 2010.08
            if(m_AssemblyPos == NULL){
				/* �ǂݏo���A�Z���u���v�f������܂���B*/
// MOD(S)	���b�Z�[�W�C��	K.Naono	04.03.05
//				SXFErrorMsgC::RecordError(SXFNOASSEMBLY,"SFIGORG",0);
				SXFErrorMsgC::RecordError2(SXFNOASSEMBLY,"SFIGORG",0);
				return SXFNOASSEMBLY;
// MOD(E)	���b�Z�[�W�C��	K.Naono	04.03.05
			}
            m_CurrentAssembly = m_SymbolAssemblyList->GetAt(m_AssemblyPos);
			// CString	strKey ;									// 2010.08
			// m_SymbolInfoTable.GetNextAssoc(m_AssemblyPos, strKey, (void*&)m_CurrentAssembly);
			/* ���݂̱����،^���Z�b�g */
            m_CurrentAssemblyType = 2;
        }
		/** �����Ȑ���` **/
		else if(IN_Type == 3){//curve
            if(m_CurveAssemblyList == NULL){
				/* �ǂݏo���A�Z���u���v�f������܂���B*/
// MOD(S)	���b�Z�[�W�C��	K.Naono	04.03.05
//				SXFErrorMsgC::RecordError(SXFNOASSEMBLY,"CCURVE_ORG",0);
				SXFErrorMsgC::RecordError2(SXFNOASSEMBLY,"CCURVE_ORG",0);
				return SXFNOASSEMBLY;
// MOD(E)	���b�Z�[�W�C��	K.Naono	04.03.05
			}
			/** �����Ȑ����X�g�̐擪�A�h���X�ݒ� **/
            m_AssemblyPos=m_CurveAssemblyList->GetHeadPosition();
            if(m_AssemblyPos == NULL){
				/* �ǂݏo���A�Z���u���v�f������܂���B*/
// MOD(S)	���b�Z�[�W�C��	K.Naono	04.03.05
//				SXFErrorMsgC::RecordError(SXFNOASSEMBLY,"CCURVE_ORG",0);
				SXFErrorMsgC::RecordError2(SXFNOASSEMBLY,"CCURVE_ORG",0);
				return SXFNOASSEMBLY;
// MOD(E)	���b�Z�[�W�C��	K.Naono	04.03.05
			}
            m_CurrentAssembly = m_CurveAssemblyList->GetAt(m_AssemblyPos);
			/* ���݂̱����،^���Z�b�g */
            m_CurrentAssemblyType = 3;
        }
    }
	/** �Q�ڈȍ~�̃A�Z���u���v�f�̂Ƃ� **/
	else{
		/* �ŏI�f�[�^�擾��̓ǂݏo���`�F�b�N */
		if (m_AssemblyPos == NULL){
			/* �ǂݏo���A�Z���u���v�f������܂���B*/
			SXFErrorMsgC::RecordError(SXFNOASSEMBLY,"",0);
			return SXFNOASSEMBLY;
		}
		/* �����}�` */
		if(m_CurrentAssemblyType == 2) {
		    m_CurrentAssembly = m_SymbolAssemblyList->GetAt(m_AssemblyPos);
			// CString	strKey ;									// 2010.08
			// m_SymbolInfoTable.GetNextAssoc(m_AssemblyPos, strKey, (void*&)m_CurrentAssembly);
		}
		/* �����Ȑ� */
        else if(m_CurrentAssemblyType == 3)
            m_CurrentAssembly = m_CurveAssemblyList->GetAt(m_AssemblyPos);
    }
    if(m_CurrentAssembly == NULL){
		/* �ǂݏo���A�Z���u���v�f������܂���B*/
		SXFErrorMsgC::RecordError(SXFNOASSEMBLY,"",0);
		return SXFNOASSEMBLY;
	}
	/** Mapping�Ǘ���޼ު�ľ�� **/
    m_CurrentMapManager = m_CurrentAssembly->AssemblyMapManager;
    if(m_CurrentMapManager == NULL){
		/* �����G���[���������܂��� */
		SXFErrorMsgC::RecordError(SXFERROR,"",0);
		return SXFERROR;
	}
	/** �A�Z���u���t�B�[�`���̍\���̎擾 **/
    OUT_Struct = m_CurrentMapManager->GetAssemblyStructData( );
	/** �C���X�^���XID�ݒ� **/
	OUT_InstanceID = m_CurrentAssembly->AssemblyID ;//�G���[���b�Z�[�W�ɕK�v�I
	/** �t�B�[�`�����X�g�ݒ� **/
    m_CurrentChildList=m_CurrentAssembly->ChildList;
	if(m_CurrentChildList == NULL){
		/** �G���[�t���O�����Ă� **/
		m_CurrentAssembly->m_AssemblyErrFlag=FALSE;
	}
	else{
		/** �t�B�[�`�����X�g�̐擪�A�h���X��ݒ� **/
		m_ChildPos = m_CurrentChildList->GetHeadPosition();
		    if(m_ChildPos == NULL){
				/** �G���[�t���O�����Ă� **/
				m_CurrentAssembly->m_AssemblyErrFlag=FALSE;
		    }
	}

	/** �p�� **/
    if(IN_Type == 1)
        m_AssemblyPos = NULL;
	/** �����}�` **/
	else if(IN_Type == 2) {
        m_SymbolAssemblyList->GetNext(m_AssemblyPos);
		// CString	strKey ;
		// SXFFeatureAssemblyC* pSymValue ;
		// m_SymbolInfoTable.GetNextAssoc(m_AssemblyPos, strKey, (void*&)pSymValue);
	}
    /** �����Ȑ� **/
	else if(IN_Type == 3)
        m_CurveAssemblyList->GetNext(m_AssemblyPos);
	/** �\���̕ԋp�ς݃t���O��ON **/
	m_CurrentMapManager->SetReturnFlag();
	/** �A�Z���u���e�[�u���̍Ō�̗v�f�̂Ƃ� **/
    if(m_AssemblyPos == NULL){
        *OUT_EndFlg = 1;	/** END flg ��ON **/
    }
	else{
        *OUT_EndFlg = 0;	/** END flg ��OFF **/
    }
    return m_CurrentAssembly->AssemblyCode;
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFReadFeatureManagerC.cpp               �쐬���F2001.2.23
//
//  �P�D�@�\�T�v
//      �����}�`���ɑΉ����镡���}�`��ʂ̎擾
//
//  �Q�D�C���^�[�t�F�[�X
//      BOOL GetSfigFlg( LPCTSTR IN_Name,
//						int* OUT_SfigFlg,
//						int* OUT_LocFlg)
//
//	    ����: �^			  ������			���e
//            LPCTSTR         IN_Name           Sfig Name
//			  int*			  OUT_SfigFlg		�����}�`���
//			  int*			  OUT_LocFlg		�z�u�t���O
//												(1:�z�u�� 0:���z�u)
//
//	    ���A�l	
//            ���펞�FTRUE		�����}�`���ɑΉ������ʂ���
//			  �ُ펞�FFALSE		�����}�`���ɑΉ������ʂȂ�
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����		 �T�v
//      �쐬		2001.2.23      �{��(FQS)
//
//------------------------------------------------------------
BOOL SXFReadFeatureManagerC::GetSfigFlg( LPCTSTR IN_Name,
											int* OUT_SfigFlg,
											int* OUT_LocFlg)
{
	*OUT_SfigFlg = -1;
	*OUT_LocFlg = -1;
/*
	if (m_SymbolAssemblyList == NULL)
		return FALSE;
	//Name check 
	for(POSITION pos = m_SymbolAssemblyList->GetHeadPosition();
					pos != NULL;m_SymbolAssemblyList->GetNext(pos)){
		if (m_SymbolAssemblyList->GetAt(pos)->AssemblyName == IN_Name){
			// �����}�`���
			*OUT_SfigFlg = m_SymbolAssemblyList->GetAt(pos)->AssemSymbolType;
			// �����}�`�z�u�׸�
			*OUT_LocFlg = m_SymbolAssemblyList->GetAt(pos)->m_SfigLocateFlag;
			return TRUE;
        }
	}
*/
	SXFFeatureAssemblyC* pValue ;
	if( m_SymbolInfoTable.Lookup(IN_Name, (void*&)pValue) ) {
		// �����}�`���
		*OUT_SfigFlg= pValue->AssemSymbolType ;
		// �����}�`�z�u�׸�
		*OUT_LocFlg	= pValue->m_SfigLocateFlag ;
		return TRUE ;
	}
	return FALSE;
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFReadFeatureManagerC.cpp               �쐬���F2001.2.23
//
//  �P�D�@�\�T�v
//      �����}�`���ɑΉ����镡���}�`��ʂ̐ݒ�
//
//  �Q�D�C���^�[�t�F�[�X
//      BOOL SetLocFlg( LPCTSTR IN_Name)
//
//	    ����: �^			  ������			���e
//            LPCTSTR         IN_Name           Sfig Name
//
//	    ���A�l	
//            ���펞�FTRUE		�����}�`���ɑΉ������ʂ���
//			  �ُ펞�FFALSE		�����}�`���ɑΉ������ʂȂ�
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2001.2.23	   �{��(FQS)
//
//------------------------------------------------------------
BOOL SXFReadFeatureManagerC::SetLocFlg( LPCTSTR IN_Name)
{
/*
	if (m_SymbolAssemblyList == NULL)
		return FALSE;
	for(POSITION pos = m_SymbolAssemblyList->GetHeadPosition();
					pos != NULL;m_SymbolAssemblyList->GetNext(pos)){
		if (m_SymbolAssemblyList->GetAt(pos)->AssemblyName == IN_Name){
			// �����}�`�z�u�׸ނ�ON 
			m_SymbolAssemblyList->GetAt(pos)->m_SfigLocateFlag = 1;
			return TRUE;
        }
	}
*/

/*
	for(int i=0;i<m_SymbolInfoTable.GetSize();i++){
		if (m_SymbolInfoTable[i].name == IN_Name){
			// �����}�`�z�u�׸ނ�ON
			m_SymbolInfoTable[i].locateflag = 1;
			return TRUE;
		}
	}
*/
	SXFFeatureAssemblyC* pValue ;
	if( m_SymbolInfoTable.Lookup(IN_Name, (void*&)pValue) ) {
		// �����}�`�z�u�׸ނ�ON
		pValue->m_SfigLocateFlag = 1 ;
		return TRUE ;
	}
	return FALSE;  
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFReadFeatureManagerC.cpp               �쐬���F2001.2.23
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
//      �쐬		2001.2.23	   �{��(FQS)
//
//------------------------------------------------------------
BOOL SXFReadFeatureManagerC::CheckHatchID( int IN_ID){
	if (m_CurveAssemblyList == NULL)
		return FALSE;
	for(POSITION pos = m_CurveAssemblyList->GetHeadPosition();
				pos != NULL;m_CurveAssemblyList->GetNext(pos)){
		if (m_CurveAssemblyList->GetAt(pos)->AssemblyCode == IN_ID)
			// ��������TRUE�ɂ���̂ł͂Ȃ��Aerror�ł��邩�ǂ��������ׂ�
			if (m_CurveAssemblyList->GetAt(pos)->m_AssemblyErrFlag == TRUE) {
				return TRUE;
			}
			else {
				return FALSE;
			}
	}
	return FALSE;			
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFReadFeatureManagerC.cpp               �쐬���F2001.2.23
//
//  �P�D�@�\�T�v
//      m_CurrentChildList��delete����
//
//  �Q�D�C���^�[�t�F�[�X
//      void Delete_m_CurrentChildList()
//
//	    ����: �^	������	    ���e
//
//	    ���A�l	
//      
//  �R�D����
//	    ����ԍ�    ���t��         �S����		�T�v
//      �쐬		2001.2.23	   �{��(FQS)
//
//------------------------------------------------------------
void SXFReadFeatureManagerC::Delete_m_CurrentChildList(){
	if(m_CurrentChildList != NULL){
		POSITION childpos = m_CurrentChildList->GetHeadPosition();
		while(childpos!=NULL){
			SXFFeatureChildC* child = m_CurrentChildList->GetAt(childpos);
			if(child!=NULL)
				delete child;
			m_CurrentChildList->GetNext(childpos);
		}
		delete m_CurrentChildList;
		m_CurrentChildList = NULL;
	}
}


