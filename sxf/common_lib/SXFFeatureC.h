//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFFeatureC.h                         �쐬���F2000.04.17
//
//	�P�D�N���X�T�v
//      ��ʗv�f�t�B�[�`���[�f�[�^��ێ�����     
//
//	�Q�D����
//	    ����ԍ�	���t��			�S����			�T�v
//      �쐬		2000.04.17		��
//		�X�V		2015.04.27		T.Matsushima	JPCERT/CC �w�E �Ǝ㐫�Ή�
//
//------------------------------------------------------------
#ifndef _SXFFEATUREC_H_
#define _SXFFEATUREC_H_

#include <afx.h>
#include "SXFDataStructC.h"

class SXFInstanceIDC;

class SXFFeatureC  
{
public:
	void SetReturnFlag();
	SXFFeatureC();
	SXFFeatureC(SXFInstanceIDC* IN_InstanceIDManager);
	virtual ~SXFFeatureC();
	//read
    BOOL SetStructData(INSTANCEDATA* IN_Feature);
	LPVOID GetAssemblyStructData();
//	LPVOID GetStructData(char*& OUT_Type);					JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
	LPVOID GetStructData(char*& OUT_Type,size_t TypeSize);	// �o�b�t�@�T�C�Y��n���悤�ɕύX
	//write
    void SetFeatureData(LPCTSTR IN_TypeName,LPVOID IN_Struct);
	void SetAssemblyData(int IN_Type,LPVOID IN_Struct);
    INSTANCEDATA* GetFeatureData( );
	int GetSheetX(int IN_Type);
	int GetSheetY(int IN_Type);
private:
	int				m_ReturnFlag;			/* ̨����\���̕ԋp�ς��׸� */
    INSTANCEDATA	m_FeatureData;			/* ��ʗv�f̨����ݽ�ݽ�ް� */
    char			m_TypeName[30];			/* ̨����^ */
    LPVOID			m_StructData;			/* ��ʗv�f�\���� */
	SXFInstanceIDC* m_InstanceIDManager;	/* �ݽ�ݽID�Ǘ���޼ު�� */
};

#endif

