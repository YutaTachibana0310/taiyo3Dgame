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
#define PLAYER_LIFE_MAX		(100.0f)



typedef struct {
	
	LPD3DXALLOCATEHIERARCHY		D3DXAlloc;			// ID3DXAlloc�C���^�[�t�F�[�X�ւ̃|�C���^
	LPD3DXLOADUSERDATA			D3DXUserData;		// X�t�@�C���̃��[�U�[��`
	LPD3DXFRAME					D3DXFrame;			// �t���[���K�w�̐e�̃|�C���^
	LPD3DXANIMATIONCONTROLLER	D3DXAnim;			// �A�j���[�V�������
	D3DXMATRIX					mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3					pos;				// ���݂̈ʒu
	D3DXVECTOR3					prevPos;			// �ߋ��̈ʒu
	D3DXVECTOR3					move;				// �ړ���
	D3DXVECTOR3					rot;				// ��]��
	D3DXVECTOR3					rotDest;			// ���݂̌���
	bool						use;				// �g�p���
	float						speed;				// �ړ��̑���
	float						life;				// �̗�
	float						special;			// 
	int							IdxShadow;			// �eID
	float						SizeShadow;			// �e�̃T�C�Y
	D3DXCOLOR					colShadow;			// �e�̐F

}PLAYER;

enum {
	P1,
	P2
};

enum {
	TEXTURE001,
	TEXTURE002,
	TEXTURE003,
	TEXTURE004,
	TEXTURE005
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
void CheckNorPlayer(D3DXVECTOR3 nor0, int index);

#endif
