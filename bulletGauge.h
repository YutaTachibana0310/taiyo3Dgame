//=============================================================================
//
// �o���b�g�Q�[�W���� [bulletGauge.h]
// Author : GP11A_341_22_�c�����z 
//
//=============================================================================
#ifndef _BULLETGAUGE_H_
#define _BULLETGAUGE_H_


// �}�N����`
#define TEXTURE_BULLETGAUGE_SIZE_X	 (100)	 // �e�N�X�`���T�C�Y
#define TEXTURE_BULLETGAUGE_SIZE_Y	 (75)	 // 

#define BULLETGAUGE_POS_X_01			 (0)	 // ����X���W 
#define BULLETGAUGE_POS_Y_01			 (100)	 // ����Y���W
#define BULLETGAUGE_POS_X_02			 (1150)	 // ����X���W 
#define BULLETGAUGE_POS_Y_02			 (100)	 // ����Y���W

enum {
	OUTER,
	INNER
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBulletGauge(int type);
void UninitBulletGauge(void);
void UpdateBulletGauge(void);
void DrawBulletGauge(void);
void SetTextureBulletGauge(int index, float val);
void SetVertexBulletGauge(int index, float val);


#endif
