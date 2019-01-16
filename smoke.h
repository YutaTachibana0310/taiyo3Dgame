//=============================================================================
//
// �X���[�N�G�t�F�N�g���� [smoke.h]
// Author : GP11A_341_22_�c�����z GP11A341_22_�c�����z
//
//=============================================================================
#ifndef _SMOKE_H_
#define _SMOKE_H_

#include "main.h"

typedef struct
{
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 scl;		// �X�P�[��
	bool		use;				// �g�p���Ă��邩�ǂ���
	float		angle;
	float		Alpha;
	int			time;

} SMOKE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSmoke(int type);
void UninitSmoke(void);
void UpdateSmoke(void);
void DrawSmoke(void);
bool SetSmoke(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Dest);
#endif
