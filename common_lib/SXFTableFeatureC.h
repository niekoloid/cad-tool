//------------------------------------------------------------
//	All Rights Reserved,(c) JACIC 2001
//	SXFTableFeatureC.h                    �쐬���F2000.04.10
//
//	�P�D�N���X�T�v
//		��`�e�[�u���t�B�[�`���f�[�^��ێ�����
//
//	�Q�D����
//	    ����ԍ�    ���t��         �S����    �T�v
//      �쐬		2000.04.10     ��
//
//------------------------------------------------------------
#ifndef _SXFTABLEFEATUREC_H_
#define _SXFTABLEFEATUREC_H_

class SXFInstanceIDC;
class SXFLayerC;

class SXFTableFeatureC  
{
public:
	SXFTableFeatureC();
	SXFTableFeatureC(SXFInstanceIDC* IN_InstanceIDManager);
	virtual ~SXFTableFeatureC();
	//WRITE
	void SetLayerFeature(SXFLayerC* IN_Layer);
    void SetFeatureData(int IN_Type,LPVOID IN_Struct);
    INSTANCEDATA* GetFeatureData( );
	//READ
    void SetStructData(int IN_Type, LPVOID IN_Class);
    LPVOID GetStructData();

private:
    INSTANCEDATA	m_FeatureData;			/* ��`ð��ٗv�f�ݽ�ݽ�ް� */
    LPVOID			m_StructData;			/* ��`ð��ٍ\���� */
	SXFInstanceIDC* m_InstanceIDManager;	/* �ݽ�ݽID��޼ު�� */

};

#endif
