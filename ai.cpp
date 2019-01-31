//=============================================================================
//
// AI���� [ai.cpp]
// Author : GP11A_341_22_�c�����z 
//
//=============================================================================
#include "ai.h"
#include "bullet.h"
#include "player.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOVE_CMP_MAX			(4)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
enum {
	PATTERN1,
	PATTERN2,
	PATTERN3,
	PATTERN4
};

//===========================================================================
// NPC�̈ړ�����
// ���@���FD3DXVECTOR3 pos(���̈ړ��ʒu)�AD3DXVECTOR3 normal(�|���S���̖@��)
//		   int index(�v���C���[�̃A�h���X�ԍ�)
// �߂�l�F
//==========================================================================
void NonePlayerMove(void)
{
	BULLET *bullet = GetBullet(P2);
	PLAYER *player = GetPlayer(P2);
	float box, out;
	float atc[MOVE_CMP_MAX], chase[MOVE_CMP_MAX], escape[MOVE_CMP_MAX];
	float pattern[MOVE_CMP_MAX];

	// ���C�t�ɂ���r
	atc[PATTERN1] = FuzzyRightDown(player->life, 40, 80);
	chase[PATTERN1] = FuzzyTrapezoid(player->life, 0, 20, 60, 80);
	escape[PATTERN1] = FuzzyRightUp(player->life, 50, 80);

	// �����ɂ���r
	float distance = 0.0f;
	float a = player[P1].pos.x - player[P2].pos.x;
	float b = player[P1].pos.z - player[P2].pos.z;

	distance = a + b;

	atc[PATTERN2] = FuzzyRightDown(distance, 100, 500);
	chase[PATTERN2] = FuzzyTrapezoid(distance, 0, 200, 400, 500);
	escape[PATTERN2] = FuzzyRightUp(distance, 0, 100);

	pattern[PATTERN1] = atc[PATTERN1] + atc[PATTERN2];
	pattern[PATTERN2] = chase[PATTERN1] + chase[PATTERN2];
	pattern[PATTERN3] = escape[PATTERN1] + escape[PATTERN2];
	
	box = And(pattern[PATTERN1], pattern[PATTERN2]);
	out = And(box, pattern[PATTERN3]);

	if (out == pattern[PATTERN1])
	{
		bullet->sclIncrease = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
		SetBullet(player->pos, player->rot, bullet->sclIncrease, 0, P2);
		bullet->sclIncrease = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	if (out == pattern[PATTERN2])
	{
		D3DXVECTOR3 vec = player[P1].pos - player[P2].pos;
		D3DXVec3Normalize(&vec, &vec);
		player->move.x -= vec.x * player->speed;
		player->move.z -= vec.z * player->speed;
	}

	if (out == pattern[PATTERN3])
	{
		D3DXVECTOR3 vec = player[P1].pos - player[P2].pos;
		D3DXVec3Normalize(&vec, &vec);
		player->move.x += vec.x * player->speed;
		player->move.z += vec.z * player->speed;

	}

}


//*****************************************************************************
// �t�@�W�[�����o�[�V�b�v�E�オ��^
// ���@���Ffloat val(�Q�l�ɂ��鐔�l), float x0(�͈͂̍ŏ��l), float x1(�͈͂̍ő�l)
// �߂�l�Ffloat�^�@0.0�`1.0�̐��l
//*****************************************************************************
float FuzzyRightUp(float val, float x0, float x1)
{
	if (val <= x0)
	{
		return 0.0f;
	}
	else if (val >= x1)
	{
		return 1.0f;
	}
	else
	{
		// ������v�Z
		float denom = x1 - x0;
		return (val / denom) - (x0 / denom);
	}
}

//*****************************************************************************
// �t�@�W�[�����o�[�V�b�v�E������^
// ���@���Ffloat val(�Q�l�ɂ��鐔�l), float x0(�͈͂̍ŏ��l), float x1(�͈͂̍ő�l)
// �߂�l�Ffloat�^�@0.0�`1.0�̐��l
//*****************************************************************************
float FuzzyRightDown(float val, float x0, float x1)
{
	if (val <= 0)
	{
		return 1;
	}
	else if (val >= x1)
	{
		return 0;
	}
	else
	{
		float denom = x1 - x0;
		return (x1 / denom) - (val / denom);
	}
}

//*****************************************************************************
// �t�@�W�[�����o�[�V�b�v�O�p�^
// ���@���Ffloat val(�Q�l�ɂ��鐔�l), float x0(�͈͂̍ŏ��l), float x1(�͈͂̍ő�l)
//		   float x2()
// �߂�l�Ffloat�^�@0.0�`1.0�̐��l
//*****************************************************************************
float FuzzyTriangle(float val, float x0, float x1, float x2)
{
	if (val <= x0)
	{
		return 0;
	}
	else if (val == x1)
	{
		return 1;
	}
	else if ((val > x0) && (val < x1))
	{
		float denom = x1 - x0;
		return (val / denom) - (x0 / denom);
	}
	else
	{
		float denom = x2 - x1;
		return (x2 / denom) - (val / denom);
	}
}

//*****************************************************************************
// �t�@�W�[�����o�[�V�b�v��`�^
// ���@���Ffloat val(�Q�l�ɂ��鐔�l), float x0(�͈͂̍ŏ��l), float x1(�͈͂̍ő�l)
//		   float x2(), float x3()
// �߂�l�Ffloat�^�@0.0�`1.0�̐��l
//*****************************************************************************
float FuzzyTrapezoid(float val, float x0, float x1, float x2, float x3)
{
	if (val <= x0)
	{
		return 0;
	}
	else if ((val >= x1) && (val <= x2))
	{
		return 1;
	}
	else if ((val > x0) && (val < x1))
	{
		float denom = x1 - x0;
		return (val / denom) - (x0 / denom);
	}
	else
	{
		float denom = x3 - x2;
		return (x3 / denom) - (val / denom);
	}
}

//*****************************************************************************
//  �t�@�W�[AND���Z�q
//
//
//*****************************************************************************
float And(float a, float b)
{
	return min(a, b);
}

//*****************************************************************************
// �t�@�W�[OR���Z�q
//
//
//*****************************************************************************

float Or(float a, float b)
{
	return max(a, b);
}

//*****************************************************************************
// �t�@�W�[Not���Z�q
//
//
//*****************************************************************************
float Not(float a, float b)
{
	return 1.0f - a;
}
