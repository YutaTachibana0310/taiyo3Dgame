//=============================================================================
//
// �`���[�g���A������ [LifeGauge.h]
// Author : GP11A_341_22_�c�����z GP11A341_22_�c�����z
//
//=============================================================================
#ifndef _LIFEGAUGE_H_
#define _LIFEGAUGE_H_

// �}�N����`
#define TEXTURE_LIFEGAUGE_SIZE_X	 (500)	 // �e�N�X�`���T�C�Y
#define TEXTURE_LIFEGAUGE_SIZE_Y	 (100)	 // 
#define TEXTURE_LIFEICON_SIZE_X		 (100)	 // �e�N�X�`���T�C�Y
#define TEXTURE_LIFEICON_SIZE_Y		 (100)	 // 
#define LIFEGAUGE_POS_X_01			 (100)	 // ����X���W 
#define LIFEGAUGE_POS_Y_01			 (0)	 // ����Y���W
#define LIFEGAUGE_POS_X_02			 (650)	 // ����X���W 
#define LIFEGAUGE_POS_Y_02			 (0)	 // ����Y���W
#define LIFEICON_POS_X_01			 (0)	 // P1�A�C�R������X���W 
#define LIFEICON_POS_Y_01			 (0)	 // P1�A�C�R������Y���W
#define LIFEICON_POS_X_02			 (1170)	 // P2�A�C�R������X���W 
#define LIFEICON_POS_Y_02			 (0)	 // P2�A�C�R������Y���W


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitLifeGauge(int type);
void UninitLifeGauge(void);
void UpdateLifeGauge(void);
void DrawLifeGauge(void);
void SetTextureLifeGauge(int index, float x);


#endif
