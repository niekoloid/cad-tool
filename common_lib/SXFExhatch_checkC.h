/**
	All Rights Reserved,(c) JACIC 2001
	SXFExHatch_checkC.h								�쐬���F2000.4.3

	�P�D�N���X�T�v
	�n�b�`���O(����`)�t�B�[�`���̃��[���`�F�b�N���s���N���X

	�Q�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.3			�{��(FQS)			�Ȃ��B

**/

#if !defined(AFX_SXFEXHATCH_CHECKC_H__70C850E4_0A29_11D4_A76E_00000EB03267__INCLUDED_)
#define AFX_SXFEXHATCH_CHECKC_H__70C850E4_0A29_11D4_A76E_00000EB03267__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afx.h>
#include "SXFStruct.h"
#include "SXFTableCheckC.h"

class SXFTableManagerC;
class SXFWriteManagerC;
class SXFReadFeatureManagerC;
class SXFComInfoC;

class SXFExhatch_checkC  :public SXFTableCheckC
{
public:
	int ReadFeature_Check(Externally_Defined_Hatch_Struct* IN_Struct);
	int attr_rule_check(Externally_Defined_Hatch_Struct* IN_exhatch_str);
	int str_rule_check(Externally_Defined_Hatch_Struct* IN_exhatch_str);
	int Feature_rule_check(Externally_Defined_Hatch_Struct* IN_exhatch_str,
							SXFTableManagerC* IN_TableManager,
							SXFReadFeatureManagerC* IN_ReadFeatureManager,
							SXFWriteManagerC* IN_WriteManager,
							CString IN_InstanceID,
							SXFComInfoC* IN_Info);
	SXFExhatch_checkC();
	virtual ~SXFExhatch_checkC();

	SXFReadFeatureManagerC* m_ReadFeatureManager;
	SXFWriteManagerC* m_WriteManager;
};

#endif // !defined(AFX_SXFEXHATCH_CHECKC_H__70C850E4_0A29_11D4_A76E_00000EB03267__INCLUDED_)
