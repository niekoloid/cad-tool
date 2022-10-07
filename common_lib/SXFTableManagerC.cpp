//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFTableManagerC.cpp                    �쐬���F2000.04.10
// 
//	�P�D�N���X�T�v
//		��`�e�[�u���f�[�^�l�ƒ�`�e�[�u��Mapping�Ǘ�
//		�I�u�W�F�N�g�̃A�h���X��ێ����A��`�e�[�u��
//		Mapping�Ǘ��I�u�W�F�N�g���Ǘ�����
//
//	�Q�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.10     ��
//
//------------------------------------------------------------
#include "stdafx.h"
#include <math.h>
#include "SXFDataStructC.h"
#include "SXFPreWidthTableC.h"
#include "SXFTableManagerC.h"
#include "SXFStruct.h"
#include "SXFTableMapManagerC.h"
#include "SXFErrorMsgC.h"
#include "SXF_EXT.h"
#include "ComSplitStringC.h"
#include "SXFComInfoC.h"
#include "SXFPart21FileWriteC.h"
#include "SXFInstanceIDC.h"
#include "SXFSplitFeatureC.h"
#include "SXFRGBTableC.h"
#include "SXFPreLineTypeTableC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFTableManagerC.cpp                    �쐬���F2000.04.10
//
//  �P�D�@�\�T�v
//      �N���X�\�z
//
//  �Q�D�C���^�[�t�F�[�X
//		void	SXFTableManagerC::SXFTableManagerC()
//		
//	����	�F	�^		������				���e
//		�Ȃ�
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.10     ��
//
//------------------------------------------------------------
SXFTableManagerC::SXFTableManagerC()
{	
	m_LayerFirstFlag = TRUE;
    m_CurrentType=0;
    m_CurrentNumber=0;
    for(int i=0;i<10;i++)
        m_PreDefWidthFlagTable[i]=0;
	userdefwidthcode=11;		/* հ�ޒ�`�������ނ�11�` */
	m_WriteFile= NULL;
    m_ComInfo=NULL;
    m_InstanceIDManager=NULL;

}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFTableManagerC.cpp                    �쐬���F2000.04.10
//
//  �P�D�@�\�T�v
//      �N���X�\�z
//
//  �Q�D�C���^�[�t�F�[�X
//	void SXFTableManagerC::SXFTableManagerC(SXFComInfoC* IN_CommonInfo)
//		
//	���� �F	�^				������			���e
//			SXFComInfoC*	IN_CommonInfo	���ʏ���޼ު��
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.10     ��
//
//------------------------------------------------------------
SXFTableManagerC::SXFTableManagerC(SXFComInfoC* IN_CommonInfo)
{	
	m_ComInfo = IN_CommonInfo;
	m_LayerFirstFlag = TRUE;
    m_CurrentType=0;
    m_CurrentNumber=0;
    for(int i=0;i<10;i++)
        m_PreDefWidthFlagTable[i]=0;
	m_WriteFile= NULL;
    m_InstanceIDManager=NULL;
	userdefwidthcode=11;		/* հ�ޒ�`�������ނ�11�` */
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFTableManagerC.cpp                    �쐬���F2000.04.10
//
//  �P�D�@�\�T�v
//      �N���X�\�z
//
//  �Q�D�C���^�[�t�F�[�X
//	void SXFTableManagerC::SXFTableManagerC(
//								SXFComInfoC* IN_CommonInfo,
//				                SXFPart21FileWriteC* IN_WriteFile,
//							    SXFInstanceIDC* IN_InstanceIDManager)
//
//		
//	���� �F	�^					  ������				���e
//			SXFComInfoC*		  IN_CommonInfo			���ʏ���޼ު�Ă̱��ڽ
//          SXFPart21FileWriteC*  IN_WriteFile			̧�ُo�͵�޼ު�Ă̱��ڽ
//          SXFInstanceIDC*		  IN_InstanceIDManager	�ݽ�ݽID��޼ު�Ă̱��ڽ
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.10     ��
//
//------------------------------------------------------------
SXFTableManagerC::SXFTableManagerC(SXFComInfoC* IN_CommonInfo,
                     SXFPart21FileWriteC* IN_WriteFile,
                     SXFInstanceIDC* IN_InstanceIDManager)
{
	m_WriteFile= IN_WriteFile;
    m_ComInfo=IN_CommonInfo;
    m_InstanceIDManager=IN_InstanceIDManager;
	m_LayerFirstFlag = TRUE;
    m_CurrentType=0;
    m_CurrentNumber=0;
    for(int i=0;i<10;i++)
        m_PreDefWidthFlagTable[i]=0;
	userdefwidthcode=11;		/* հ�ޒ�`�������ނ�11�` */
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFTableManagerC.cpp                    �쐬���F2000.04.10
//
//  �P�D�@�\�T�v
//      �N���X����
//
//  �Q�D�C���^�[�t�F�[�X
//		void	SXFTableManagerC::~SXFTableManagerC()
//		
//	����	�F	�^		������				���e
//		�Ȃ�
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.10     ��
//
//------------------------------------------------------------
SXFTableManagerC::~SXFTableManagerC()
{
    //delete mapping class in layer table
    for(int i=0;i<m_LayerTable.GetSize();i++){
        if(m_LayerTable[i].m_MappingManager!=NULL)
            delete m_LayerTable[i].m_MappingManager;
    }
    //delete mapping class in predefcolor table
    for( i=0;i<16;i++){
        if(m_PreDefColorTable[i].m_MappingManager!=NULL)
            delete m_PreDefColorTable[i].m_MappingManager;
    }
    //delete mapping class in userdefcolor table
    for( i=0;i<m_UserDefColorTable.GetSize();i++){
        if(m_UserDefColorTable[i].m_MappingManager!=NULL)
            delete m_UserDefColorTable[i].m_MappingManager;
    }
    //delete mapping class in predeffont table
    for( i=0;i<16;i++){
        if(m_PreDefFontTable[i].m_MappingManager!=NULL)
            delete m_PreDefFontTable[i].m_MappingManager;
    }
    //delete mapping class in userdeffont table
    for( i=0;i<m_UserDefFontTable.GetSize();i++){
        if(m_UserDefFontTable[i].m_MappingManager!=NULL)
            delete m_UserDefFontTable[i].m_MappingManager;
    }
    //delete mapping class in width table
    for(i=0;i<16;i++){
        if(m_WidthTable[i].m_MappingManager!=NULL)
            delete m_WidthTable[i].m_MappingManager;
    }
    //delete mapping class in textfont table
    for(i=0;i<m_TextFontTable.GetSize();i++){
        if(m_TextFontTable[i].m_MappingManager!=NULL)
            delete m_TextFontTable[i].m_MappingManager;
    }
}


//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFTableManagerC.cpp                    �쐬���F2000.04.10
//
//  �P�D�@�\�T�v
//      Feature Comment Table Instance��o�^����(READ)
//      
//  �Q�D�C���^�[�t�F�[�X
//      BOOL RegisterFeatureTable( INSTANCEDATA *IN_Instance )
//
//	    ����: �^			  ������		    ���e
//            INSTANCEDATA*   IN_Instance       Instance��
//                                              �\���̂̃A�h���X 
//      
//	    ���A�l	
//            ���펞�FTRUE
//			  �ُ펞�FFALSE
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.10     ��
//
//------------------------------------------------------------
BOOL SXFTableManagerC::RegisterFeatureTable(INSTANCEDATA *IN_Instance )
{
	/** ���C�� **/
    if(IN_Instance->EntityName == "layer_feature"){
        SXFLayerC layer;
		/* ڲԺ��� */
        INT_PTR layercode = m_LayerTable.GetSize()+1;
		/** �ő僌�C�����𒴂����Ƃ��G���[ **/
        if (layercode > MAXLAYER){// max layer code = 256 
			SXFErrorMsgC::RecordError(SXFMAXLAYER,"LAYER",0);
			return FALSE;
		}
		/* ڲԺ��ސݒ� */
        layer.m_Code = (int)layercode;
        CStringArray* array;
        SXFSplitFeatureC split(IN_Instance->EntityData);
        array = split.Split();
        if(array == NULL)
            return FALSE;
        if (array->GetSize() != 2) // syntax err
            return FALSE;
		/* ڲԖ� */
        layer.m_Name = (* array)[0];
		//���C�������w�肳��Ă��Ȃ��Ƃ�
		if (strlen(layer.m_Name) == 0){
			SXFErrorMsgC::RecordError(SXFNOTSETLNAME,"LAYER",0);
			return FALSE;
		}
		/* ڲԖ�������ð��ٓ��ɂ���δװ */
        if (!CheckSameLayer(layer.m_Name)){
			SXFErrorMsgC::RecordError(SXFSAMENAME,"LAYER",1,layer.m_Name);
			return FALSE;
		}
		/* �\���^��\���׸� */
        int lfflg = atoi( (* array)[1] );
        layer.m_LfFlag = lfflg;
		//�\���^��\���t���O�̃`�F�b�N
		if (layer.m_LfFlag < 0 || layer.m_LfFlag > 1) {
			SXFErrorMsgC::RecordError(SXFLAYERFLAG,"LAYER",1,layer.m_LfFlag);
			return FALSE;
		}
		/* ��`ð��ٗv�fMapping�Ǘ���޼ު�Đ��� */
        SXFTableMapManagerC* mappingmanager = new SXFTableMapManagerC(); 
		/* ڲԏ��� */
        mappingmanager->SetFeatureData( 1 ,&layer );//class type && ptr of the class
		/* �ݽ�ݽID��� */
        layer.m_ID = IN_Instance->InstanceID;
		/* ��`ð��ٗv�fMapping�Ǘ���޼ު�ľ�� */
        layer.m_MappingManager = mappingmanager;
		/* ڲ�ð��قɒǉ� */
        m_LayerTable.Add(layer);
    }
	/** ����`�F **/
	else if(IN_Instance->EntityName == "pre_defined_colour_feature"){
        SXFPreDefColorC predefcolor;
        CStringArray* array;
        SXFSplitFeatureC split(IN_Instance->EntityData);
        array = split.Split();
        if(array == NULL)
            return FALSE;
        if (array->GetSize() != 1) // syntax err
            return FALSE;
		/* ����`�F�ȊO�̖��O�̂Ƃ� */
        if (!predefcolor.SetName((* array)[0])){
			SXFErrorMsgC::RecordError(SXFNOTPRECOLOUR,"PREDEFINED_COLOUR",1,(* array)[0]);
			return FALSE;
		}
		/* �F��������ð��ٓ��ɂ���Ƃ� */
		if (!CheckSamePreDefColor((* array)[0])){
			SXFErrorMsgC::RecordError(SXFSAMENAME,"PREDEFINED_COLOUR",1,(* array)[0]);
			return FALSE;
		}
		/* ��`ð��ٗv�fMapping�Ǘ���޼ު�Đ��� */
        SXFTableMapManagerC* mappingmanager = new SXFTableMapManagerC(); 
		/* �F����� */
        mappingmanager->SetFeatureData(2,&predefcolor);
		/* ��`ð��ٗv�fMapping�Ǘ���޼ު�Ă�� */
        predefcolor.m_MappingManager=mappingmanager;
		/* �ݽ�ݽID��� */
        predefcolor.m_ID = IN_Instance->InstanceID;
		/* ����`�Fð��قɒǉ� */
        m_PreDefColorTable[predefcolor.m_Code-1] = predefcolor;
    }
	/** ���[�U��`�F **/
	else if(IN_Instance->EntityName == "user_defined_colour_feature"){
        SXFUserDefColorC userdefcolor;
        userdefcolor.m_Code = (int) m_UserDefColorTable.GetSize()+17;
		/** �ő�F���𒴂����Ƃ��G���[���� **/
        if(userdefcolor.m_Code > MAXCOLOUR){
			SXFErrorMsgC::RecordError(SXFMAXUSERCOLOUR,"USERDEFINED_COLOUR",0);
			return FALSE;
		}
        CStringArray* array;
        SXFSplitFeatureC split(IN_Instance->EntityData);
        array = split.Split();
        if(array == NULL)
            return FALSE;
        if (array->GetSize() != 3) // syntax err
            return FALSE;
        userdefcolor.R=atoi( (* array)[0] );
        userdefcolor.G=atoi( (* array)[1] );
        userdefcolor.B=atoi( (* array)[2] );
		//R�l��0����255�łȂ��Ƃ�
		if ((userdefcolor.R < 0) || (userdefcolor.R > MAXRGB)){
			SXFErrorMsgC::RecordError(SXFRGBERROR,
										"USERDEFINED_COLOUR",
										1,
										userdefcolor.R);
			return FALSE;
		}
		//G�l��0����255�łȂ��Ƃ�
		if ((userdefcolor.G < 0) || (userdefcolor.G > MAXRGB)){
			SXFErrorMsgC::RecordError(SXFRGBERROR,
										"USERDEFINED_COLOUR",
										1,
										userdefcolor.G);
			return FALSE;
		}
		//B�l��0����255�łȂ��Ƃ�
		if ((userdefcolor.B < 0) || (userdefcolor.B > MAXRGB)){
			SXFErrorMsgC::RecordError(SXFRGBERROR,
										"USERDEFINED_COLOUR",
										1,
										userdefcolor.B);
			return FALSE;
		}
		/* ��`ð��ٗv�fMapping�Ǘ���޼ު�Đ��� */
        SXFTableMapManagerC* mappingmanager = new SXFTableMapManagerC(); 
		/* հ�ޒ�`�F���� */
        mappingmanager->SetFeatureData(3,&userdefcolor);
		/* ��`ð��ٗv�fMapping�Ǘ���޼ު�ľ�� */
        userdefcolor.m_MappingManager=mappingmanager;
		/* �ݽ�ݽID��� */
        userdefcolor.m_ID = IN_Instance->InstanceID;
		/* հ�ޒ�`�Fð��قɒǉ� */
        m_UserDefColorTable.Add(userdefcolor);
    }
	/** ����`���� **/
	else if(IN_Instance->EntityName == "pre_defined_font_feature"){
        SXFPreDefFontC predeffont;
        CStringArray* array;
        SXFSplitFeatureC split(IN_Instance->EntityData);
        array = split.Split();
        if(array == NULL)
            return FALSE;
        if (array->GetSize() != 1) // syntax err
            return FALSE;
        CString predeffontname=(* array)[0];
		/* ����`���햼�łȂ� */
        if (!predeffont.SetName(predeffontname)){
			SXFErrorMsgC::RecordError(SXFNOTPRETYPE,
										"PREDEFINED_LINETYPE",
										1,
										predeffontname);
			return FALSE;
		}
		/* ����`���햼������ð��ٓ��ɂ��� */
		if (!CheckSamePreDefFont(predeffontname)){
			SXFErrorMsgC::RecordError(SXFSAMENAME,
										"PREDEFINED_LINETYPE",
										1,
										predeffontname);
			return FALSE;
		}
		/* ��`ð��ٗv�fMapping�Ǘ���޼ު�Đ��� */
        SXFTableMapManagerC* mappingmanager = new SXFTableMapManagerC(); 
		/* ����`�������� */
        mappingmanager->SetFeatureData(4,&predeffont);
		/* ��`ð��ٗv�fMapping�Ǘ���޼ު�ľ�� */
        predeffont.m_MappingManager=mappingmanager;
		/* �ݽ�ݽID��� */
        predeffont.m_ID = IN_Instance->InstanceID;
		/* ����`����ð��قɒǉ� */
        m_PreDefFontTable[predeffont.m_Code-1] = predeffont;
    }
	/** ���[�U��`���� **/
	else if(IN_Instance->EntityName == "user_defined_font_feature"){
        SXFUserDefFontC userdeffont;
        userdeffont.m_Code = (int) m_UserDefFontTable.GetSize()+17;//17---
		/** �ő���퐔�𒴂����ꍇ�G���[���� **/
        if( userdeffont.m_Code > MAXLINETYPE){
			SXFErrorMsgC::RecordError(SXFMAXUSERLINETYPE,
										"USERDEFINED_LINETYPE",
										0);
			return FALSE;
		}
        CStringArray* array;
        SXFSplitFeatureC split(IN_Instance->EntityData);
        array = split.Split();
        if(array == NULL)
            return FALSE;
        if (array->GetSize() !=3 ) // syntax err
            return FALSE;
        userdeffont.m_Name = (* array)[0];
		/* հ�ޒ�`���햼�����ł�ð��ٓ��ɂ��� */
		if (!CheckSameUserDefFont(userdeffont.m_Name)){
			SXFErrorMsgC::RecordError(SXFSAMENAME,
										"USERDEFINED_LINETYPE",
										1,
										userdeffont.m_Name);
			return FALSE;
		}
        userdeffont.m_Segment=atoi((* array)[1]);
		/////////////////////////
		//Segment�̃`�F�b�N
		/////////////////////////
		//�Z�O�����g�����Q�̔{���łȂ��Ƃ�
		if ((userdeffont.m_Segment % 2) != 0){
			SXFErrorMsgC::RecordError(SXFSEGMENTERROR,
										"USERDEFINED_LINETYPE",
										1,
										userdeffont.m_Segment);
			return FALSE;
		}
		//�Z�O�����g�����Q����W�łȂ��Ƃ�
		if ((userdeffont.m_Segment < MINSEGMENT) 
				|| (userdeffont.m_Segment > MAXSEGMENT)){
			SXFErrorMsgC::RecordError(SXFSEGMENTERROR,
										"USERDEFINED_LINETYPE",
										1,
										userdeffont.m_Segment);
			return FALSE;
		}
        CStringArray* arraysecond;
        (* array)[2].TrimLeft('(');
        (* array)[2].TrimRight(')');
        ComSplitStringC splitsecond((* array)[2]);
        arraysecond = splitsecond.Split(',');
        if(userdeffont.m_Segment != arraysecond->GetSize())
            return FALSE;//// syntax err
		double pitch;
        for(int i=0; i < userdeffont.m_Segment; i++){
			pitch = atof((* arraysecond)[i]);
			/* �s�b�`���K��͈͊O */
			if (double_check(pitch) < 0 ){
				SXFErrorMsgC::RecordError(SXFPITCHERROR,
											"USERDEFINED_LINETYPE",
											1,
											pitch);
				return FALSE;
			}
            userdeffont.m_Pitch.Add(pitch);
        }
		/* ��`ð��ٗv�fMapping�Ǘ���޼ު�Đ��� */
        SXFTableMapManagerC* mappingmanager = new SXFTableMapManagerC(); 
		/* հ�ޒ�`�������� */
        mappingmanager->SetFeatureData(5,&userdeffont);
		/* ��`ð��ٗv�fMapping�Ǘ���޼ު�ľ�� */
        userdeffont.m_MappingManager=mappingmanager;
		/* �ݽ�ݽID��� */
        userdeffont.m_ID = IN_Instance->InstanceID;
		/* հ�ޒ�`����ð��قɒǉ� */
        m_UserDefFontTable.Add(userdeffont);
    }
	/** ���� **/
	else if(IN_Instance->EntityName == "width_feature"){
        SXFWidthC width;
        CStringArray* array;
        SXFSplitFeatureC split(IN_Instance->EntityData);
        array = split.Split();
        if(array == NULL)
            return FALSE;
        if (array->GetSize() != 1 ) // syntax err
            return FALSE;
        double inwidth=atof( (* array)[0] );
		//�������K��͈͊O
		if (double_check(inwidth) < 0){
			SXFErrorMsgC::RecordError(SXFWIDTHERROR,
										"LINE_WIDTH",
										1,
										inwidth);
			return FALSE;
		}
		double Eps, Angle_Eps;
		m_ComInfo->Get_Tolerance(Eps,Angle_Eps);
		/* �����ɑΉ�����������ނ����߂� */
        int resaultcode = width.InquireCode(inwidth,Eps);
		/* �Ή�����������ނ������(����`) */
        if(resaultcode != 0){
			/* ����������ð��ٓ��ɂ���� */
            if(m_PreDefWidthFlagTable[resaultcode-1] == 1){
				SXFErrorMsgC::RecordError(SXFSAMEWIDTH,
											"LINE_WIDTH",
											1,
											inwidth);
				return FALSE;
            }
			/* ��`�ς��׸ނ�ON */
            m_PreDefWidthFlagTable[resaultcode-1]=1;
			/* �������ނ�� */
            width.m_Code = resaultcode;
            SXFPreWidthTableC prewidthtable;
            double prewidth;
			/* ���ނɑΉ�������������߂� */
            prewidthtable.GetPreWidth(resaultcode, prewidth); 
            width.m_Width = prewidth;
        }
		/* �Ή�����������ނ��Ȃ�(����`�łȂ�) */
		else{
			/* �ő�������𒴂����Ƃ� */
            if (userdefwidthcode > MAXLINEWIDTH){//widthcode 1---16
				SXFErrorMsgC::RecordError(SXFMAXLINEWIDTH,
											"LINE_WIDTH",
											0);
                return FALSE;
            }
			/* �������޾�� */
            width.m_Code = userdefwidthcode;
            userdefwidthcode++;
			/* ������� */
            width.m_Width=inwidth;
        }
		/* ��`ð��ٗv�fMapping�Ǘ���޼ު�Đ��� */
        SXFTableMapManagerC* mappingmanager = new SXFTableMapManagerC(); 
		/* ��������� */
        mappingmanager->SetFeatureData(6,&width);
		/* ��`ð��ٗv�fMapping�Ǘ���޼ު�ľ�� */
        width.m_MappingManager=mappingmanager;
		/* �ݽ�ݽID��� */
        width.m_ID = IN_Instance->InstanceID;
		/* ����ð��ْǉ� */
        m_WidthTable[width.m_Code-1] = width;
    }
	/** �����t�H���g **/
	else if(IN_Instance->EntityName == "text_font_feature"){       
        SXFTextFontC textfont;
        CStringArray* array;
        SXFSplitFeatureC split(IN_Instance->EntityData);
        array = split.Split();
        if(array == NULL)
            return FALSE;
        if (array->GetSize() != 1 ) // syntax err
            return FALSE;
        textfont.m_Name = (* array)[0];
		//�����t�H���g���̒������O�̓G���[
		if (textfont.m_Name.GetLength() <= 0){
			SXFErrorMsgC::RecordError(SXFFONTNAMEERROR,
										"TEXT_FONT",
										0);
			return FALSE;
		}
		/* ����̫�Ė�������ð��قɂ��� */
		if (!CheckSameTextFont(textfont.m_Name)){
			SXFErrorMsgC::RecordError(SXFSAMENAME,
										"TEXT_FONT",
										1,
										textfont.m_Name);
			return FALSE;
		}
		/* ����̫�ĺ��޾�� */
        textfont.m_Code = (int) m_TextFontTable.GetSize()+1;        
		/* �ő啶��̫�Đ��𒴂����ꍇ */
        if (textfont.m_Code > MAXTEXTFONT){//textfont 1--1024
            //error
			SXFErrorMsgC::RecordError(SXFMAXTEXTFONT,
										"TEXT_FONT",
										0);
			return FALSE;
        }
		/* ��`ð��ٗv�fMapping�Ǘ���޼ު�Đ��� */
        SXFTableMapManagerC* mappingmanager = new SXFTableMapManagerC(); 
		/* ����̫�ď��� */
        mappingmanager->SetFeatureData(7,&textfont);
		/* ��`ð��ٗv�fMapping�Ǘ���޼ު�ľ�� */
        textfont.m_MappingManager=mappingmanager;
		/* �ݽ�ݽID��� */
        textfont.m_ID = IN_Instance->InstanceID;
		/* ����̫��ð��قɒǉ� */
        m_TextFontTable.Add(textfont);
    }
    return TRUE;

}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFTableManagerC.cpp                    �쐬���F2000.04.10
//
//  �P�D�@�\�T�v
//      Table �v�f�̍\���̂�o�^����(WRITE)
//      
//  �Q�D�C���^�[�t�F�[�X
//      int RegisterStructTable( int IN_Type, LPVOID IN_Struct)
//
//	    ����: �^			  ������			    ���e
//            int             IN_Type              �\���̂�Type
//            LPVOID          IN_Struct            �\���̂̃A�h���X
//                                                  
//      
//	    ���A�l	
//            ���펞�F Table �v�f��Code
//			  �ُ펞�F ��(�G���[�R�[�h)
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.10     ��
//
//------------------------------------------------------------
int SXFTableManagerC::RegisterStructTable( int IN_Type, LPVOID IN_Struct)
{
	int return_code;
	SXFTableMapManagerC* mappingmanager; 
	SXFLayerC layer;
	SXFPreDefColorC predefcolor;
	SXFUserDefColorC userdefcolor;
	SXFPreDefFontC predeffont;
	SXFUserDefFontC userdeffont;
	SXFWidthC width;
	double inwidth;
	int resaultcode;
	SXFTextFontC textfont;
	int i = 0;
	INT_PTR layersize;
	INT_PTR usercolorsize;
	INT_PTR userfontsize;
	INT_PTR textfontsize;
	double eps1,eps2;
	int InstanceID;

	switch(IN_Type)
    {
		/** ���C�� **/
		case 1:
			/* ڲ�ð��ٻ��� */
			layersize = m_LayerTable.GetSize();
			/* �ő�ڲԐ��𒴂����Ƃ� */
			if (layersize >= MAXLAYER){// max layer code = 256 
				SXFErrorMsgC::RecordError(SXFMAXLAYER,"LAYER",0);
				return SXFMAXLAYER;
			}
			/* ڲԺ��� */
			layer.m_Code = (int)layersize+1;
			/* ڲԖ� */
			layer.m_Name = ((Layer_Struct*)IN_Struct)->name;
			/* �\���^��\���׸� */
			layer.m_LfFlag = ((Layer_Struct*)IN_Struct)->lflag;
			/* ��`ð��ٗv�fMapping�Ǘ���޼ު�Đ��� */
			mappingmanager = new SXFTableMapManagerC(m_WriteFile,
														m_InstanceIDManager);
			/* ���A�l(ڲԺ���) */
			return_code = layer.m_Code;
			/* ��`ð��ٗv�fMapping�Ǘ���޼ު�ľ�� */
			layer.m_MappingManager = mappingmanager;
			/* ڲ�ð��قɒǉ� */
			m_LayerTable.Add(layer);
			break;
		/** ����`�F **/
		case 2://predefcolor 16
			//����`�łȂ����O�̓G���[
			if (!predefcolor.SetName(((Predefined_Colour_Struct*)IN_Struct)->name)){
				SXFErrorMsgC::RecordError(SXFNOTPRECOLOUR,
											"PREDEFINED_COLOUR",
											1,
											((Predefined_Colour_Struct*)IN_Struct)->name);
				return SXFNOTPRECOLOUR;
			}
			/* ��`ð��ٗv�fMapping�Ǘ���޼ު�Đ��� */
			mappingmanager = new SXFTableMapManagerC(m_WriteFile,
														m_InstanceIDManager);
			/* ����`�F�\���̾�� */
			mappingmanager->SetStructPrecolor(IN_Type,
												IN_Struct,
												predefcolor);
			/* ����`�F�ݽ�ݽ�o�� */
			return_code = mappingmanager->WriteInstance(&InstanceID);
			/* �o�͎��s */
			if (return_code){
				delete mappingmanager;
				break;
			}
			/* ��`ð��ٗv�fMapping�Ǘ���޼ު�ľ�� */
			predefcolor.m_MappingManager=mappingmanager;
			/* ���A�l(�F����) */
			return_code = predefcolor.m_Code;
			/* �ݽ�ݽID */
			predefcolor.m_ID = InstanceID;
			/* ����`�Fð��قɒǉ� */
			m_PreDefColorTable[predefcolor.m_Code-1] = predefcolor;
			break;
		/** ���[�U��`�F **/
		case 3://userdefcolor
			/* հ�ޒ�`�Fð��ٻ��� */
			usercolorsize = m_UserDefColorTable.GetSize();
			///ERROR
			//���[�U��`��240�F������`�ł��Ȃ��B
			if (usercolorsize >= MAXUSERCOLOUR){
				SXFErrorMsgC::RecordError(SXFMAXUSERCOLOUR,
											"USERDEFINED_COLOUR",
											0);
				return SXFMAXUSERCOLOUR;
			}
			/* ��`ð��ٗv�fMapping�Ǘ���޼ު�� */
			mappingmanager = new SXFTableMapManagerC(m_WriteFile,
													m_InstanceIDManager);
			/* �F���� */
			userdefcolor.m_Code = (int)usercolorsize+17;//17------
			/* RGB�l */
			userdefcolor.R =((Userdefined_Colour_Struct*)IN_Struct)->red;
			userdefcolor.G =((Userdefined_Colour_Struct*)IN_Struct)->green;
			userdefcolor.B =((Userdefined_Colour_Struct*)IN_Struct)->blue;
			/* հ�ޒ�`�F�\���̾�� */
			mappingmanager->SetStructData(IN_Type,IN_Struct);
			/* հ�ޒ�`�F�ݽ�ݽ�o�� */
			return_code = mappingmanager->WriteInstance(&InstanceID);
			/* �o�͎��s */
			if (return_code){
				delete mappingmanager;
				break;
			}
			/* ��`ð��ٗv�fMapping�Ǘ���޼ު�ľ�� */
			userdefcolor.m_MappingManager=mappingmanager;
			/* ���A�l(�F����) */
			return_code = userdefcolor.m_Code;
			/* �ݽ�ݽID��� */
			userdefcolor.m_ID = InstanceID;
			/* հ�ޒ�`�Fð��قɒǉ� */
			m_UserDefColorTable.Add(userdefcolor);
			break;
		/** ����`���� **/
		case 4://predeffont
			//����`�łȂ����O�̓G���[
			if (!predeffont.SetName(((Predefined_Linetype_Struct*)IN_Struct)->name)){
				SXFErrorMsgC::RecordError(SXFNOTPRETYPE,
										"PREDEFINED_LINETYPE",
										1,
										((Predefined_Linetype_Struct*)IN_Struct)->name);
				return SXFNOTPRETYPE;
			}
			/* ��`ð��ٗv�fMapping�Ǘ���޼ު�Đ��� */
			mappingmanager = new SXFTableMapManagerC(m_WriteFile,
													m_InstanceIDManager);
			/* ����`����\���̾�� */
			mappingmanager->SetStructData(IN_Type,IN_Struct);
			/* ����`����ݽ�ݽ�o�� */
			return_code = mappingmanager->WriteInstance(&InstanceID);
			/* �o�͎��s */
			if (return_code){
				delete mappingmanager;
				break;
			}
			/* ��`ð��ٗv�fMapping�Ǘ���޼ު�ľ�� */
			predeffont.m_MappingManager=mappingmanager;
			/* ���A�l(������) */
			return_code = predeffont.m_Code;
			/* �ݽ�ݽID */
			predeffont.m_ID = InstanceID;
			/* ����`����ð��ْǉ� */
			m_PreDefFontTable[predeffont.m_Code-1] = predeffont;
			break;
		/** ���[�U��`���� **/
		case 5://userdeffont
			/* հ�ޒ�`����ð��ٻ��� */
			userfontsize = m_UserDefFontTable.GetSize();
			///ERROR
			//���[�U��`�����32������`�ł��Ȃ��B
			if (userfontsize >= MAXUSERLINETYPE){
				SXFErrorMsgC::RecordError(SXFMAXUSERLINETYPE,
											"USERDEFINED_LINETYPE",
											0);
				return SXFMAXUSERLINETYPE;
			}
			/* ������ */
			userdeffont.m_Code = (int) userfontsize+17;//17---
			/* ���햼 */
			userdeffont.m_Name = ((Userdefined_Linetype_Struct*)IN_Struct)->name;
			/* �����Đ� */
			userdeffont.m_Segment=((Userdefined_Linetype_Struct*)IN_Struct)->segment;
			/* �߯� */
			for(i=0;i<userdeffont.m_Segment;i++)
				userdeffont.m_Pitch.Add( ((Userdefined_Linetype_Struct*)IN_Struct)->pitch[i] );
			/* ��`ð��ٗv�fMapping�Ǘ���޼ު�Đ��� */
			mappingmanager = new SXFTableMapManagerC(m_WriteFile,m_InstanceIDManager);
			/* հ�ޒ�`����\���̾�� */
			mappingmanager->SetStructData(IN_Type,IN_Struct);
			/* հ�ޒ�`����ݽ�ݽ�o�� */
			return_code = mappingmanager->WriteInstance(&InstanceID);
			/* �o�͎��s */
			if (return_code){
				delete mappingmanager;
				break;
			}
			/* ��`ð��ٗv�fMapping�Ǘ���޼ު�ľ�� */
			userdeffont.m_MappingManager=mappingmanager;
			/* �ԋp�l(������) */
			return_code = userdeffont.m_Code;
			/* �ݽ�ݽID */
			userdeffont.m_ID = InstanceID;
			/* հ�ޒ�`����ð��ْǉ� */
			m_UserDefFontTable.Add(userdeffont);
			break;
		/** ���� **/
		case 6://width
			/* ���� */
			inwidth = ((Line_Width_Struct*)IN_Struct)->width;
			/* ���e�덷�擾 */
			m_ComInfo->Get_Tolerance(eps1,eps2);
			/* ��������������ނ����߂� */
			resaultcode = width.InquireCode(inwidth,eps1);
			/* �����ɑΉ�����������ނ�����(����`) */
			if(resaultcode != 0){
				/* ����ð��ٓ��ɂ��� */
				if(m_PreDefWidthFlagTable[resaultcode-1] == 1){
					SXFErrorMsgC::RecordError(SXFSAMEWIDTH,
												"LINE_WIDTH",
												1,
												inwidth);
					return SXFSAMEWIDTH;
				}
				/* ��`�ς��׸ނ�ON */
				m_PreDefWidthFlagTable[resaultcode-1]=1;
				/* �������� */
				width.m_Code = resaultcode;
				SXFPreWidthTableC prewidthtable;
				double prewidth = 0.0;
				/* �������ނ���������擾 */
				prewidthtable.GetPreWidth(resaultcode, prewidth); 
				/* ���� */
				width.m_Width = prewidth;
			}
			//�����ɑΉ�����R�[�h���O�̂Ƃ��͊���`�ł͂Ȃ��B
			else{
				//�������P�U�ȏ�o�^����Ă����
				//����ȏ�o�^�ł��Ȃ��̂ŁA�G���[
				if (userdefwidthcode > MAXLINEWIDTH){//widthcode 1---16
  					SXFErrorMsgC::RecordError(SXFMAXLINEWIDTH,
												"LINE_WIDTH",
												0);
					return SXFMAXLINEWIDTH;
				}
				/* �������� */
				width.m_Code = userdefwidthcode;
				userdefwidthcode++;
				/* ���� */
				width.m_Width=inwidth;
			}
			/* ��`ð��ٗv�fMapping�Ǘ���޼ު�Đ��� */
			mappingmanager = new SXFTableMapManagerC(m_WriteFile,
														m_InstanceIDManager);
			/* �����\���̾�� */
			mappingmanager->SetStructData(IN_Type,IN_Struct);
			/* �����ݽ�ݽ�o�� */
			return_code = mappingmanager->WriteInstance(&InstanceID);
			/* �o�͎��s */
			if (return_code){
				delete mappingmanager;
				break;
			}
			/* ��`ð��ٗv�fMapping�Ǘ���޼ު�ľ�� */
			width.m_MappingManager=mappingmanager;
			/* ���A�l(��������) */
			return_code = width.m_Code;
			/* �ݽ�ݽID */
			width.m_ID = InstanceID;
			/* ����ð��قɒǉ� */
			m_WidthTable[width.m_Code-1] = width;
			break;
		/** �����t�H���g **/
		case 7://textfont
			//ERROR
			//�����t�H���g�͂P�O�Q�S�����o�^�ł��Ȃ�
			textfontsize = m_TextFontTable.GetSize();
			if (textfontsize >= MAXTEXTFONT){//textfont 1--1024
				SXFErrorMsgC::RecordError(SXFMAXTEXTFONT,"TEXT_FONT",0);
				return SXFMAXTEXTFONT;
			}
			/* ����̫�Ė� */
			textfont.m_Name = ((Text_Font_Struct*)IN_Struct)->name;
			/* ����̫�ĺ��� */
			textfont.m_Code = (int) textfontsize+1;
			/* ��`ð��ٗv�fMapping�Ǘ���޼ު�Đ��� */
			mappingmanager = new SXFTableMapManagerC(m_WriteFile,
													m_InstanceIDManager);
			/* ����̫�č\���̾�� */
			mappingmanager->SetStructData(IN_Type,IN_Struct);
			/* ����̫�Ĳݽ�ݽ�o�� */
			return_code = mappingmanager->WriteInstance(&InstanceID);
			/* �o�͎��s */
			if (return_code){
				delete mappingmanager;
				break;
			}
			/* ��`ð��ٗv�fMapping�Ǘ���޼ު�ľ�� */
			textfont.m_MappingManager=mappingmanager;
			/* ����̫�ĺ��� */
			return_code = textfont.m_Code;
			/* �ݽ�ݽID */
			textfont.m_ID = InstanceID;
			/* ����̫��ð��قɒǉ� */
			m_TextFontTable.Add(textfont);
			break;
    }
    return return_code;
}
//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFTableManagerC.cpp                    �쐬���F2000.04.10
//
//  �P�D�@�\�T�v
//      �w�肵��Table�v�f��Code����`����Ă��邩�`�F�b�N
//      
//  �Q�D�C���^�[�t�F�[�X
//      int GetID(int IN_Type, int IN_Code)
//
//	    ����: �^			  ������			    ���e
//            int             IN_Type              Table�v�f��Type
//            int             IN_Code              Table�v�f��Code
//                                                  
//      
//	    ���A�l	
//            ���펞�F ��	:��`����Ă���
//			  �ُ펞�F -1	:��`����Ă��Ȃ�
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.10     ��
//
//------------------------------------------------------------
int SXFTableManagerC::GetID(int IN_Type, int IN_Code)
{
    int getid,RW_Flag;

    if(IN_Code<1)  //code must >=1
		return -1;
	/* �Ǐ����׸ގ擾 */
	m_ComInfo->Get_RWFlag(RW_Flag);

    getid=-1;
    switch (IN_Type){
		case 1://layer
			if(IN_Code > m_LayerTable.GetSize())
				return -1;//layer code not register
			getid = m_LayerTable[IN_Code-1].m_LfFlag;//�e�[�u���ɓo�^����Ă��Ȃ���Ώ����l-�P
			break;
		case 2://predefcolor
			if(IN_Code>16)
				return -1;//predefcolor must <= 16
			getid = m_PreDefColorTable[IN_Code-1].m_ID;
			break;
		case 3://userdefcolor
			if(IN_Code<17 || IN_Code>=m_UserDefColorTable.GetSize()+17)
				return -1;//userdefcolor code must 17---256
						  //or user def color not register
			getid=m_UserDefColorTable[IN_Code-17].m_ID;
			break;
		case 4://predeffont
			if(IN_Code>16)
				return -1;//predeffont code must <=16
			getid = m_PreDefFontTable[IN_Code-1].m_ID;
			break;
		case 5://userdeffont
			if(IN_Code<17 || IN_Code>=m_UserDefFontTable.GetSize()+17)
				return -1;//user def font code 17---32
						  //or user def font not register
			getid = m_UserDefFontTable[IN_Code-17].m_ID;
			break;
		case 6://width
			if(IN_Code>16)
				return -1;//width code 1--16
			getid=m_WidthTable[IN_Code-1].m_ID;
			break;
		case 7://textfont
			if(IN_Code>m_TextFontTable.GetSize())
				return -1;//text font must 1--1024
						  //text font not register
			getid=m_TextFontTable[IN_Code-1].m_ID;
			break;
		default:
			break;
	} 
    return getid;//-1:error, ID:OK
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFTableManagerC.cpp                    �쐬���F2000.04.10
//
//  �P�D�@�\�T�v
//      �w�肵��Layer Name����`����Ă��邩�`�F�b�N
//      
//  �Q�D�C���^�[�t�F�[�X
//      BOOL CheckSameLayer( LPCTSTR IN_Name)
//
//	    ����: �^			  ������			    ���e
//            LPCTSTR        IN_Name               Layer Name                        
//      
//	    ���A�l	
//            ���펞�F TRUE
//			  �ُ펞�F FALSE
//      
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.10     ��
//
//------------------------------------------------------------
BOOL SXFTableManagerC::CheckSameLayer( LPCTSTR IN_Name)
{
    for(int i=0;i<m_LayerTable.GetSize();i++){
        if(IN_Name == m_LayerTable[i].m_Name)
            return FALSE;
    }
    
    return TRUE;
}
//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFTableManagerC.cpp                    �쐬���F2000.04.10
//
//  �P�D�@�\�T�v
//      �w�肵��PreDefColor Name����`����Ă��邩�`�F�b�N
//      
//  �Q�D�C���^�[�t�F�[�X
//      BOOL CheckSamePreDefColor( LPCTSTR IN_Name)
//
//	    ����: �^			  ������			    ���e
//            LPCTSTR        IN_Name               PreDefColor Name                        
//      
//	    ���A�l	
//            ���펞�F TRUE
//			  �ُ펞�F FALSE
//      
//  �Q�D�C���^�[�t�F�[�X
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.10     ��
//
//------------------------------------------------------------
BOOL SXFTableManagerC::CheckSamePreDefColor( LPCTSTR IN_Name)
{
    for(int i=0;i<16;i++){
        if(IN_Name == m_PreDefColorTable[i].m_Name)
            return FALSE;
    }

    return TRUE;
}
//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFTableManagerC.cpp                    �쐬���F2000.04.10
//
//  �P�D�@�\�T�v
//      �w�肵��PreDefFont Name����`����Ă��邩�`�F�b�N
//      
//  �Q�D�C���^�[�t�F�[�X
//      BOOL CheckSamePreDefFont( LPCTSTR IN_Name)
//
//	    ����: �^			  ������			    ���e
//            LPCTSTR        IN_Name               PreDefFont Name                        
//      
//	    ���A�l	
//            ���펞�F TRUE
//			  �ُ펞�F FALSE
//      
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.10     ��
//
//------------------------------------------------------------
BOOL SXFTableManagerC::CheckSamePreDefFont( LPCTSTR IN_Name)
{
    for(int i=0;i<16;i++){
        if(IN_Name == m_PreDefFontTable[i].m_Name)
            return FALSE;
    }
    return TRUE;
}
//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFTableManagerC.cpp                    �쐬���F2000.04.10
//
//  �P�D�@�\�T�v
//      �w�肵��UserDefFont Name����`����Ă��邩�`�F�b�N
//      
//  �Q�D�C���^�[�t�F�[�X
//      BOOL CheckSameUserDefFont( LPCTSTR IN_Name)
//
//	    ����: �^			  ������			    ���e
//            LPCTSTR        IN_Name               UserDefFont Name                        
//      
//	    ���A�l	
//            ���펞�F TRUE
//			  �ُ펞�F FALSE
//      
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.10     ��
//
//------------------------------------------------------------
BOOL SXFTableManagerC::CheckSameUserDefFont( LPCTSTR IN_Name)
{
    for(int i=0;i<m_UserDefFontTable.GetSize();i++){
        if(IN_Name == m_UserDefFontTable[i].m_Name)
            return FALSE;
    }

    return TRUE;
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFTableManagerC.cpp                    �쐬���F2000.04.10
//
//  �P�D�@�\�T�v
//      �w�肵��Width�l����`����Ă��邩�`�F�b�N
//      
//  �Q�D�C���^�[�t�F�[�X
//      BOOL CheckSameWidth( double IN_Width)
//
//	    ����: �^			  ������			    ���e
//            double         IN_Width              Width�l                        
//      
//	    ���A�l	
//            ���펞�F TRUE
//			  �ُ펞�F FALSE
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.10     ��
//
//------------------------------------------------------------
BOOL SXFTableManagerC::CheckSameWidth( double IN_Width)
{
	double eps,angle_eps;
	m_ComInfo->Get_Tolerance(eps,angle_eps);
    SXFPreWidthTableC prewidthtable;
    int code = prewidthtable.GetCode(IN_Width,eps);
    if(m_PreDefWidthFlagTable[code-1] == 1){
        return FALSE;
    }
    return TRUE;
}
//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFTableManagerC.cpp                    �쐬���F2000.04.10
//
//  �P�D�@�\�T�v
//      �w�肵��TextFont����`����Ă��邩�`�F�b�N
//      
//  �Q�D�C���^�[�t�F�[�X
//      BOOL CheckSameTextFont( LPCTSTR IN_Name)
//
//	    ����: �^			  ������			    ���e
//            LPCTSTR        IN_Name                TextFont Name                        
//      
//	    ���A�l	
//            ���펞�F TRUE
//			  �ُ펞�F FALSE
//      
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.10     ��
//
//------------------------------------------------------------

BOOL SXFTableManagerC::CheckSameTextFont( LPCTSTR IN_Name)
{
    for(int i=0;i<m_TextFontTable.GetSize();i++){
        if(IN_Name == m_TextFontTable[i].m_Name)
            return FALSE;
    }

    return TRUE;
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFTableManagerC.cpp                    �쐬���F2000.04.10
//
//  �P�D�@�\�T�v
//      �o�^����Layer�v�f��Mapping����
//      
//  �Q�D�C���^�[�t�F�[�X
//      void  LayerMapping()
//
//	    ����: �^			  ������			    ���e
//      
//	    ���A�l	
//            �Ȃ�
//      
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.10     ��
//
//------------------------------------------------------------
void  SXFTableManagerC::LayerMapping()
{
	int InstanceID;

	for(int i=0;i<m_LayerTable.GetSize();i++){
		/* ڲԏ��� */
		if (m_LayerTable[i].m_MappingManager->SetStructLayer(&m_LayerTable[i],&InstanceID))
			/* �ݽ�ݽID��� */
			m_LayerTable[i].m_ID = InstanceID;
	}
}

//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFTableManagerC.cpp                    �쐬���F2000.04.10
//
//  �P�D�@�\�T�v
//      �Ǘ�Table����o�^����Table�v�f����o�͂���
//
//  �Q�D�C���^�[�t�F�[�X
//      int GetTableElement(int IN_Type,
//                          LPVOID& OUT_Struct,
//                          int& OUT_EndFlg)
//
//	    ����: �^			  ������			    ���e
//            int            IN_Type               Table�v�f��Type
//            LPVOID&        OUT_Struct            Table�v�f�̍\����
//                                                 �̃A�h���X
//            int&           OUT_EndFlg            �Ō�̗v�f��Flag
//                                                  1:�Ō�̗v�f
//                                                  0:����
//
//	    ���A�l	
//            ���펞�F Table�v�f��Code
//			  �ُ펞�F ��(�G���[�R�[�h)
//
//  �R�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.10     ��
//
//------------------------------------------------------------
int SXFTableManagerC::GetTableElement(int IN_Type, LPVOID OUT_Struct, int* OUT_EndFlg)
{
    *OUT_EndFlg = 1;
	SXFTableMapManagerC* mappingmanager;
	int i = 0;
	CUIntArray predefcolor;
	CUIntArray predeffont;
	CUIntArray width;
	int return_code = -1;
	INT_PTR table_size;

	/* ð��ٌ^���ُ� */
	if (IN_Type < 1 || 7 < IN_Type){
		SXFErrorMsgC::RecordError(SXFTABLETYPEERR,"",1,IN_Type);
		return SXFTABLETYPEERR;
	}
	/* ð��ٲ��ޯ����0 */
    if(m_CurrentNumber == 0 ){
        m_CurrentType = IN_Type;
    }
	else{
        if(m_CurrentType != IN_Type){
		    m_CurrentNumber = 0;
	        m_CurrentType = IN_Type;
		}
    }
    switch (m_CurrentType){
		/* ڲ� */
		case 1://layer
			/* ڲ�ð��ق̻��� */
			table_size = m_LayerTable.GetSize();
			/* ���ނ�0�̂Ƃ� */
			if (table_size == 0){
				/* �ǂݏo�����C��������܂��� */
//	MOD(S)	���b�Z�[�W�C��	K.Naono	04.03.05
//				SXFErrorMsgC::RecordError(SXFNOLAYER,"LAYER",0);
				SXFErrorMsgC::RecordError2(SXFNOLAYER,"LAYER",0);
				return SXFNOLAYER;
//	MOD(E)	���b�Z�[�W�C��	K.Naono	04.03.05
			}
			/* ڲ�ð��ٲ��ޯ����ð��ق̍Ō� */
			if(m_CurrentNumber == table_size - 1)
				*OUT_EndFlg = 1;	/* EndFlg��ON */
			else if(m_CurrentNumber > table_size - 1) {
				*OUT_EndFlg = 1;	/* EndFlg��ON */
				/* �ǂݏo�����C��������܂��� */
				SXFErrorMsgC::RecordError(SXFNOLAYER,"LAYER",0);
				return SXFNOLAYER;
			}
			else
				*OUT_EndFlg = 0;	/* EndFlg��OFF */
			/* ڲԍ\���� */
			*(Layer_Struct*)OUT_Struct = *(Layer_Struct*)(m_LayerTable[m_CurrentNumber].m_MappingManager->GetStructData(  ));
			/* ���A�l(ڲԺ���) */
			return_code = m_LayerTable[m_CurrentNumber].m_Code;
			/* ð��ٲ��ޯ�����{�P */
			m_CurrentNumber++;
			break;
		/* ����`�F */
		case 2://predefcolor
			for(i=0; i<MAXPRECOLOUR; i++){
				/* ��`ð��ٗv�fMapping�Ǘ���޼ު�ľ�� */
				mappingmanager = m_PreDefColorTable[i].m_MappingManager;
				if(mappingmanager != NULL)
					/* ����`�Fð��قɒǉ� */
					predefcolor.Add(i);
			}
			/* ����`�Fð��ٻ��� */
			table_size = predefcolor.GetSize();
			/* ð��ٻ��ނ�0 */
			if (table_size == 0){
				/* �ǂݏo������`�F������܂��� */
//	MOD(S)	���b�Z�[�W�C��	K.Naono	04.03.05
//				SXFErrorMsgC::RecordError(SXFNOPRECOLOUR,"PREDEFINED_COLOUR",0);
				SXFErrorMsgC::RecordError2(SXFNOPRECOLOUR,"PREDEFINED_COLOUR",0);
				return SXFNOPRECOLOUR;
//	MOD(E)	���b�Z�[�W�C��	K.Naono	04.03.05
			}
			/* ð��ٲ��ޯ�����Ō� */
			if(m_CurrentNumber == table_size-1)
				*OUT_EndFlg = 1;	/* EndFlg��ON */
			else if(m_CurrentNumber > table_size-1) {
				*OUT_EndFlg = 1;	/* EndFlg��ON */
				/* �ǂݏo������`�F������܂��� */
				SXFErrorMsgC::RecordError(SXFNOPRECOLOUR,"PREDEFINED_COLOUR",0);
				return SXFNOPRECOLOUR;
			}
			else
				*OUT_EndFlg = 0;	/* EndFlg��OFF */
			/* ����`�F�\���� */
			*(Predefined_Colour_Struct*)OUT_Struct = *(Predefined_Colour_Struct*)(m_PreDefColorTable[predefcolor[m_CurrentNumber]].m_MappingManager->GetStructData(  ));
			/* ���A�l(�F����) */
			return_code = m_PreDefColorTable[predefcolor[m_CurrentNumber]].m_Code;
			/* ð��ٲ��ޯ�����{�P */
			m_CurrentNumber++;
			break;
		/* հ�ޒ�`�F */
		case 3://userdefcolor
			/* հ�ޒ�`�Fð��ٻ��� */
			table_size = m_UserDefColorTable.GetSize();
			/* ð��ٻ��ނ�0 */
			if (table_size == 0){
				/* �ǂݏo��հ�ޒ�`�F������܂��� */
//	MOD(S)	���b�Z�[�W�C��	K.Naono	04.03.05
//				SXFErrorMsgC::RecordError(SXFNOUSERCOLOUR,"USERDEFINED_COLOUR",0);
				SXFErrorMsgC::RecordError2(SXFNOUSERCOLOUR,"USERDEFINED_COLOUR",0);
				return SXFNOUSERCOLOUR;
//	MOD(E)	���b�Z�[�W�C��	K.Naono	04.03.05
			}
			/* ð��ٲ��ޯ�����Ō� */
			if(m_CurrentNumber == table_size-1)
				*OUT_EndFlg = 1;	/* EndFlg��ON */
			else if(m_CurrentNumber > table_size-1) {
				*OUT_EndFlg = 1;	/* EndFlg��ON */
				/* �ǂݏo��հ�ޒ�`�F������܂��� */
				SXFErrorMsgC::RecordError(SXFNOUSERCOLOUR,"USERDEFINED_COLOUR",0);
				return SXFNOUSERCOLOUR;
			}
			else
				*OUT_EndFlg = 0;	/* EndFlg��OFF */
			/* հ�ޒ�`�F�\���� */
			*(Userdefined_Colour_Struct*)OUT_Struct = *(Userdefined_Colour_Struct*)(m_UserDefColorTable[m_CurrentNumber].m_MappingManager->GetStructData(  ));
			/* ���A�l(�F����) */
			return_code = m_UserDefColorTable[m_CurrentNumber].m_Code;
			/* ð��ٲ��ޯ�����{�P */
			m_CurrentNumber++;
			break;
		/* ����`���� */
		case 4://predeffont
			for(i=0; i<MAXPRELINETYPE; i++){
				/* ��`ð��ٗv�fMapping�Ǘ���޼ު�Đ��� */
				mappingmanager = m_PreDefFontTable[i].m_MappingManager;
				if(mappingmanager != NULL)
					/* ����`����ð��قɒǉ� */
					predeffont.Add(i);
			}
			/* ����`����ð��ٻ��� */
			table_size = predeffont.GetSize();
			/* ð��ٻ��ނ�0 */
			if (table_size == 0){
				/* �ǂݏo������`���킪����܂��� */
//	MOD(S)	���b�Z�[�W�C��	K.Naono	04.03.05
//				SXFErrorMsgC::RecordError(SXFNOPRELINETYPE,"PREDEFINED_LINETYPE",0);
				SXFErrorMsgC::RecordError2(SXFNOPRELINETYPE,"PREDEFINED_LINETYPE",0);
				return SXFNOPRELINETYPE;
//	MOD(E)	���b�Z�[�W�C��	K.Naono	04.03.05
			}
			/* ð��ٲ��ޯ����ð��ق̍Ō� */
			if(m_CurrentNumber == table_size-1)
				*OUT_EndFlg = 1;	/* EndFlg��ON */
			else if(m_CurrentNumber > table_size-1) {
				*OUT_EndFlg = 1;	/* EndFlg��ON */
				/* �ǂݏo������`���킪����܂��� */
				SXFErrorMsgC::RecordError(SXFNOPRELINETYPE,"PREDEFINED_LINETYPE",0);
				return SXFNOPRELINETYPE;
			}
			else
				*OUT_EndFlg = 0;	/* EndFlg��OFF */
			/* ����`����\���� */
			*(Predefined_Linetype_Struct*)OUT_Struct = *(Predefined_Linetype_Struct*)(m_PreDefFontTable[predeffont[m_CurrentNumber]].m_MappingManager->GetStructData(  ));
			/* ���A�l(������) */
			return_code = m_PreDefFontTable[predeffont[m_CurrentNumber]].m_Code;
			/* ð��ٲ��ޯ�����{�P */
			m_CurrentNumber++;
			break;
		/* հ�ޒ�`���� */
		case 5://userdeffont
			/* հ�ޒ�`����ð��ٻ��� */
			table_size = m_UserDefFontTable.GetSize();
			/* ð��ٻ��ނ�0 */
			if (table_size == 0){
				/* �ǂݏo��հ�ޒ�`���킪����܂��� */
//	MOD(S)	���b�Z�[�W�C��	K.Naono	04.03.05
//				SXFErrorMsgC::RecordError(SXFNOUSERLINETYPE,"USERDEFINED_LINETYPE",0);
				SXFErrorMsgC::RecordError2(SXFNOUSERLINETYPE,"USERDEFINED_LINETYPE",0);
				return SXFNOUSERLINETYPE;
//	MOD(E)	���b�Z�[�W�C��	K.Naono	04.03.05
			}
			/* ð��ٲ��ޯ����ð��ق̍Ō� */
			if(m_CurrentNumber == table_size-1)
				*OUT_EndFlg = 1;		/* EndFlg ��ON */
			else if(m_CurrentNumber > table_size-1) {
				*OUT_EndFlg = 1;		/* EndFlg ��ON */
				/* �ǂݏo��հ�ޒ�`���킪����܂��� */
				SXFErrorMsgC::RecordError(SXFNOUSERLINETYPE,"USERDEFINED_LINETYPE",0);
				return SXFNOUSERLINETYPE;
			}
			else
				*OUT_EndFlg = 0;		/* EndFlg ��OFF */
			/* հ�ޒ�`����\���� */
			*(Userdefined_Linetype_Struct*)OUT_Struct = *(Userdefined_Linetype_Struct*)(m_UserDefFontTable[m_CurrentNumber].m_MappingManager->GetStructData(  ));
			/* ���A�l(������) */
			return_code = m_UserDefFontTable[m_CurrentNumber].m_Code;
			/* ð��ٲ��ޯ�����{�P */
			m_CurrentNumber++;
			break;
		/* ���� */
		case 6://width
			for(i=0; i<MAXLINEWIDTH; i++){
				/* ��`ð��ٗv�fMapping�Ǘ���޼ު�ľ�� */
				mappingmanager = m_WidthTable[i].m_MappingManager;
				if(mappingmanager != NULL)
					/* ����ð��قɒǉ� */
					width.Add(i);
			}
			/* ����ð��ٻ��� */
			table_size = width.GetSize();
			/* ð��ٻ��ނ�0 */
			if (table_size == 0){
				/* �ǂݏo������������܂��� */
//	MOD(S)	���b�Z�[�W�C��	K.Naono	04.03.05
//				SXFErrorMsgC::RecordError(SXFNOLINEWIDTH,"LINE_WIDTH",0);
				SXFErrorMsgC::RecordError2(SXFNOLINEWIDTH,"LINE_WIDTH",0);
				return SXFNOLINEWIDTH;
//	MOD(E)	���b�Z�[�W�C��	K.Naono	04.03.05
			}
			/* ð��ٲ��ޯ����ð��ق̍Ō� */        
			if(m_CurrentNumber == table_size-1)
				*OUT_EndFlg = 1;	/* EndFlg��ON */
			else if(m_CurrentNumber > table_size-1) {
				*OUT_EndFlg = 1;	/* EndFlg��ON */
				/* �ǂݏo������������܂��� */
				SXFErrorMsgC::RecordError(SXFNOLINEWIDTH,"LINE_WIDTH",0);
				return SXFNOLINEWIDTH;
			}
			else
				*OUT_EndFlg = 0;	/* EndFlg��OFF */
			/* �����\���� */
			*(Line_Width_Struct*)OUT_Struct = *(Line_Width_Struct*)(m_WidthTable[width[m_CurrentNumber]].m_MappingManager->GetStructData(  ));
			/* ���A�l(��������) */
			return_code = m_WidthTable[width[m_CurrentNumber]].m_Code;
			/* ð��ٲ��ޯ�����{�P */
			m_CurrentNumber++;
			break;
		/* ����̫�� */
		case 7://textfont
			/* ����̫��ð��ٻ��� */
			table_size = m_TextFontTable.GetSize();
			/* ð��ٻ��ނ�0 */
			if (table_size == 0){
				/* �ǂݏo������̫�Ă�����܂��� */
//	MOD(S)	���b�Z�[�W�C��	K.Naono	04.03.05
//				SXFErrorMsgC::RecordError(SXFNOTEXTFONT,"TEXT_FONT",0);
				SXFErrorMsgC::RecordError2(SXFNOTEXTFONT,"TEXT_FONT",0);
				return SXFNOTEXTFONT;
//	MOD(E)	���b�Z�[�W�C��	K.Naono	04.03.05
			}
			/* ð��ٲ��ޯ����ð��ق̍Ō� */
			if(m_CurrentNumber == table_size-1)
				*OUT_EndFlg = 1;		/* EndFlg ��ON */
			else if(m_CurrentNumber > table_size-1) {
				*OUT_EndFlg = 1;		/* EndFlg ��ON */
				/* �ǂݏo������̫�Ă�����܂��� */
				SXFErrorMsgC::RecordError(SXFNOTEXTFONT,"TEXT_FONT",0);
				return SXFNOTEXTFONT;
			}
			else
				*OUT_EndFlg = 0;		/* EndFlg ��OFF */
			/* ����̫�č\���� */
			*(Text_Font_Struct*)OUT_Struct = *(Text_Font_Struct*)(m_TextFontTable[m_CurrentNumber].m_MappingManager->GetStructData(  ));
			/* ���A�l(����̫�ĺ���) */
			return_code = m_TextFontTable[m_CurrentNumber].m_Code;
			/* ð��ٲ��ޯ�����{�P */
			m_CurrentNumber++;
			break;
    }        
	return return_code;
}
