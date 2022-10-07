//---------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFPart21FileC.h	                  �쐬���F2000.03.25
//
//	�P�D�N���X�T�v
//      �t�@�C���̓��͂Əo�͂��Ǘ�����
//
//	�Q�D����
//		����ԍ�	���t��		 �S����	    �T�v
//		�쐬		2000.03.25  ��
//		�X�V		2002.02.20	K.Naono		�w�b�_��͏����̉��P�Ή�
//
//---------------------------------------------------------
#include "SXFDataStructC.h"

class SXFPart21FileC:public CStdioFile{

public:
//
//	<�R���X�g���N�^>
//
    SXFPart21FileC();
    SXFPart21FileC( LPCTSTR IN_lpszFileName, UINT IN_nOpenFlags);

//
//	<�f�X�g���N�^>
//
    ~SXFPart21FileC();

//	MOD(S)	�w�b�_��͏����̉��P�Ή�	K.Naono		02.02.20
//	int  ReadHeadSection(HEADSECTION *OUT_Head);
	virtual int  ReadHeadSection(HEADSECTION* IO_Head);
//	MOD(E)	�w�b�_��͏����̉��P�Ή�	K.Naono		02.02.20

	int	 ReadHeaderInstance(INSTANCEDATA *OUT_Instance);
    int  ReadInstance(INSTANCEDATA *OUT_Instance);
    void WriteHeadSection(HEADSECTION *IN_Head);
    void WriteInstance(INSTANCEDATA *IN_Instance);

private:
	int featurecount;			/* ̨����ݽ�ݽ�� */

};
