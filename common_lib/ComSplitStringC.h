/**
	All Rights Reserved,(c) JACIC 2001
	ComSplitStringC.h						�쐬���F1998.09.04

	�P�D�N���X�T�v
		�����񕪊��N���X

	�Q�D����
		����ԍ�	���t��		�S����		�T�v
		�쐬		1998.09.04	����(FS)

**/
#ifndef _COMSPLITSTRINGC_CLASS_
#define _COMSPLITSTRINGC_CLASS_

#include <afx.h>

class ComSplitStringC {
public :
//
//	<�R���X�g���N�^>
//
	ComSplitStringC();
	ComSplitStringC(CString& IN_Str) {
		m_String = IN_Str ;
	}
	ComSplitStringC(CString* IN_Str) {
		m_String = *IN_Str ;
	}
	ComSplitStringC(char* IN_Str) {
		m_String = IN_Str ;
	}
//
//	<�f�X�g���N�^>
//
	~ComSplitStringC() {}
//
//	<�w�肳�ꂽ��؂蕶���R�[�h�ŕ�������>
//
	CStringArray*	Split(int	IN_SplitCode) {
		m_SplitData.SetSize(0) ;
		CString		str ;
		LPTSTR		wp = m_String.GetBuffer(m_String.GetLength()) ;

		char	*dp, *p ;
		for(dp=p=(char*)wp; p; dp=p+1){
			if( (p=strchr(dp,IN_SplitCode)) ) {
				p[0] = NULL ;
			}
			str = dp ;
			m_SplitData.Add(str) ;
		}
		m_String.ReleaseBuffer() ;
		return &m_SplitData ;
	}
//
//	<�w�肳�ꂽ������ŕ�������>
//
	CStringArray*	Split(char	*IN_SplitStr) {
		m_SplitData.SetSize(0) ;
		CString		str ;
		LPTSTR		wp = m_String.GetBuffer(m_String.GetLength()) ;

		char	*dp, *p ;
		for(dp=p=(char*)wp; p; dp=p+1){
			if( (p=strstr(dp,IN_SplitStr)) ) {
				memset(p,0x00,strlen(IN_SplitStr)) ;
				p += (strlen(IN_SplitStr)-1) ;
			}
			else{
				break;
			}
			str = dp ;
			m_SplitData.Add(str) ;
		}
		m_String.ReleaseBuffer() ;
		return &m_SplitData ;
	}

protected :
//
//	<������>
//
	CString		m_String ;
//
//	<�������������񃊃X�g>
//
	CStringArray	m_SplitData ;
} ;
#endif