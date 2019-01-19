//=============================================================================
//
// �o���b�g���� [bullet.h]
// Author : GP11A_341_22_�c�����z 
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"


#define BULLET_MAX				(60)

#define BULLET_SET_MAX			(30)

typedef struct
{
	D3DXMATRIX		mtxWorld;				// ���[���h�}�g���b�N�X
	LPD3DXMESH		D3DXMesh;				// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
	LPD3DXBUFFER	D3DXBuffMat;			// ���b�V���̃}�e���A�������i�[
	DWORD			NumMat;					// �������̑���
	D3DXVECTOR3		pos[BULLET_MAX];		// �ʒu
	D3DXVECTOR3		prevPos[BULLET_MAX];	// �O��̈ʒu
	D3DXVECTOR3		move[BULLET_MAX];		// �ړ���
	D3DXVECTOR3		refVec[BULLET_MAX];		// ���˃x�N�g��
	D3DXVECTOR3		rot[BULLET_MAX];		// ��]��
	D3DXVECTOR3		scl[BULLET_MAX];		// �X�P�[��
	int				time[BULLET_MAX];		// ����
	int				cntReflect[BULLET_MAX];	// �ړ�����
	bool			use[BULLET_MAX];		// �g�p���Ă��邩�ǂ���
	bool			reflect[BULLET_MAX];
	
} BULLET;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBullet(int type);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
BULLET *GetBullet(int bno);
bool SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Dest, int index);
D3DXVECTOR3 ReflectBullet(D3DXVECTOR3 pos, D3DXVECTOR3 normal, int index, int bno);

#endif
