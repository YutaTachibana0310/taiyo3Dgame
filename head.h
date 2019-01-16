//=============================================================================
//
// ���f������ [model.h]
// Author : GP11A_341_22_�c�����z 
//
//=============================================================================
#ifndef _HEAD_H_
#define _HEAD_H_

#include "main.h"

typedef struct
{
	D3DXMATRIX			mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3			pos;				// ���݂̈ʒu
	D3DXVECTOR3			rot;				// ���݂̌���
	D3DXVECTOR3			scl;				// �g�嗦
	int					nIdxShadow;			// �eID
	float				fSizeShadow;		// �e�̃T�C�Y
	D3DXCOLOR			colShadow;			// �e�̐F

}HEAD;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitHead(void);
void UninitHead(void);
void UpdateHead(void);
void DrawHead(void);

D3DXVECTOR3 GetPosHead(void);
D3DXVECTOR3 GetRotHead(void);
D3DXVECTOR3 GetRotDestHead(void);

#endif
