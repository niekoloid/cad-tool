//---------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFPart21FileReadC.h	              �쐬���F2000.03.26
//
//	�P�D�N���X�T�v
//		�t�@�C���̓��͂��Ǘ�����
// 
//	�Q�D����
//		����ԍ�	���t��		 �S����	    �T�v
//		�쐬		2000.03.26   ��
//
//---------------------------------------------------------
#ifndef _SXFPART21FILEREADC_H_
#define _SXFPART21FILEREADC_H_

class SXFTableManagerC;
class SXFReadFeatureManagerC;
class SXFComInfoC;

class SXFPart21FileReadC{
public:
//
//	<�R���X�g���N�^>
//
    SXFPart21FileReadC();
	SXFPart21FileReadC(SXFTableManagerC* IN_TableManager,
                       SXFReadFeatureManagerC* IN_ReadFeatureManager,
                       SXFComInfoC* IN_ComInfo);

//
//	<�f�X�g���N�^>
//
    ~SXFPart21FileReadC();
//
    int OpenPart21ReadFile( LPCTSTR IN_FileName );
    void ClosePart21ReadFile(  );
    void GetHeadData(int *OUT_Level,
                     int *OUT_Mode,
                     char *OUT_FileName,
                     char *OUT_Author,
                     char *OUT_Organization,
                     char *OUT_Version,
                     char *OUT_OriginatingSystem );
protected:
    BOOL RegisterFeatureEntity(INSTANCEDATA *IN_Instance);
    BOOL RegisterFeatureTable(INSTANCEDATA *IN_Instance);
    BOOL RegisterFeatureAssembly(INSTANCEDATA *IN_Instance);
    void ClearInstanceData();

	SXFTableManagerC*	m_TableManager;	/* ��`ð��ٗv�fMapping�Ǘ���޼ު�� */
	SXFReadFeatureManagerC* m_ReadFeatureManager;	/* Read�Ǘ���޼ު�� */
    HEADSECTION				m_HeadSection;			/* ͯ�ޏ�� */
    INSTANCEDATA			m_InstanceData;			/* �ݽ�ݽ�ް� */
    SXFPart21FileC*			m_File;					/* ̧�يǗ���޼ު�� */
	SXFComInfoC*			m_ComInfo;				/* ���ʏ��Ǘ���޼ު�� */
};

#endif

