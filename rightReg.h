//=============================================================================
//
// ���f������ [model.h]
// Author : GP11A_341_22_�c�����z 
//
//=============================================================================
#ifndef _RIGHTREG_H_
#define _RIGHTREG_H_

#include "main.h"

typedef struct {

	D3DXMATRIX			mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3			pos;					// ���݂̈ʒu
	D3DXVECTOR3			rot;					// ���݂̌���

	 int				nIdxShadow;				// �eID
	 float				fSizeShadow;				// �e�̃T�C�Y
	 D3DXCOLOR			colShadow;				// �e�̐F

}RIGHTREG;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitRightReg(void);
void UninitRightReg(void);
void UpdateRightReg(void);
void DrawRightReg(void);

#endif
