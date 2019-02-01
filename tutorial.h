//=============================================================================
//
// �`���[�g���A������ [Tutorial.h]
// Author : GP11A_341_22_�c�����z
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_


// �}�N����`
#define TEXTURE_TUTORIAL1	("data/TEXTURE/tutorial02.png")		// ���s�p�摜
#define TEXTURE_TUTORIAL2	("data/TEXTURE/tutorial2.png")		// ���s�p�摜
#define TEXTURE_TUTORIAL3	("data/TEXTURE/tutorial3.png")		// ���s�p�摜



#define TEXTURE_MAX				 (1)	 // �摜����
#define TEXTURE_TUTORIAL_SIZE_X	 (800)	 // �e�N�X�`���T�C�Y
#define TEXTURE_TUTORIAL_SIZE_Y	 (600)	 // 

#define TUTORIAL_POS_X	 (250)	 // ����X���W 
#define TUTORIAL_POS_Y	 (100)	 // ����Y���W

#define	NUM_TUTORIAL				 (2)	 // �|���S����
#define TUTORIAL_TEXTURE_MAX		 (1)	 // ��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTutorial(int type);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);


#endif
