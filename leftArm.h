//=============================================================================
//
// ���f������ [model.h]
// Author : GP11A_341_22_�c�����z 
//
//=============================================================================
#ifndef _LEFTARM_H_
#define _LEFTARM_H_

#include "main.h"

typedef struct
{
	D3DXMATRIX			mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3			pos;					// ���݂̈ʒu
	D3DXVECTOR3			rot;					// ���݂̌���

	int					nIdxShadow;				// �eID
	float				fSizeShadow;				// �e�̃T�C�Y
	D3DXCOLOR			colShadow;				// �e�̐F

}LEFTARM;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitLeftArm(void);
void UninitLeftArm(void);
void UpdateLeftArm(void);
void DrawLeftArm(void);

LEFTARM *GetLeftArm(int index);

#endif
