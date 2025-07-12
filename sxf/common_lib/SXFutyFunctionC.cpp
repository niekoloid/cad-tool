/**
	All Rights Reserved,(c) JACIC 2001
	SXFutyFunctionC.cpp								�쐬���F2000.4.13

	�P�D�N���X�T�v
		���ʊ֐��N���X

	�Q�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.13			�{��(FQS)			�Ȃ��B

**/

#include "stdafx.h"
#include <math.h>
#include "SXFutyFunctionC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/**
	All Rights Reserved,(c) JACIC 2001
	SXFutyFunctionC.cpp								�쐬���F2000.4.13

	�P�D�@�\�T�v
		�R���X�g���N�^

	�Q�D�C���^�[�t�F�[�X
		void	SXFutyFunctionC::SXFutyFunctionC()
		
	����	�F	�^		������				���e
		�Ȃ�

	�R�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.13			�{��(FQS)			�Ȃ��B

**/
SXFutyFunctionC::SXFutyFunctionC()
{
}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFutyFunctionC.cpp								�쐬���F2000.4.13

	�P�D�@�\�T�v
		�f�X�g���N�^

	�Q�D�C���^�[�t�F�[�X
		void	SXFutyFunctionC::~SXFutyFunctionC()
		
	����	�F	�^		������				���e
		�Ȃ�

	�R�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2000.4.13			�{��(FQS)			�Ȃ��B

**/
SXFutyFunctionC::~SXFutyFunctionC()
{
}

/**
	All Rights Reserved,(c) JACIC 2001
	SXFutyFunctionC.cpp								�쐬���F2001.2.23

	�P�D�@�\�T�v
		�p�x��L����15���̕�����ɕϊ�

	�Q�D�C���^�[�t�F�[�X
		CString	SXFutyFunctionC::out_ctl(double IN_angle)
		
	����	�F	�^		������		���e
				double	IN_angle	�p�x

	���A�l�F
				CString		out		�L����15���̕�����

	�R�D����
	����ԍ�		���t��				�S����				�T�v
	�쐬			2001.2.23			�{��(FQS)			�Ȃ��B
	�X�V			2002.03.06			K.Naono				�o�O�C��

    �S�D�⑫����
			double �̌^���l�𕶎���ɕϊ����܂��B

			char *_ecvt( double value, int count, int *dec, int *sign )

				�߂�l

					_ecvt �͐��l������ւ̃|�C���^��Ԃ��܂��B

				����

					value   �ϊ����鐔�l

					count   �i�[���錅��

					dec		�i�[���ꂽ�����_�ʒu

					sign   �ϊ����ꂽ���l�̕���

			��F
				value	count	dec		sign
				1.0		15		1		100000000000000
				0.1		15		0		100000000000000
				0.01	15		-1		100000000000000

**/
CString SXFutyFunctionC::out_ctl(double IN_angle)
{
	// �����_�̈ʒu
	int		decimal;
	// ���̒l�����̒l���H
	int		sign;
	// ����
//	char	*buffer;
	// �T�C�Y
	int		precision = 15;

//	ADD(S)	��Q�C��	K.Naono	02.03.06
	if( IN_angle <= 1.0e-014 ) {
		IN_angle += 5.0e-015 ;
	}
//	ADD(E)	��Q�C��	K.Naono	02.03.06

//	MOD(S)	JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27
//	buffer = _ecvt(	IN_angle, 
//					precision,
//					&decimal,
//					&sign );
	char buffer[_CVTBUFSIZE] = "";
	_ecvt_s(	buffer,
				_countof(buffer),
				IN_angle, 
				precision,
				&decimal,
				&sign );
//	MOD(E)	JPCERT/CC �w�E �Ǝ㐫�Ή�	T.Matsushima	2015.04.27

	//�����_�̈ʒu��0�܂��͕��̏ꍇ��buffer�̑O��0.00�����K�v
	/* �Ⴆ��0.0001�̂Ƃ�decimal=-3*/
	/* 0.0�̂Ƃ�deciaml=0 */
	CString tmp_out,out ;
	if (decimal <= 0){
		CString tmp_str("0.00000000000000");
		tmp_out = CString(buffer);
		out = tmp_str.Left(abs(decimal)+2) + tmp_out.Left(precision - (abs(decimal)+1));
	}
	//�����_������
	else{
		out = CString(buffer);
		out.Insert(decimal,'.');
	}

	//����������
	if (sign)
		out = "-" + out;

	return out;
}
