//=============================================================================
//
// �v���C���[���� [player.h]
// Author : GP11A_341_22_�c�����z GP11A341_22_�c�����z
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//=============================================================================
//�}�N����`
//=============================================================================

#define PLAYER_MAX				(2)



typedef struct {
	
	LPD3DXALLOCATEHIERARCHY		D3DXAlloc;			// ID3DXAlloc�C���^�[�t�F�[�X�ւ̃|�C���^
	LPD3DXLOADUSERDATA			D3DXUserData;		// X�t�@�C���̃��[�U�[��`
	LPD3DXFRAME					D3DXFrame;			// �t���[���K�w�̐e�̃|�C���^
	LPD3DXANIMATIONCONTROLLER	D3DXAnim;
	D3DXMATRIX					mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3					pos;				// ���݂̈ʒu
	D3DXVECTOR3					prevPos;			// �ߋ��̈ʒu
	D3DXVECTOR3					move;				// �ړ���
	D3DXVECTOR3					rot;				// ���݂̌���
	D3DXVECTOR3					rotDest;
	bool						use;			
	int							IdxShadow;			// �eID
	float						SizeShadow;			// �e�̃T�C�Y
	D3DXCOLOR					colShadow;			// �e�̐F


}PLAYER;

enum {
	P1,
	P2
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(int type);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER *GetPlayer(int index);
bool PlayerDamageManager(int index);
bool CheckFieldInPlayer(int index);

#endif
