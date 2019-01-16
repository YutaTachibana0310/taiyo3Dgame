//=============================================================================
//
// ���f������ [model.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"


#define ENEMY_MAX			(1)

typedef struct {

D3DXVECTOR3			pos;				// ���f���̈ʒu
D3DXVECTOR3			rot;				// ���f���̌���(��])
D3DXVECTOR3			scl;				// ���f���̑傫��(�X�P�[��)
bool				use;
int					life;

}ENEMY;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
ENEMY *GetEnemy(int index);

#endif
