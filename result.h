//=============================================================================
//
// ���U���g���� [result.h]
// Author : GP11A_341_22_�c�����z
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_


// �}�N����`
#define TEXTURE_CLEAR 		("data/TEXTURE/gameclear.png")	// �T���v���p�摜
#define TEXTURE_GAMEOVER 	("data/TEXTURE/gameover.png")	// �T���v���p�摜


#define TEXTURE_SAMPLE00_SIZE_X_RESULT	(800) // �e�N�X�`���T�C�Y
#define TEXTURE_SAMPLE00_SIZE_Y_RESULT	(600) // ����

#define TEXTURE_PATTERN_DIVIDE_X_RESULT	(8)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_RESULT	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define TIME_ANIMATION_RESULT			(100)	// �A�j���[�V�����̐؂�ւ��J�E���g
#define	NUM_RESULT						(2)		// �|���S����
#define RESULT_MAX						(2)		// ���U���g�̎��

enum {
	CLEAR,
	GAMEOVER
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitResult(int type);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void SetTextureResult(int num);


#endif
