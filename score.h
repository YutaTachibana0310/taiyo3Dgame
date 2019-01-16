//=============================================================================
//
// �X�R�A���� [score.h]
// Author : GP11A_341_22_�c�����z GP11A341_22_�c�����z
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

// �}�N����`
#define TEXTURE_GAME_SCORE		("data/TEXTURE/number16x32.png")	// �T���v���p�摜
#define TEXTURE_SCORE00_SIZE_X	(30)	// �e�N�X�`���T�C�Y
#define TEXTURE_SCORE00_SIZE_Y	(50)	// ����
#define SCORE_POS_X				(600)		// �|���S���̏����ʒuX
#define SCORE_POS_Y				(0)		// ����
#define SCORE_MAX				(999999)		// �X�R�A�̍ő�l
#define SCORE_DIGIT				(6)			// ����
#define NUM_SCORE				(2)


#define BULLET_HIT			(10)
#define ENEMY001_POINT		(20)
#define ENEMY002_POINT		(30)
#define BOSS_POINT			(100)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitScore(int type);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void AddScore( int add );

#endif
