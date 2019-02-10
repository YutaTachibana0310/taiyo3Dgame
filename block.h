//=============================================================================
//
// �u���b�N���� [block.h]
// Author : GP11A_341_22_�c�����z
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define	BLOCK_MAX				(106)	// �u���b�N�̍ő吔
#define VTX_MAX					(104)	// �|���S������
#define BLOCK_NUM_CORNER		(4)		// �S�p
#define BLOCK_NUM_LEFTSIDE		(24)	// �|���S���̃i���o�����O
#define BLOCK_NUM_NEARSIDE		(53)	// 
#define BLOCK_NUM_RIGHTSIDE		(77)	// 
#define BLOCK_NUM_FEARSIDE		(106)	// 

typedef struct {
	
	D3DXVECTOR3					pos;		// ���݂̈ʒu
	int							life;		// �u���b�N�̎���
	int							textureNum; // �e�N�X�`���[�̔ԍ�
	bool						use;		// �g�p���

}BLOCK;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBlock(int type);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);

BLOCK *GetBlock(int bno);
void BlockDamageManager(int bno);
bool HitCheckBlock(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1);
bool HitCheckCornerBlock(D3DXVECTOR3 pos0);

#endif
