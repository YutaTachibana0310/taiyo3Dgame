//=============================================================================
//
// ���f������ [rightArm.h]
// Author : GP11A_341_22_�c�����z 
//
//=============================================================================
#ifndef _RIGHTARM_H_
#define _RIGHTARM_H_

#include "main.h"

typedef struct {

	D3DXMATRIX			mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3			pos;					// ���݂̈ʒu
	D3DXVECTOR3			rot;					// ���݂̌���

	 int					nIdxShadow;				// �eID
	 float				fSizeShadow;				// �e�̃T�C�Y
	 D3DXCOLOR			colShadow;				// �e�̐F

}RIGHTARM;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitRightArm(void);
void UninitRightArm(void);
void UpdateRightArm(void);
void DrawRightArm(void);

#endif
