//=============================================================================
//
// ���� [field.h]
// Author : GP11A_341_22_�c�����z 
//
//=============================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

#include "main.h"
#define FIELD_SIZE_X	(400.0f)
#define FIELD_SIZE_Y	(0.0f)
#define FIELD_SIZE_Z	(150.0f)					

typedef struct {

	D3DXMATRIX				mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3				pos;				// ���݂̈ʒu
	D3DXVECTOR3				rot;				// ���݂̌���
	int						scanData;			//

}FIELD;

//typedef struct
//{
//	int			nextTexType;	// �e�N�X�`���[�̃^�C�v
//	int			scanResult;		// �f�[�^�̓ǂݍ���
//	int			nextIndex;		// POP����OBJ�̃A�h���X�ԍ�
//	float		nextPopObj;	// POP����̍��W
//	D3DXVECTOR3 nextSize;		// POP���鏉�����W
//	D3DXVECTOR3 nextNor;
//
//}FIELDDATA;

enum {

	BOLCK_TEX,
	IRON_TEX,
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitField(int type);
void UninitField(void);
void UpdateField(void);
void DrawField(void);
void InitMakeVertex(void);
bool HitCheckField(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1);
FIELD *GetField(int fno);
void SetMakeField(void);

#endif
