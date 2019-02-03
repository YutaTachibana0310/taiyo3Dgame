//=============================================================================
//
// �Փ˔��菈�� [checkhit.cpp]
// Author : GP11A_341_22_�c�����z 
//
//=============================================================================
#include "main.h"
#include "checkhit.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "score.h"
#include "result.h"
#include "effect.h"
#include "block.h" 
#include "explosion.h"
#include "field.h"

D3DXVECTOR3				p3;
D3DXVECTOR3				nor;
//=============================================================================
// BB�ɂ�铖���蔻�菈��
// ��]�͍l�����Ȃ�
// �߂�l�F�������Ă���true
//=============================================================================
void CheckHit(void)
{
	int i, j;

	/* �u���b�N�΃o���b�g�̓����蔻�� */
	BLOCK *block = GetBlock(0);	// �u���b�N�̃A�h���X���擾
	for (i = 0; i < BLOCK_MAX; i++, block++)
	{
		if (!block->use) continue;
		for (j = 0; j < BULLET_SET_MAX; j++)
		{
			CheckBlockHitBullet(i, j, block->pos);
		}
	}
	/* �΃v���C���[�̓����蔻�� */
	PLAYER *player = GetPlayer(0);
	for (i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (!player->use) continue;

		// �v���C���[�̃t�B�[�����O����
		if (!CheckFieldInPlayer(i))
		{
			PlayerDamageManager(i);
			player->pos.y -= 5.0f;
		}

		if (HitCheckCornerBlock(player->pos))
		{
			player->pos = player->prevPos;
		}

	}
	
	BULLET *bullet = GetBullet(0);	//�o���b�g�̃A�h���X���擾
	player = GetPlayer(0);
	for (i = 0; i < BULLET_ONESET_MAX; i++)
	{
		// �v���C���[�P�̃o���b�g
		if (bullet[P1].use[i])
		{
			if (CheckHitBC(bullet[P1].pos[i], player[P2].pos,
				bullet[P1].size[j].x, 10.0f))
			{
				player[P2].life += 15.0f;
				if (player[P2].life > 100.0f)
				{
					SetStage(RESULT);
				}
				player[P2].pos += bullet[P1].move[i];	// �ȈՃm�b�N�o�b�N
				bullet[P1].use[i] = false;
				bullet[P1].reflect[i] = false;
				bullet[P1].cntReflect[i] = 2;
			}
		}
		// �v���C���[�Q�̃o���b�g
		if (bullet[P2].use[i])
		{
			if (CheckHitBC(bullet[P2].pos[i], player[P1].pos,
				bullet[P2].size[j].x, 10.0f))
			{
				player[P1].life -= 15.0f;
				if (player[P1].life < 0.0f)
				{
					SetStage(RESULT);
				}
				player[P1].pos += bullet[P2].move[i];	// �ȈՃm�b�N�o�b�N
				bullet[P2].use[i] = false;
				bullet[P2].reflect[i] = false;
				bullet[P2].cntReflect[i] = 2;
			}
		}
	}
}

//=============================================================================
// BB�ɂ�铖���蔻�菈��
// ��]�͍l�����Ȃ�
// �߂�l�F�������Ă���true
//=============================================================================
bool CheckHitBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2)
{
	size1 /= 2.0f;	// ���T�C�Y�ɂ���
	size2 /= 2.0f;	// ����

	if (pos2.x + size2.x > pos1.x - size1.x && pos1.x + size1.x > pos2.x - size2.x &&
		pos2.y + size2.y > pos1.y - size1.y && pos1.y + size1.y > pos2.y - size2.y &&
		pos2.z + size2.z > pos1.z - size1.z && pos1.z + size1.z > pos2.z - size2.z)
	{
		return true;
	}

	return false;
}

//=============================================================================
// BC�ɂ�铖���蔻�菈��
// �T�C�Y�͔��a
// �߂�l�F�������Ă���true
//=============================================================================
bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{
	if ((size1 + size2) * (size1 + size2) >
		(pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y) + (pos1.z - pos2.z) * (pos1.z - pos2.z))
	{
		return true;
	}

	return false;
}

//=============================================================================
// �����ƃ|���S���̓����蔻�菈��
// ���@���F D3DXVECTOR3 p0,p1,p2(�|���S���̊e���_), D3DXVECTOR3 pos0(�n�_)
//			D3DXVECTOR3 pos1(�I�_)
// �߂�l�F bool�^ �������Ă����false, �����łȂ����true
//=============================================================================
bool CheckHitPolygon(D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1)
{
	
	// �|���S���̊O��
	D3DXVECTOR3		vec01 = p1 - p0;
	D3DXVECTOR3		vec02 = p2 - p0;
	D3DXVec3Cross(&nor, &vec01, &vec02);
	D3DXVec3Normalize(&nor, &nor);
	
	// ���ʂƐ����̓���
 	D3DXVECTOR3		vec1 = pos0 - p0;
	D3DXVECTOR3		vec2 = pos1 - p0;
	float dot1 = D3DXVec3Dot(&vec1, &nor);
	float dot2 = D3DXVec3Dot(&vec2, &nor);

	// �|���S���̕\������
	if ((dot1 * dot2) > 0)
	{
		return true;
	}

	// �|���S���Ɛ����̌�_�����߂�
	float d1 = fabsf(D3DXVec3Dot(&nor, &vec1));		// �_�ƃ|���S���Ƃ̋���
	float d2 = fabsf(D3DXVec3Dot(&nor, &vec2));		// �_�ƃ|���S���Ƃ̋���
	float a = d1 / (d1 + d2);						// ������
	D3DXVECTOR3	vec3 = (1 - a) * vec1 + a * vec2;	// ��_�ւ̃x�N�g��
	p3 = p0 + vec3;									// ��_

	// �|���S���̊e�ӂ̃x�N�g��
	D3DXVECTOR3		v1 = p1 - p0;
	D3DXVECTOR3		v2 = p2 - p1;
	D3DXVECTOR3		v3 = p0 - p2;

	// �e���_�ƌ�_�Ƃ̃x�N�g��
	D3DXVECTOR3		v4 = p3 - p1;
	D3DXVECTOR3		v5 = p3 - p2;
	D3DXVECTOR3		v6 = p3 - p0;
	
	// �e�ӂƂ̊O�ςŖ@�������߂�
	D3DXVECTOR3		n1, n2, n3;
	D3DXVec3Cross(&n1, &v1, &v4);
	D3DXVec3Cross(&n2, &v2, &v5);
	D3DXVec3Cross(&n3, &v3, &v6);

	// ���ꂼ��̃x�N�g���̌���
	float dot12, dot23, dot31;

	dot12 = D3DXVec3Dot(&n1, &nor);
	dot23 = D3DXVec3Dot(&n2, &nor);
	dot31 = D3DXVec3Dot(&n3, &nor);

	// ��_�̓��O����
	if (dot12 < 0) return true;
	if (dot23 < 0) return true;
	if (dot31 < 0) return true;

 	return false;
}

//===========================================================================
// �ǂ���̃x�N�g���v�Z����
// ���@���FD3DXVECTOR3 pos(���̈ړ��ʒu)�AD3DXVECTOR3 normal(�|���S���̖@��)
//		   int index(�v���C���[�̃A�h���X�ԍ�)
// �߂�l�FD3DXVECTOR3�^ out
//==========================================================================
D3DXVECTOR3 WallShear(D3DXVECTOR3 pos, D3DXVECTOR3 normal, int index)
{
	PLAYER *player = GetPlayer(index);
	D3DXVECTOR3 normal_n;
	D3DXVECTOR3 frontVec, out;

	frontVec = pos - player->prevPos;
	D3DXVec3Normalize(&normal_n, &normal);
	D3DXVec3Normalize(&out, &(frontVec - D3DXVec3Dot(&frontVec, &normal_n) * normal_n));
	return out;
}


//========================================================================
// ��_�̎擾
// ���@���F�Ȃ�
// �߂�l�FD3DXVECTOR3�^
//========================================================================
D3DXVECTOR3 GetP3(void)
{
	return p3;
}

//========================================================================
// �@���̎擾
// ���@���F�Ȃ�
// �߂�l�FD3DXVECTOR3�^
//========================================================================
D3DXVECTOR3 GetNormal(void)
{
	return nor;
}

//========================================================================
// �I�u�W�F�N�g�̏Փˌ�ʒu�v�Z����
//
//
//========================================================================
//void Reperlling(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, float weight0, float weight1, float speed0, float speed1)
//{
//	float totalWeight = weight0 + weight1;	// ������
//	float refRate = 1.10f;					// ������
//	D3DXVECTOR3 c = pos1 - pos0;			// �Փˎ��x�N�g��
//	float speed = speed0 - speed1;			// �Փˎ��̑��x		
//	float dot;
//	D3DXVECTOR3 vec;
//	D3DXVec3Normalize(&c, &c);
//	dot = D3DXVec3Dot(&speed, &c);
//
//	vec = ((refRate * dot) / totalWeight) * c;
//	
//}

