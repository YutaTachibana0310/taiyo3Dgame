//=============================================================================
//
// �������f������ [leftReg.h]
// Author : GP11A_341_22_�c�����z GP11A_341_22_�c�����z
//
//=============================================================================
#ifndef _LEFTREG_H_
#define _LEFTREG_H_

#include "main.h"

typedef struct {

	D3DXMATRIX			mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3			pos;					// ���݂̈ʒu
	D3DXVECTOR3			rot;					// ���݂̌���

	static int					nIdxShadow;				// �eID
	static float				fSizeShadow;				// �e�̃T�C�Y
	static D3DXCOLOR			colShadow;				// �e�̐F

}LEFTREG;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitLeftReg(void);
void UninitLeftReg(void);
void UpdateLeftReg(void);
void DrawLeftReg(void);


#endif
