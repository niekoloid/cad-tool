//---------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFPart21FileC.cpp					�쐬���F2001.09.17
//
//	�P�D�N���X�T�v
//		�t�@�C���̓��͂��Ǘ�����
//
//	�Q�D����
//		����ԍ�	���t��		 �S����			�T�v
//		�쐬		2001.09.17	K.Naono(FQS)	�w�b�_��͏����̉��P�Ή�
//
//---------------------------------------------------------
#include "stdafx.h"
#include "SXFPart21FileExC.h"
#include "SXFHeaderLex.h"
#include "ComSplitStringC.h"
#include "SXFutyConvKanjiC.h"

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

//---------------------------------------------------------
//	All Rights Reserved,(c)JACIC 2001
//	SXFPart21FileC.cpp					�쐬���F2001.09.17
//
//	�P�D�@�\�T�v
//		�R���X�g���N�^
//
//	�Q�D�C���^�[�t�F�C�X
//		SXFPart21FileExC::SXFPart21FileExC(
//						LPCTSTR	IN_lpszFileName,
//						UINT	IN_nOpenFlags)
//
//		����: �^				������			    ���e
//				LPCTSTR		IN_lpszFileName		�t�@�C����
//				UINT		IN_nOpenFlags		�t�@�C���I�[�v�����[�h
//
//		���A�l	�Ȃ�
//
//	�R�D����
//		����ԍ�	���t��		 �S����			�T�v
//		�쐬		2001.09.17	K.Naono(FQS)
//---------------------------------------------------------
SXFPart21FileExC::SXFPart21FileExC(
						LPCTSTR	IN_lpszFileName,
						UINT	IN_nOpenFlags)
				:SXFPart21FileC(IN_lpszFileName, IN_nOpenFlags)
{
}

//---------------------------------------------------------
//	All Rights Reserved,(c)JACIC 2001
//	SXFPart21FileC.cpp					�쐬���F2001.09.17
//
//	�P�D�@�\�T�v
//		�f�X�g���N�^
//
//	�Q�D�C���^�[�t�F�C�X
//		SXFPart21FileExC::~SXFPart21FileExC()
//
//		����:	�Ȃ�
//
//		���A�l	�Ȃ�
//
//	�R�D����
//		����ԍ�	���t��		 �S����			�T�v
//		�쐬		2001.09.17	K.Naono(FQS)
//---------------------------------------------------------
SXFPart21FileExC::~SXFPart21FileExC()
{
}

//---------------------------------------------------------
//	All Rights Reserved,(c)JACIC 2001
//	SXFPart21FileC.cpp					�쐬���F2001.09.17
//
//	�P�D�@�\�T�v
//		Head Section������ǂݍ���
//
//	�Q�D�C���^�[�t�F�C�X
//		int SXFPart21FileExC::ReadHeadSection(
//							HEADSECTION*	IO_Head)
//
//		����: �^				������			    ���e
//			HEADSECTION*	IO_Head				HeadSection��
//												�\���̂̃A�h���X
//		���A�l
//			���펞�F 1 : OK
//			�ُ펞�F
//					-1 : file end
//					-2 : found syntax error 
//					-3 : can not to find a headsection
//
//	�R�D����
//		����ԍ�	���t��		 �S����			�T�v
//		�쐬		2001.09.17	K.Naono(FQS)
//---------------------------------------------------------
int SXFPart21FileExC::ReadHeadSection(HEADSECTION* IO_Head)
{
	ASSERT(IO_Head) ;
	if( IO_Head == NULL ) {
		return -1 ;
	}

	//	HEADER �` ENDSEC�܂ł�ǂݍ���
	CString	buffer ;
	CString	record ;

	while( ReadString(record) ) {
		record.TrimLeft() ;
		record.TrimRight() ;
		buffer += record ;
		if( record.Find(ID_ENDSEC) != -1 )
			break ;
	}
	if( buffer.GetLength() == 0 ) {
		return -3 ;
	}

	//	����̉�͂��n�߂�
    BOOL			bExistHeader = FALSE ;
	CStringArray	array ;
	int token = 0, ret = 0 ;
	CSXFHeaderLex*	pLex = new CSXFHeaderLex(buffer) ;
	while( (token = pLex->Lex() ) != TT_EOF) {

		switch(token) {
		case TT_FILE_DESCRIPTION :
			//	�����l�̎擾
			getAttribute(pLex, array) ;

			//	�����l�̉��
			if( (ret = analyzeDescription(array, IO_Head)) == 1 ) {
				break ;
			}
			delete pLex ;
			if( ret == 0 ) {
				return ret ;
			} else {
				return !bExistHeader ? -3 : ret ;
			}
			break ;

		case TT_FILE_NAME :
			//	�����l�̎擾
			getAttribute(pLex, array) ;

			//	�����l�̉��
			if( (ret = analyzeName(array, IO_Head)) < 0 ) {
				delete pLex ;
				return !bExistHeader ? -3 : ret ;
			}
			break ;

		case TT_FILE_SCHEMA :
			break ;

		case TT_HEADER :
			bExistHeader = TRUE ;
			break ;

		case TT_ENDSEC :
			bExistHeader = FALSE ;
			break ;
		}
	}

	delete pLex ;

	return 1 ;
}

//---------------------------------------------------------
//	All Rights Reserved,(c)JACIC 2001
//	SXFPart21FileC.cpp					�쐬���F2001.09.17
//
//	�P�D�@�\�T�v
//		Part21 File��FILE_DESCRIPTION��������͂���
//
//	�Q�D�C���^�[�t�F�C�X
//		int SXFPart21FileExC::analyzeDescription(
//							CStringArray&	array,
//							HEADSECTION*	IO_Head)
//
//		����: �^				������			    ���e
//			CStringArray&		array			�����l
//			HEADSECTION*		IO_Head			HeadSection��
//												�\���̂̃A�h���X
//		���A�l	
//			���펞�F 1 : OK
//			�ُ펞�F
//					-1 : file end
//					-2 : found syntax error 
//					-3 : can not to find a headsection
//
//	�R�D����
//		����ԍ�	���t��		 �S����			�T�v
//		�쐬		2001.09.17	K.Naono(FQS)
//---------------------------------------------------------
int SXFPart21FileExC::analyzeDescription(
							CStringArray&	array,
							HEADSECTION*	IO_Head)
{
	if( array.GetSize() != 2 ) {
		return -2 ;
	}

	CStringArray*	pElem ;
	ComSplitStringC split(array[0]) ;
	pElem = split.Split(' ') ;
	if( pElem->GetSize() < 3 ) {
		return -2 ;
	}
	//	SCADEC�ȊO�̃t�@�C��
	if( (*pElem)[0] != ID_SCADEC ) {
		return 0 ;
	}

	//	SCADEC flg ��ON
	IO_Head->scadec_flg = 1 ;
	for(int i = 0; i < pElem->GetSize(); i++) {
		//	���x��
		if( !(*pElem)[i].CompareNoCase(ID_LEVEL1) ) {
			IO_Head->Level = 1 ;

		} else if( !(*pElem)[i].CompareNoCase(ID_LEVEL2) ) {
			IO_Head->Level = 2 ;

		//	���[�h
		} else if( !(*pElem)[i].CompareNoCase(ID_AMBI_MODE) ) {
			IO_Head->Mode = 0 ;

		} else if( !(*pElem)[i].CompareNoCase(ID_FEATURE_MODE) ) {
			IO_Head->Mode = 1 ;

		} else if( !(*pElem)[i].CompareNoCase(ID_AP202_MODE) ) {
			IO_Head->Mode = 2 ;
		}
	}

	return 1 ;
}

//---------------------------------------------------------
//	All Rights Reserved,(c)JACIC 2001
//	SXFPart21FileC.cpp					�쐬���F2001.09.17
//
//	�P�D�@�\�T�v
//		Part21 File��FILE_NAME��������͂���
//
//	�Q�D�C���^�[�t�F�C�X
//		int SXFPart21FileExC::analyzeName(
//							CStringArray&	array,
//							HEADSECTION*	IO_Head)
//
//		����: �^				������			    ���e
//			CStringArray&		array			�����l
//			HEADSECTION*		IO_Head			HeadSection��
//												�\���̂̃A�h���X
//		���A�l	
//			���펞�F 1 : OK
//			�ُ펞�F
//					-1 : file end
//					-2 : found syntax error 
//					-3 : can not to find a headsection
//
//	�R�D����
//		����ԍ�	���t��		 �S����			�T�v
//		�쐬		2001.09.17	K.Naono(FQS)
//---------------------------------------------------------
int SXFPart21FileExC::analyzeName(
							CStringArray&	array,
							HEADSECTION*	IO_Head)
{
	if( array.GetSize() != 7 ) {
		return -2 ;
	}

	TCHAR	buffer[257] ;
	//	name�����l�̎擾
	SXFutyConvKanjiC::ConvKanji("ToJIS",
//					(char*)(LPCTSTR)array[0], buffer) ;	JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
					(char*)(LPCTSTR)array[0], buffer, _countof(buffer)) ;
	IO_Head->FileName = buffer ;

	//	author�����l�̎擾
	SXFutyConvKanjiC::ConvKanji("ToJIS",
//					(char*)(LPCTSTR)array[2], buffer) ;	JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
					(char*)(LPCTSTR)array[2], buffer, _countof(buffer)) ;
	IO_Head->Author = buffer ;

	//	organization�����l�̎擾
	SXFutyConvKanjiC::ConvKanji("ToJIS",
//					(char*)(LPCTSTR)array[3], buffer) ;	JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
					(char*)(LPCTSTR)array[3], buffer, _countof(buffer)) ;
	IO_Head->Organization = buffer ;

	//	preprocessor_version�����l�̎擾
	SXFutyConvKanjiC::ConvKanji("ToJIS",
//					(char*)(LPCTSTR)array[4], buffer) ;	JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
					(char*)(LPCTSTR)array[4], buffer, _countof(buffer)) ;
	IO_Head->Version = buffer ;

	//	originating_system�����l�̎擾
	SXFutyConvKanjiC::ConvKanji("ToJIS",
//					(char*)(LPCTSTR)array[5], buffer) ;	JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
					(char*)(LPCTSTR)array[5], buffer, _countof(buffer)) ;
	IO_Head->OriginatingSystem = buffer ;

	return 1 ;
}

//---------------------------------------------------------
//	All Rights Reserved,(c)JACIC 2001
//	SXFPart21FileC.cpp					�쐬���F2001.09.17
//
//	�P�D�@�\�T�v
//      Part21 File�̃G���e�B�e�B�̑����l���擾����
//
//	�Q�D�C���^�[�t�F�C�X
//		void SXFPart21FileExC::getAttribute(
//							CSXFHeaderLex*	pLex,
//							CStringArray&	array)
//
//		����: �^				������			    ���e
//			CSXFHeaderLex*		pLex			Lex�I�u�W�F�N�g
//			CStringArray&		array			�����l�i�[�p�z��
//
//		���A�l
//			�Ȃ�
//
//	�R�D����
//		����ԍ�	���t��		 �S����			�T�v
//		�쐬		2001.09.17	K.Naono(FQS)
//---------------------------------------------------------
void SXFPart21FileExC::getAttribute(
					CSXFHeaderLex*	pLex,
					CStringArray&	array)
{
	if( array.GetSize() > 0 ) {
		array.RemoveAll() ;
	}

//	CString	key ;
	int token ;
	while( (token = pLex->Lex()) != ';' ) {
//	ADD(S)	�o�O�C��	K.Naono	03.05.29
		if( token == TT_EOF ) break ;
//	ADD(E)	�o�O�C��	K.Naono	03.05.29

		// �ǂݔ�΂�
		if( token == ' ' || token == '\t' )	continue ;

		if( token == TT_LINE_COMMENT ) {
			while((token = pLex->Lex()) != TT_EOL) ;
			continue ;
		}
		if( token == TT_BLOCK_COMMENT_START ) {
//			while((token = pLex->Lex()) != TT_BLOCK_COMMENT_END) ;
			while( (token = pLex->Lex()) != TT_EOF ) {
				if( token == TT_BLOCK_COMMENT_END )
					break ;
			}
			continue ;
		}

		switch(token) {
		// �L�[���[�h
		case TT_IDENTIFIER :
		case TT_STRING :
			array.Add(pLex->GetTokenImage()) ;
			break ;

		default :
			break ;
		}
	}
}
