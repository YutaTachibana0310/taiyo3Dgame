//=============================================================================
//
// �^�C�g����ʏ��� [title.h]
// Author : GP11A_341_22_�c�����z
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************


#define	TITLE_POS_X			(350)								// �^�C�g���̕\���ʒu
#define	TITLE_POS_Y			(250)								// �^�C�g���̕\���ʒu
#define	TITLE_SIZE_X		(600)							// �^�C�g���̕�
#define	TITLE_SIZE_Y		(250)							// �^�C�g���̍���

#define	TITLE_LOGO_POS_X	(550)							// �^�C�g�����S�̕\���ʒu
#define	TITLE_LOGO_POS_Y	(500)							// �^�C�g�����S�̕\���ʒu
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
