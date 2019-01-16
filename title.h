//=============================================================================
//
// �^�C�g����ʏ��� [title.h]
// Author : GP11A_341_22_�c�����z GP11A341_22_�c�����z
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TITLE		("data/TEXTURE/title.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_SPACE		("data/TEXTURE/space.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_GAMESTART	("data/TEXTURE/gamestart.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_OPTION		("data/TEXTURE/option.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_EXIT		("data/TEXTURE/exit.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_SELECT		("data/TEXTURE/yajirusi.png")	// �ǂݍ��ރe�N�X�`���t�@�C����



#define	TITLE_POS_X			(0)								// �^�C�g���̕\���ʒu
#define	TITLE_POS_Y			(0)								// �^�C�g���̕\���ʒu
#define	TITLE_SIZE_X		(800)							// �^�C�g���̕�
#define	TITLE_SIZE_Y		(600)							// �^�C�g���̍���

#define	TITLE_LOGO_POS_X	(200)							// �^�C�g�����S�̕\���ʒu
#define	TITLE_LOGO_POS_Y	(300)							// �^�C�g�����S�̕\���ʒu
#define	TITLE_LOGO_SIZE_X	(200)							// �^�C�g�����S�̕�
#define	TITLE_LOGO_SIZE_Y	(150)							// �^�C�g�����S�̍���
#define SET_LOGO			(50)

#define	TITLE_SELECT_POS_X	(5)								// �^�C�g�����S�̕\���ʒu
#define	TITLE_SELECT_POS_Y	(300)							// �^�C�g�����S�̕\���ʒu
#define	TITLE_SELECT_SIZE_X	(60)							// �^�C�g�����S�̕�
#define	TITLE_SELECT_SIZE_Y	(60)							// �^�C�g�����S�̍���
#define SELECT_MOVE			(50)							// �Z���N�g�̈ړ��l

#define NUM_TITLE			(2)
#define LOGO_MAX			(4)
#define SELECT_START		(0)
#define SELECT_OPTION		(1)
#define SELECT_EXIT			(2)

enum {

	SPACE,
	GAMESTART,
	OPTION,
	EXIT,
	SELECT,
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTitle(int type);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif
