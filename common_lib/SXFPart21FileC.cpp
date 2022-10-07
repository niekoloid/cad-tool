//---------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFPart21FileC.cpp	                  �쐬���F2000.03.25
//
//	�P�D�N���X�T�v
//      �t�@�C���̓��͂Əo�͂��Ǘ�����
//
//	�Q�D����
//		����ԍ�	���t��		 �S����	    �T�v
//		�쐬		2000.03.25  ��
//		�X�V		2002.12.03	K.Naono		Ver3.0�Ή�
//
//---------------------------------------------------------

#include "stdafx.h"
#include <afx.h>
#include "ComSplitStringC.h"
#include "SXFDataStructC.h"
#include "SXFPart21FileC.h"
#include "SXFutyConvKanjiC.h"
#include "max.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------
//	All Rights Reserved,(c)JACIC 2001
//	SXFPart21FileC.cpp		              �쐬���F2000.03.25
//
//	�P�D�@�\�T�v
//		�R���X�g���N�^
//
//	�Q�D�C���^�[�t�F�C�X
//		void	SXFPart21FileC::SXFPart21FileC()
//		
//	����	�F	�^		������				���e
//		�Ȃ�
//      
//	���A�l�F�Ȃ�
//
//	�R�D����
//		����ԍ�	���t��		 �S����	    �T�v
//		�쐬		2000.03.25  ��
//---------------------------------------------------------
SXFPart21FileC::SXFPart21FileC()
{
	featurecount = 0;
}

//---------------------------------------------------------
//	All Rights Reserved,(c)JACIC 2001
//	SXFPart21FileC.cpp		              �쐬���F2000.03.25
//
//	�P�D�@�\�T�v
//		�R���X�g���N�^
//
//	�Q�D�C���^�[�t�F�C�X
//		void	SXFPart21FileC::SXFPart21FileC( 
//								LPCTSTR IN_lpszFileName,
//                              UINT IN_nOpenFlags)
//
//	����	�F	�^			������				���e
//				LPCTSTR		IN_lpszFileName		�t�@�C����
//				UINT		IN_nOpenFlags		�t�@�C���I�[�v�����[�h
//      
//	���A�l�F�Ȃ�
//
//	�R�D����
//		����ԍ�	���t��			�S����	    �T�v
//		�쐬		2000.03.25		��
//---------------------------------------------------------
SXFPart21FileC::SXFPart21FileC( LPCTSTR IN_lpszFileName,
                                UINT IN_nOpenFlags)
               :CStdioFile( IN_lpszFileName,IN_nOpenFlags )
{
	featurecount = 0;
}

//---------------------------------------------------------
//	All Rights Reserved,(c)JACIC 2001
//	SXFPart21FileC.cpp		              �쐬���F2000.03.25
//
//	�P�D�@�\�T�v
//      �f�X�g���N�^
//
//	�Q�D�C���^�[�t�F�C�X
//		void	SXFPart21FileC::~SXFPart21FileC()
//		
//	����	�F	�^		������				���e
//		�Ȃ�
//      
//	���A�l�F�Ȃ�
//
//	�R�D����
//		����ԍ�	���t��		 �S����	    �T�v
//		�쐬		2000.03.25  ��
//---------------------------------------------------------
SXFPart21FileC::~SXFPart21FileC()
{
}

//---------------------------------------------------------
//	All Rights Reserved,(c)JACIC 2001
//	SXFPart21FileC.cpp		              �쐬���F2000.03.25
//
//	�P�D�@�\�T�v
//      Head Section������ǂݍ���
//
//	�Q�D�C���^�[�t�F�C�X
//      int ReadHeadSection(HEADSECTION *OUT_Head)
//
//	    ����: �^			  ������			    ���e
//            HEADSECTION*    OUT_Head              HeadSection��
//                                                 �\���̂̃A�h���X
//	    ���A�l	
//            ���펞�F  1 : OK
//						0 : SCADEC�ȊO�̃t�@�C��
//			  �ُ펞�F -1 : file end
//                    -2  : found syntax error 
//                    -3  : can not to find a headsection
//
//	�R�D����
//		����ԍ�	���t��		 �S����	    �T�v
//		�쐬		2000.03.25  ��
//---------------------------------------------------------
int SXFPart21FileC::ReadHeadSection(HEADSECTION *OUT_Head)
{
	INSTANCEDATA record;
    BOOL headflg = FALSE;
    CStringArray* array;
	char tmp_filename[257];
	char tmp_author[257];
	char tmp_org[257];
	char tmp_orgsystem[257];
	int result;

    while( 1 ) {
        result = ReadHeaderInstance(&record);
        if ( result<0 ){//end file or syntax err
            if (result == -1 && headflg == FALSE)
                return -3;// can not find headsection
            return result;
        }
        if( record.EntityName == "HEADER"){
            headflg=TRUE;
            continue;
        }
        if ( headflg == TRUE ){
            if( record.EntityName == "ENDSEC"){
                headflg = FALSE;
                break;
            }
			else if( record.EntityName=="FILE_DESCRIPTION"){
				record.EntityData.Remove('(');			//'(' 0x28
				record.EntityData.Remove(')');			//')' 0x29
				record.EntityData.Remove(0x27);			//'  0x27
				record.EntityData.Replace(" ", ",");	//'SPACE' -> ','
                ComSplitStringC split(record.EntityData);
				array = split.Split(',');				//',' 0x2c
                if (array->GetSize() != 4)				// syntax err
                    return -2;
				if ((*array)[0] != "SCADEC")
					return 0;			//SCADEC�ȊO�̃t�@�C��
				OUT_Head->scadec_flg = 1;		/* SCADEC flg ��ON */
				/* ���x�� */
				if((* array)[1]=="level1")
					OUT_Head->Level=1;
				else if((* array)[1]=="level2")
					OUT_Head->Level=2;
                else
					return 0;			//SCADEC�ȊO�̃t�@�C��
				/* ���[�h */
				if((* array)[2]=="ambi_mode")
					OUT_Head->Mode=0;
				else if((* array)[2]=="feature_mode")
					OUT_Head->Mode=1;
				else if((* array)[2]=="AP202_mode")
					OUT_Head->Mode=2;
				else
					return 0;			//SCADEC�ȊO�̃t�@�C��
            }
			else if( record.EntityName=="FILE_NAME"){
				record.EntityData.Remove('(');				//'(' 0x28
				record.EntityData.Remove(')');				//')' 0x29
				record.EntityData.Remove(0x27);				//'  0x27
                ComSplitStringC split(record.EntityData);
				array = split.Split(',');					//',' 0x2c
                if (array->GetSize() != 7)					// syntax err
                    return -2;
				/* ̧�ٖ� */
				SXFutyConvKanjiC::ConvKanji("ToJIS",
											(char*)(LPCTSTR)(* array)[0],
											//	JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
											//tmp_filename);
											tmp_filename,_countof(tmp_filename));
				OUT_Head->FileName= tmp_filename;
				/* ̧�ٍ쐬�� */
				SXFutyConvKanjiC::ConvKanji("ToJIS",
											(char*)(LPCTSTR)(* array)[2],
											//	JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
											//tmp_author);
											tmp_author,_countof(tmp_author));
				OUT_Head->Author= tmp_author;
				/* �쐬�ҏ��� */
				SXFutyConvKanjiC::ConvKanji("ToJIS",
											(char*)(LPCTSTR)(* array)[3],
											//	JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
											//tmp_org);
											tmp_org,_countof(tmp_org));
				OUT_Head->Organization= tmp_org;
				/* ����ײ�����ް�ޮ� */
                OUT_Head->Version=(* array)[4];
				/* ��ݽڰ��� */
				SXFutyConvKanjiC::ConvKanji("ToJIS",
											(char*)(LPCTSTR)(* array)[5],
											//	JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
											//tmp_orgsystem);
											tmp_orgsystem,_countof(tmp_orgsystem));
				OUT_Head->OriginatingSystem= tmp_orgsystem;
            }
			else
                continue;
        }//end of headflg
    }//end of while(1)
    return 1;
}

//---------------------------------------------------------
//	All Rights Reserved,(c)JACIC 2001
//	SXFPart21FileC.cpp		              �쐬���F2000.03.25
//
//	�P�D�@�\�T�v
//      �w�b�_��ǂݍ���
//
//	�Q�D�C���^�[�t�F�C�X
//      int ReadHeaderInstance(INSTANCEDATA *OUT_Instance)
//
//	    ����: �^			  ������		   ���e
//            INSTANCEDATA*   OUT_Instance     Instance Data��
//                                             �\���̂̃A�h���X
//	    ���A�l	
//            ���펞�F   1 :  OK
//			  �ُ펞�F  -1 :  file end
//                     -2 :  found syntax error
//
//	�R�D����
//		����ԍ�	���t��		 �S����	    �T�v
//		�쐬		2001.03.07   �{��
//
//---------------------------------------------------------
int SXFPart21FileC::ReadHeaderInstance(INSTANCEDATA *OUT_Instance)
{
    CString recordline;
    CString record;
    BOOL instanceendflg = FALSE;
    BOOL fileendflg=TRUE;
    BOOL firstline = TRUE;	
	// read a instance with multilines 
    while(ReadString(recordline))
    { 
        recordline.TrimLeft();
        recordline.TrimRight();
        if(recordline.GetLength()==0)
            continue;
        if(firstline==TRUE){
            if(recordline.GetLength()>15){
				if (recordline.Left(9)!="FILE_NAME" &&
                    recordline.Left(11)!="FILE_SCHEMA" &&
                    recordline.Left(16)!="FILE_DESCRIPTION" &&
                    recordline.Right(1)!=";")
                    continue;
            }
			else if(recordline.GetLength()>10){
				if (recordline.Left(9)!="FILE_NAME" &&
                    recordline.Left(11)!="FILE_SCHEMA" &&
                    recordline.Right(1)!=";")
                    continue;
            }
			else if(recordline.GetLength()>8){
				if (recordline.Left(9)!="FILE_NAME" &&
                    recordline.Right(1)!=";")
                    continue;
            }
			else if(recordline.GetLength() > 0){
				if (recordline.Right(1)!=";")
                    continue;
            }
        }
        firstline = FALSE;
        fileendflg=FALSE;
        record += recordline;
        if (record.Right(1) ==";"){
            instanceendflg = TRUE;
            break;
        }
    }
	/* ̧�ق̍Ō� */
    if( fileendflg )
        return -1;
	/* �ݽ�ݽ�ł͂Ȃ� */
    if(! instanceendflg )
        return -2;		//found syntax error

	record.TrimRight(';');
    if(record[0] != '#'){// if the first char is not '#' then (headsection, sectionmark)
        int findfirstparentheses = record.Find('(');
		if (findfirstparentheses < 0){  // if have not a '(' in this instance
			// then must be a section mark line
			if (record == "HEADER" ||
				record == "ENDSEC" ||
				record == "DATA" ||
				record == "END-ISO-10303-21" ||
				record == "ISO-10303-21")
			{//section mark
				OUT_Instance->EntityName = record;
				OUT_Instance->InstanceMode = SXF_IM_SECTIONMARK; //2 Sectionmark
			}
			else{
				return -2;//found syntax error
			}
		}
		else if(findfirstparentheses==0) // if the first char is '(' 
			//then syntax error
			return -2; //found syntax error
		else{  // if have a '(' then must be a headsection instance
			OUT_Instance->EntityName=record.Left(findfirstparentheses);
			OUT_Instance->EntityData=record.Right(record.GetLength()
				-findfirstparentheses);
			if (OUT_Instance->EntityName == "FILE_DESCRIPTION"
				|| OUT_Instance->EntityName == "FILE_NAME"
				|| OUT_Instance->EntityName == "FILE_SCHEMA")
				OUT_Instance->InstanceMode = SXF_IM_HEADSECTION; //3 HeadSection
			else
				return -2; //found syntax error
		}//end of findfirstparenthese in a instance without a '#'
	}//end of to inquire if the first char is a '#'
    return 1;
}

//---------------------------------------------------------
//	All Rights Reserved,(c)JACIC 2001
//	SXFPart21FileC.cpp		              �쐬���F2000.03.25
//
//	�P�D�@�\�T�v
//      ���Instance��ǂݍ���
//
//	�Q�D�C���^�[�t�F�C�X
//      int ReadInstance(INSTANCEDATA *OUT_Instance)
//
//	    ����: �^			  ������			    ���e
//            INSTANCEDATA*   OUT_Instance          Instance Data��
//                                                 �\���̂̃A�h���X
//	    ���A�l	
//            ���펞�F   1 :  OK
//			  �ُ펞�F  -1 :  file end
//                     -2 :  found syntax error
//                     -4 :  can not to find a feature instance
//                           in this file 
//
//	�R�D����
//		����ԍ�	���t��		 �S����	    �T�v
//		�쐬		2000.03.25  ��
//		�X�V		2002.12.03	K.Naono		Ver3.0�Ή�
//---------------------------------------------------------
int SXFPart21FileC::ReadInstance(INSTANCEDATA *OUT_Instance)
{
    CString recordline;
    CString record;
    BOOL fileendflg;
	BOOL start_flg = FALSE;
	// read a instance with multilines 
    while(1)
    {
		fileendflg = ReadString(recordline);
		if (!fileendflg){
			/* ̨����ݽ�ݽ������Ȃ� */
			if(featurecount == 0)
				return -4;// can not find a feature instance
			return -1;//file end
		}
		recordline.TrimLeft();
		recordline.TrimRight();
//	MOD(S)	Ver3.0�Ή�	K.Naono	02.12.03
//		if (recordline == "/*SXF"){
		if (recordline == "/*SXF" || recordline == "/*SXF3" ||  recordline == "/*SXF3.1"){
//	MOD(E)	Ver3.0�Ή�	K.Naono	02.12.03
			start_flg = TRUE;
			continue;
		}
		if (start_flg){
//	MOD(S)	Ver3.0�Ή�	K.Naono	02.12.03
//			if (recordline == "SXF*/")
			if (recordline == "SXF*/" || recordline == "SXF3*/" || recordline == "SXF3.1*/")
//	MOD(E)	Ver3.0�Ή�	K.Naono	02.12.03
				break;
			record += recordline;
		}
    }
	if(record[0] != '#'){		// if have not a '#' then error
		return -2;				//found syntax error
	}
    //analyse this instance and set (INSTANCEDATA *OUT_Instance)
	/* ̨����ݽ�ݽ���{�P */
	featurecount ++;//feature count++
	int findequalsign = record.Find('=');
	if (findequalsign<2) 
		return -2;//found syntax error in file
	//get feature ID
	CString idstring = record.Mid(1,findequalsign-1);
	int featureid = atoi( idstring );
	if (featureid<=0) 
		return -2;//found syntax error in file            
	OUT_Instance->InstanceID = featureid;		
	//get feature data
	CString datastring = record.Right(record.GetLength()
		-findequalsign - 1 );
	datastring.TrimLeft();
	datastring.TrimRight();
	//find the first '(' 
	int findfirstparentheses = datastring.Find('(');
	if (findfirstparentheses <=0){//no feature name
		return -2;//found syntax error in file
	}
	OUT_Instance->EntityName = datastring.Left( findfirstparentheses);
	OUT_Instance->EntityName.TrimRight();
	OUT_Instance->EntityName.TrimLeft();
	OUT_Instance->EntityData = datastring.Right(datastring.GetLength()
								- findfirstparentheses);
	// analyse instance mode (ft_table,ft_assembly,common entity)
	if( OUT_Instance->EntityName == "layer_feature" ||
		OUT_Instance->EntityName == "pre_defined_font_feature" ||
		OUT_Instance->EntityName == "user_defined_font_feature" ||
		OUT_Instance->EntityName == "width_feature" ||
		OUT_Instance->EntityName == "text_font_feature" ||
		OUT_Instance->EntityName == "pre_defined_colour_feature" ||
		OUT_Instance->EntityName == "user_defined_colour_feature")
	{
		//22 Feature_Table
		OUT_Instance->InstanceMode = SXF_IM_FT_TABLE;                
	}
	//assembly feature name
	else if( OUT_Instance->EntityName == "drawing_sheet_feature" ||
		OUT_Instance->EntityName == "sfig_org_feature" ||
		OUT_Instance->EntityName == "composite_curve_org_feature" ){
		//23 Feature_Assembly
		OUT_Instance->InstanceMode = SXF_IM_FT_ASSEMBLY;
	}
	else
		//21 Feature_common Entity
		OUT_Instance->InstanceMode = SXF_IM_FT_ENTITY;
    return 1;
}

//---------------------------------------------------------
//	All Rights Reserved,(c)JACIC 2001
//	SXFPart21FileC.cpp		              �쐬���F2000.03.25
//
//	�P�D�@�\�T�v
//
//      Head Section�����o�͂���
//
//	�Q�D�C���^�[�t�F�C�X
//      void WriteHeadSection(HEADSECTION *IN_Head)
//
//	    ����: �^			  ������			    ���e
//            HEADSECTION*    IN_Head              Head Section��
//                                                 �\���̂̃A�h���X
//	    ���A�l:	
//            �Ȃ�
//
//	�R�D����
//		����ԍ�	���t��		 �S����	    �T�v
//		�쐬		2000.03.25  ��
//---------------------------------------------------------
void SXFPart21FileC::WriteHeadSection(HEADSECTION *IN_Head)
{
	char out_filename[MAXUNICODENAME];
	char out_author[MAXUNICODENAME];
	char out_org[MAXUNICODENAME];
	char out_orgsystem[MAXUNICODENAME];
	int backslash_find;
    CString headsection;
    CString tempstring;
    CString mode;
    CString endline("\n");

    headsection="ISO-10303-21;";
    headsection+=endline;
    headsection+="HEADER;";
    headsection+=endline;

	/* Ӱ�� */
    switch (IN_Head->Mode){
		case 0:
			mode = "ambi_mode";
			break;
		case 1:
			mode = "feature_mode";
			break;
		case 2:
			mode = "AP202_mode";
			break;
		default:
			break;   
	}
    /* level, mode�̏o��̫�ϯč쐬 */
    tempstring.Format("FILE_DESCRIPTION(('SCADEC level%d %s'),\n",
                       IN_Head->Level,mode);
    headsection += tempstring;
    headsection += "        '2;1');";
    headsection+=endline;
    /* file name(need not path name) */
	CString filename = IN_Head->FileName;
	backslash_find = filename.ReverseFind('\\');
	if (backslash_find != -1)
		filename = filename.Mid(backslash_find+1);
	/* ̧�ٖ���UNICODE�֕ϊ� */
	//	JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
	//SXFutyConvKanjiC::ConvKanji("FromJIS",(char*)(LPCTSTR)filename,out_filename);
	SXFutyConvKanjiC::ConvKanji("FromJIS",(char*)(LPCTSTR)filename,out_filename,_countof(out_filename));
	/* ̧�ٖ��̏o��̫�ϯč쐬 */
    tempstring.Format("FILE_NAME('%s',\n",out_filename);
    headsection += tempstring;
    //current date and time
    CTime currenttime=CTime::GetCurrentTime();
    tempstring.Format("        '%d-%d-%dT%d:%d:%d',\n",
                      currenttime.GetYear(),
                      currenttime.GetMonth(),
                      currenttime.GetDay(),
                      currenttime.GetHour(),
                      currenttime.GetMinute(),
                      currenttime.GetSecond() );
    headsection += tempstring;
    /* author��UNICODE�ɕϊ� */
	SXFutyConvKanjiC::ConvKanji("FromJIS",
								(char*)(LPCTSTR)IN_Head->Author,
								//	JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
								//out_author);
								out_author,_countof(out_author));
	/* �o��̫�ϯč쐬 */
    tempstring.Format("        ('%s'),\n",out_author);
    headsection += tempstring;
    /* organization ��UNICODE�ɕϊ� */
	SXFutyConvKanjiC::ConvKanji("FromJIS",
								(char*)(LPCTSTR)IN_Head->Organization,
								//	JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
								//out_org);
								out_org,_countof(out_org));
	/* �o��̫�ϯč쐬 */
    tempstring.Format("        ('%s'),\n",out_org);
    headsection += tempstring;
    /* version �o��̫�ϯč쐬 */
    tempstring.Format("        '%s',\n",IN_Head->Version);
    headsection += tempstring;
    /* Originating system �o��̫�ϯč쐬 */
	SXFutyConvKanjiC::ConvKanji("FromJIS",
								(char*)(LPCTSTR)IN_Head->OriginatingSystem,
								//	JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
								//out_orgsystem);
								out_orgsystem,_countof(out_orgsystem));
    tempstring.Format("        '%s',\n",out_orgsystem);
	/* ͯ�ް�o��̫�ϯč쐬 */
    headsection += tempstring;
	headsection += "        '');";
	headsection += endline;
    headsection += "FILE_SCHEMA(('ASSOCIATIVE_DRAUGHTING'));";
    headsection+=endline;
    headsection += "ENDSEC;";
    headsection+=endline;
    headsection += "DATA;";
    headsection+=endline;
	/* ͯ�ް�̏o�� */
    WriteString(headsection);
}

//---------------------------------------------------------
//	All Rights Reserved,(c)JACIC 2001
//	SXFPart21FileC.cpp		              �쐬���F2000.03.25
//
//	�P�D�@�\�T�v
//      ���Instance���o�͂���
//
//	�Q�D�C���^�[�t�F�C�X
//      void WriteInstance(INSTANCEDATA *IN_Instance)
//
//	    ����: �^			  ������			    ���e
//            INSTANCEDATA*   IN_Instance          Instance Data��
//                                                 �\���̂̃A�h���X
//	    ���A�l	:
//            �Ȃ�
//
//	�R�D����
//		����ԍ�	���t��		 �S����	    �T�v
//		�쐬		2000.03.25  ��
//		�X�V		2002.12.03	K.Naono		Ver3.0�Ή�
//		�X�V		2007.1.29	����		Ver4.0�Ή�
//---------------------------------------------------------
void SXFPart21FileC::WriteInstance(INSTANCEDATA *IN_Instance)
{    
    CString instance;
    switch (IN_Instance->InstanceMode)
    {
		case SXF_IM_FT_ENTITY:		//Feature
		case SXF_IM_FT_TABLE:		//Feature table
		case SXF_IM_FT_ASSEMBLY:	//Feature assembly
			{
				CString	PreFix = "SXF";
				if( IN_Instance->EntityName == "drawing_attribute_feature" ) {
					PreFix = "SXF3";
				}
				else if( IN_Instance->EntityName == "curve_dim_feature" ||
						 IN_Instance->EntityName == "clothoid_feature") {
					PreFix = "SXF3.1";
				}
				/* �o��̫�ϯč쐬 */
				instance.Format("\n/*%s\n#%d = %s%s\n%s*/\n",
								PreFix,
								IN_Instance->InstanceID,
								IN_Instance->EntityName,
								IN_Instance->EntityData,
								PreFix);
			}
			break;
		default: 
			return;
    }
	/* �ݽ�ݽ�o�� */    
    WriteString(instance);
}
