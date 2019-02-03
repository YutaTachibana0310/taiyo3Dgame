//=============================================================================
//
// �X���[�N�G�t�F�N�g���� [smoke.h]
// Author : GP11A_341_22_�c�����z 
//
//=============================================================================
#ifndef _SMOKE_H_
#define _SMOKE_H_

#include "main.h"

#define SMOKE_ONESET_MAX			(30)
#define SMOKE_SET_MAX				(2)

typedef struct
{
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos[SMOKE_ONESET_MAX];		// �ʒu
	D3DXVECTOR3 scl[SMOKE_ONESET_MAX];		// �X�P�[��
	bool		use[SMOKE_ONESET_MAX];				// �g�p���Ă��邩�ǂ���
	int			time[SMOKE_ONESET_MAX];
	float		Alpha[SMOKE_ONESET_MAX];
	float		angle;

} SMOKE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSmoke(int type);
void UninitSmoke(void);
void UpdateSmoke(void);
void DrawSmoke(void);
bool SetSmoke(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Dest, float sizeX, float sizeY, int index);
#endif
