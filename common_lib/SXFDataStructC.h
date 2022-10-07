//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFDataStructC.h	                  �쐬���F2000.03.25
//
//	�P�D�N���X�T�v
//      Instance Data��Head Section Data�̍\���̂̒�`
//      
//	�Q�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.03.25     ��       �Ȃ�
//
//------------------------------------------------------------
#ifndef _SXFDATASTRUCTC_H_
#define _SXFDATASTRUCTC_H_

#include <afx.h>

struct HEADSECTION{
    CString FileName;
    int     Level;					/* ���� */
    int     Mode;					/* Ӱ�� */
										//0:ambilateral(mix)
										//1:Feature
										//2:AP202
	CString Author;					/* �쐬�Җ� */
    CString Organization;			/* �쐬�ҏ��� */
    CString Version;				/* �ް�ޮ� */
	CString OriginatingSystem;		/* ��ݽڰ��� */
	int		scadec_flg;				/* SCADEÇ���׸� */
										//-1:SCADEC�ȊO��̧��
										//1:SCADEÇ��
};

#define SXF_IM_NULL         0

#define SXF_IM_COMMENT      1
#define SXF_IM_SECTIONMARK  2
#define SXF_IM_HEADSECTION  3

#define SXF_IM_FT_ENTITY    21
#define SXF_IM_FT_TABLE     22
#define SXF_IM_FT_ASSEMBLY  23


struct INSTANCEDATA{
    int     InstanceMode;//0  NULL,
                         //1  Comment
                         //2  SectionMark
                         //3  HeadSection
                         //21 Feature_Entity
                         //22 Feature_Table
                         //23 Feature_Assembly
	int     InstanceID;		/* �ݽ�ݽID */
	CString EntityName;		/* ��èè�� */
    CString EntityData;		/* ��èè�ް� */
};

#endif

