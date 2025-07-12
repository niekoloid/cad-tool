/**
	All Rights Reserved,(c) JACIC 2001
	SXFReadMapManagerC.cpp								�쐬���F2000.4.25

	�P�D�N���X�T�v
	Read��(�t�B�[�`���R�����g�j�̃t�B�[�`���I�u�W�F�N�g��
						Mapping�I�u�W�F�N�g�̊Ǘ����s���N���X�B


	�Q�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.25			�{��(FQS)			�Ȃ��B
	�X�V			2015.04.27			T.Matsushima		JPCERT/CC �w�E �Ǝ㐫�Ή�

**/

#if !defined(AFX_SXFREADMAPMANAGERC_H__7A7CDA80_1A22_11D4_A76E_00000EB03267__INCLUDED_)
#define AFX_SXFREADMAPMANAGERC_H__7A7CDA80_1A22_11D4_A76E_00000EB03267__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SXFDataStructC.h"

class SXFFeatureC;

class SXFReadMapManagerC  
{
public:
	void SetReturnFlag();
	LPVOID GetAssemblyStructData();
//	LPVOID GetStructData(char*& OUT_TypeName);						JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
	LPVOID GetStructData(char*& OUT_TypeName,size_t TypeNameSize);	// �o�b�t�@�T�C�Y��n���悤�ɕύX
	BOOL SetFeatureData(INSTANCEDATA* IN_Instance);
	SXFReadMapManagerC();
	virtual ~SXFReadMapManagerC();

private:
	SXFFeatureC* m_Feature;		/* ̨�����޼ު�� */
};

#endif // !defined(AFX_SXFREADMAPMANAGERC_H__7A7CDA80_1A22_11D4_A76E_00000EB03267__INCLUDED_)
