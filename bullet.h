//=============================================================================
//
// �o���b�g���� [bullet.h]
// Author : GP11A_341_22_�c�����z 
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"


#define BULLET_MAX				(128)
#define BULLET_ONESET_MAX		(5)
#define BULLET_SET_MAX			(2)
#define BULLET_CHARGE_FRAME_CNT	(10)
#define BULLET_CHARGE_MAX		(2.0f)

typedef struct
{
	D3DXMATRIX		mtxWorld;						// ���[���h�}�g���b�N�X
	LPD3DXMESH		D3DXMesh;						// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
	LPD3DXBUFFER	D3DXBuffMat;					// ���b�V���̃}�e���A�������i�[
	DWORD			NumMat;							// �������̑���
	D3DXVECTOR3		pos[BULLET_ONESET_MAX];			// �ʒu
	D3DXVECTOR3		prevPos[BULLET_ONESET_MAX];		// �O��̈ʒu
	D3DXVECTOR3		move[BULLET_ONESET_MAX];		// �ړ���
	D3DXVECTOR3		refVec[BULLET_ONESET_MAX];		// ���˃x�N�g��
	D3DXVECTOR3		rot[BULLET_ONESET_MAX];			// ��]��
	D3DXVECTOR3		scl[BULLET_ONESET_MAX];			// �X�P�[��
	D3DXVECTOR3		sclIncrease;	// �X�P�[���̑����l
	D3DXVECTOR3		size[BULLET_ONESET_MAX];		// �傫��
	int				time[BULLET_ONESET_MAX];		// ����
	int				cntReflect[BULLET_ONESET_MAX];	// ���ˉ�
	bool			use[BULLET_ONESET_MAX];			// �g�p���
	bool			reflect[BULLET_ONESET_MAX];		// ���˂̑O���ォ
	
} BULLET;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBullet(int type);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
BULLET *GetBullet(int bno);
bool SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float Dest, int index);
D3DXVECTOR3 ReflectBullet(D3DXVECTOR3 pos, D3DXVECTOR3 normal, int index, int bno);
void CheckBlockHitBullet(int blockNo, int index, D3DXVECTOR3 pos);

#endif
