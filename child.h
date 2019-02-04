//=============================================================================
//
// �q�����f������ [child.h]
// Author : GP11A_341_22_�c�����z
//
//=============================================================================
#ifndef _CHILD_H_
#define _CHILD_H_

#include "main.h"


#define CHILD_MAX			(30)
#define CHILD_SET_MAX		(2)
#define CHILD_ONESET_MAX	(30)

typedef struct {

D3DXVECTOR3			pos[CHILD_ONESET_MAX];				// ���f���̈ʒu
D3DXVECTOR3			rot[CHILD_ONESET_MAX];				// ���f���̌���(��])
D3DXVECTOR3			scl[CHILD_ONESET_MAX];				// ���f���̑傫��(�X�P�[��)
bool				use[CHILD_ONESET_MAX];
int					life[CHILD_ONESET_MAX];

}CHILD;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitChild(void);
void UninitChild(void);
void UpdateChild(void);
void DrawChild(void);
CHILD *GetChild(int index);

#endif
