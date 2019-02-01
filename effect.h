//=============================================================================
//
// �G�t�F�N�g���� [effect.h]
// Author : GP11A_341_22_�c�����z
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

typedef struct
{
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 scl;		// �X�P�[��
	D3DXVECTOR3 move;		// �ړ���
	float		fWidth;			// ��
	float		fHeight;			// ����
	int			IndxShadow;			// �eID
	bool		bUse;				// �g�p���Ă��邩�ǂ���
	float		angle;
	float		Alpha;
	int			time;

} EFFECT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEffect(int type);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
bool SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Dest);
#endif
