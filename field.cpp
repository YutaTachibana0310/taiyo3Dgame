//=============================================================================
//
// �n�ʏ��� [field.cpp]
// Author : GP11A_341_22_�c�����z 
//
//=============================================================================
#include "field.h"
#include "checkhit.h"
#include "explosion.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_FIELD	"data/TEXTURE/field003.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define FIELD_MAX				(1)					// �ő吔
//#define FIELD_BOTTOMUP		(50.0f)				// ��グ����
//#define GAMEFIELD_SIZE_X		(500.0f)
//#define GAMEFIELD_SIZE_Y		(300.0f)
//#define GAMEFIELD_SIZE_Z		(500.0f)					

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice);
//void SetMakeField(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureField = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffField = NULL;	// ���_�o�b�t�@�ւ̃|�C���^


FIELD					fieldWk[FIELD_MAX];			// �t�B�[���h�\����
//=============================================================================
// ����������
//=============================================================================
HRESULT InitField(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); 
	HRESULT hr;

	FIELD *field = &fieldWk[0];

	// �ʒu�A�����̏����ݒ�
	for (int i = 0; i < FIELD_MAX; i++)
	{
		field[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}


	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_FIELD,			// �t�@�C���̖��O
								&D3DTextureField);	// �ǂݍ��ރ������[
	}

	// ���_���̍쐬
	hr = MakeVertexField(pDevice);

	return hr;
}

//=============================================================================
// �I������
//=============================================================================
void UninitField(void)
{
	if(D3DTextureField != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureField->Release();
		D3DTextureField = NULL;
	}

	if(D3DVtxBuffField != NULL)
	{// ���_�o�b�t�@�̊J��
		D3DVtxBuffField->Release();
		D3DVtxBuffField = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateField(void)
{
	

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); 
	D3DXMATRIX mtxRot, mtxTranslate;
	FIELD *field = &fieldWk[0];

	for (int i = 0; i < FIELD_MAX; i++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&field[i].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, field[i].rot.y, field[i].rot.x, field[i].rot.z);
		D3DXMatrixMultiply(&field[i].mtxWorld, &field[i].mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, field[i].pos.x, field[i].pos.y, field[i].pos.z);
		D3DXMatrixMultiply(&field[i].mtxWorld, &field[i].mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &field[i].mtxWorld);

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, D3DVtxBuffField, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, D3DTextureField);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (i * NUM_VERTEX), NUM_POLYGON);
	}

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * FIELD_MAX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&D3DVtxBuffField,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{	//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D			   *pVtx;
		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-FIELD_SIZE_X, FIELD_SIZE_Y, FIELD_SIZE_Z);
		pVtx[1].vtx = D3DXVECTOR3(FIELD_SIZE_X, FIELD_SIZE_Y, FIELD_SIZE_Z);
		pVtx[2].vtx = D3DXVECTOR3(-FIELD_SIZE_X, FIELD_SIZE_Y, -FIELD_SIZE_Z);
		pVtx[3].vtx = D3DXVECTOR3(FIELD_SIZE_X, FIELD_SIZE_Y, -FIELD_SIZE_Z);

		// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuffField->Unlock();

		/* ���_���̐ݒ� */
		//InitMakeVertex();	
	}
	return S_OK;
}

//=============================================================================
// �Ƃ̓����蔻��
// pos0:�n�_�i�ړ��O�j
// pos1:�I�_�i�ړ���j
//=============================================================================
FIELD *GetField(int fno)
{
	return &fieldWk[fno];
}

//=============================================================================
// �ǂƂ̓����蔻��
// pos0:�n�_�i�ړ��O�j
// pos1:�I�_�i�ړ���j
//=============================================================================
bool HitCheckField(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1)
{
	FIELD *field = &fieldWk[0];

	D3DXVECTOR3		pos[NUM_VERTEX]; // ���_���W�̕ۑ�
	bool			ans;
	VERTEX_3D	    *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	D3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < FIELD_MAX; i++, pVtx += 4)
	{
		// ���_���W�̐ݒ�
		pos[0] = pVtx[0].vtx;
		pos[1] = pVtx[1].vtx;
		pos[2] = pVtx[2].vtx;
		pos[3] = pVtx[3].vtx;

		// �������|���S���Ɛ����̓����蔻��
		ans = CheckHitPolygon(pos[0], pos[2], pos[3], pos0, pos1);
		if (!ans)
		{
			break;
		}
		// �E�㑤�|���S���Ɛ����̓����蔻��
		ans = CheckHitPolygon(pos[0], pos[3], pos[1], pos0, pos1);
		if (!ans)
		{
			break;
		}
	}

	// ���_�f�[�^���A�����b�N����
	D3DVtxBuffField->Unlock();

	return ans;
}

////============================================================================
//// �Q�[���t�B�[���h�̍쐬
////============================================================================
//void SetMakeField(void)
//{
//	FIELD *field = &fieldWk[0];
//
//	// BOX�̒��_���̐ݒ�
//	{
//		//���_�o�b�t�@�̒��g�𖄂߂�
//		VERTEX_3D			   *pVtx;
//		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
//		D3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);
//
//		// ���
//		{
//			// ���_���W�̐ݒ�
//			pVtx[0].vtx = D3DXVECTOR3(GAMEFIELD_SIZE_X, GAMEFIELD_SIZE_Y + 50.0f, GAMEFIELD_SIZE_Z);
//			pVtx[1].vtx = D3DXVECTOR3(-GAMEFIELD_SIZE_X, GAMEFIELD_SIZE_Y + 50.0f, GAMEFIELD_SIZE_Z);
//			pVtx[2].vtx = D3DXVECTOR3(GAMEFIELD_SIZE_X, GAMEFIELD_SIZE_Y + 50.0f, -GAMEFIELD_SIZE_Z);
//			pVtx[3].vtx = D3DXVECTOR3(-GAMEFIELD_SIZE_X, GAMEFIELD_SIZE_Y + 50.0f, -GAMEFIELD_SIZE_Z);
//
//			// �@���x�N�g���̐ݒ�
//			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//
//			// ���ˌ��̐ݒ�
//			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//			// �e�N�X�`�����W�̐ݒ�
//			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//		}
//
//		// ���
//		{
//			// ���_���W�̐ݒ�
//			pVtx[4].vtx = D3DXVECTOR3(-GAMEFIELD_SIZE_X, -GAMEFIELD_SIZE_Y + 50.0f, GAMEFIELD_SIZE_Z);
//			pVtx[5].vtx = D3DXVECTOR3(GAMEFIELD_SIZE_X, -GAMEFIELD_SIZE_Y + 50.0f, GAMEFIELD_SIZE_Z);
//			pVtx[6].vtx = D3DXVECTOR3(-GAMEFIELD_SIZE_X, -GAMEFIELD_SIZE_Y + 50.0f, -GAMEFIELD_SIZE_Z);
//			pVtx[7].vtx = D3DXVECTOR3(GAMEFIELD_SIZE_X, -GAMEFIELD_SIZE_Y + 50.0f, -GAMEFIELD_SIZE_Z);
//
//			// �@���x�N�g���̐ݒ�
//			pVtx[4].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
//			pVtx[5].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
//			pVtx[6].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
//			pVtx[7].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
//
//			// ���ˌ��̐ݒ�
//			pVtx[4].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[5].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[6].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[7].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//			// �e�N�X�`�����W�̐ݒ�
//			pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
//			pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
//			pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
//			pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);
//		}
//
//		// ����
//		{
//			// ���_���W�̐ݒ�
//			pVtx[8] = pVtx[3];
//			pVtx[9] = pVtx[1];
//			pVtx[10] = pVtx[6];
//			pVtx[11] = pVtx[4];
//
//			// �@���x�N�g���̐ݒ�
//			pVtx[8].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
//			pVtx[9].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
//			pVtx[10].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
//			pVtx[11].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
//
//			// ���ˌ��̐ݒ�
//			pVtx[8].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[9].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[10].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[11].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//			// �e�N�X�`�����W�̐ݒ�
//			pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
//			pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
//			pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
//			pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);
//		}
//
//		// �E��
//		{
//			// ���_���W�̐ݒ�
//			pVtx[12] = pVtx[0];
//			pVtx[13] = pVtx[2];
//			pVtx[14] = pVtx[5];
//			pVtx[15] = pVtx[7];
//
//			// �@���x�N�g���̐ݒ�
//			pVtx[12].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
//			pVtx[13].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
//			pVtx[14].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
//			pVtx[15].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
//
//			// ���ˌ��̐ݒ�
//			pVtx[12].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[13].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[14].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[15].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//			// �e�N�X�`�����W�̐ݒ�
//			pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
//			pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
//			pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
//			pVtx[15].tex = D3DXVECTOR2(1.0f, 1.0f);
//		}
//
//		// ����
//		{
//			// ���_���W�̐ݒ�
//			pVtx[16] = pVtx[2];
//			pVtx[17] = pVtx[3];
//			pVtx[18] = pVtx[7];
//			pVtx[19] = pVtx[6];
//
//			// �@���x�N�g���̐ݒ�
//			pVtx[16].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
//			pVtx[17].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
//			pVtx[18].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
//			pVtx[19].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
//
//			// ���ˌ��̐ݒ�
//			pVtx[16].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[17].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[18].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[19].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//			// �e�N�X�`�����W�̐ݒ�
//			pVtx[16].tex = D3DXVECTOR2(0.0f, 0.0f);
//			pVtx[17].tex = D3DXVECTOR2(1.0f, 0.0f);
//			pVtx[18].tex = D3DXVECTOR2(0.0f, 1.0f);
//			pVtx[19].tex = D3DXVECTOR2(1.0f, 1.0f);
//		}
//
//		// �w��
//		{
//			// ���_���W�̐ݒ�
//			pVtx[20] = pVtx[5];
//			pVtx[21] = pVtx[4];
//			pVtx[22] = pVtx[0];
//			pVtx[23] = pVtx[1];
//
//			// �@���x�N�g���̐ݒ�
//			pVtx[20].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
//			pVtx[21].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
//			pVtx[22].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
//			pVtx[23].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
//
//			// ���ˌ��̐ݒ�
//			pVtx[20].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[21].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[22].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[23].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//			// �e�N�X�`�����W�̐ݒ�
//			pVtx[20].tex = D3DXVECTOR2(0.0f, 0.0f);
//			pVtx[21].tex = D3DXVECTOR2(1.0f, 0.0f);
//			pVtx[22].tex = D3DXVECTOR2(0.0f, 1.0f);
//			pVtx[23].tex = D3DXVECTOR2(1.0f, 1.0f);
//		}
//
//
//
//		// ���_�f�[�^���A�����b�N����
//		D3DVtxBuffField->Unlock();
//	}
//
//}
////============================================================================
//// �{�b�N�X�̒��_�@�쐬
////============================================================================
//void InitMakeVertex(void)
//{
//	FIELD *field = &fieldWk[0];
//
//	// BOX�̒��_���̐ݒ�
//	{
//		//���_�o�b�t�@�̒��g�𖄂߂�
//		VERTEX_3D			   *pVtx;
//		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
//		D3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);
//
//		// ���
//		{
//			// ���_���W�̐ݒ�
//			pVtx[0].vtx = D3DXVECTOR3(FIELD_SIZE_X, FIELD_SIZE_Y + 50.0f, FIELD_SIZE_Z);
//			pVtx[1].vtx = D3DXVECTOR3(-FIELD_SIZE_X, FIELD_SIZE_Y + 50.0f, FIELD_SIZE_Z);
//			pVtx[2].vtx = D3DXVECTOR3(FIELD_SIZE_X, FIELD_SIZE_Y + 50.0f, -FIELD_SIZE_Z);
//			pVtx[3].vtx = D3DXVECTOR3(-FIELD_SIZE_X, FIELD_SIZE_Y + 50.0f, -FIELD_SIZE_Z);
//
//			// �@���x�N�g���̐ݒ�
//			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//
//			// ���ˌ��̐ݒ�
//			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//			// �e�N�X�`�����W�̐ݒ�
//			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//		}
//
//		// ���
//		{
//			// ���_���W�̐ݒ�
//			pVtx[4].vtx = D3DXVECTOR3(-FIELD_SIZE_X, -FIELD_SIZE_Y + 50.0f, FIELD_SIZE_Z);
//			pVtx[5].vtx = D3DXVECTOR3(FIELD_SIZE_X, -FIELD_SIZE_Y + 50.0f, FIELD_SIZE_Z);
//			pVtx[6].vtx = D3DXVECTOR3(-FIELD_SIZE_X, -FIELD_SIZE_Y + 50.0f, -FIELD_SIZE_Z);
//			pVtx[7].vtx = D3DXVECTOR3(FIELD_SIZE_X, -FIELD_SIZE_Y + 50.0f, -FIELD_SIZE_Z);
//
//			// �@���x�N�g���̐ݒ�
//			pVtx[4].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
//			pVtx[5].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
//			pVtx[6].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
//			pVtx[7].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
//
//			// ���ˌ��̐ݒ�
//			pVtx[4].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[5].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[6].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[7].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//			// �e�N�X�`�����W�̐ݒ�
//			pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
//			pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
//			pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
//			pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);
//		}
//
//		// ����
//		{
//			// ���_���W�̐ݒ�
//			pVtx[8] = pVtx[3];
//			pVtx[9] = pVtx[1];
//			pVtx[10] = pVtx[6];
//			pVtx[11] = pVtx[4];
//
//			// �@���x�N�g���̐ݒ�
//			pVtx[8].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
//			pVtx[9].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
//			pVtx[10].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
//			pVtx[11].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
//
//			// ���ˌ��̐ݒ�
//			pVtx[8].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[9].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[10].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[11].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//			// �e�N�X�`�����W�̐ݒ�
//			pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
//			pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
//			pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
//			pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);
//		}
//
//		// �E��
//		{
//			// ���_���W�̐ݒ�
//			pVtx[12] = pVtx[0];
//			pVtx[13] = pVtx[2];
//			pVtx[14] = pVtx[5];
//			pVtx[15] = pVtx[7];
//
//			// �@���x�N�g���̐ݒ�
//			pVtx[12].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
//			pVtx[13].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
//			pVtx[14].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
//			pVtx[15].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
//
//			// ���ˌ��̐ݒ�
//			pVtx[12].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[13].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[14].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[15].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//			// �e�N�X�`�����W�̐ݒ�
//			pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
//			pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
//			pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
//			pVtx[15].tex = D3DXVECTOR2(1.0f, 1.0f);
//		}
//
//		// ����
//		{
//			// ���_���W�̐ݒ�
//			pVtx[16] = pVtx[2];
//			pVtx[17] = pVtx[3];
//			pVtx[18] = pVtx[7];
//			pVtx[19] = pVtx[6];
//
//			// �@���x�N�g���̐ݒ�
//			pVtx[16].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
//			pVtx[17].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
//			pVtx[18].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
//			pVtx[19].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
//
//			// ���ˌ��̐ݒ�
//			pVtx[16].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[17].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[18].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[19].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//			// �e�N�X�`�����W�̐ݒ�
//			pVtx[16].tex = D3DXVECTOR2(0.0f, 0.0f);
//			pVtx[17].tex = D3DXVECTOR2(1.0f, 0.0f);
//			pVtx[18].tex = D3DXVECTOR2(0.0f, 1.0f);
//			pVtx[19].tex = D3DXVECTOR2(1.0f, 1.0f);
//		}
//
//		// �w��
//		{
//			// ���_���W�̐ݒ�
//			pVtx[20] = pVtx[5];
//			pVtx[21] = pVtx[4];
//			pVtx[22] = pVtx[0];
//			pVtx[23] = pVtx[1];
//
//			// �@���x�N�g���̐ݒ�
//			pVtx[20].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
//			pVtx[21].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
//			pVtx[22].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
//			pVtx[23].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
//
//			// ���ˌ��̐ݒ�
//			pVtx[20].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[21].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[22].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[23].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//			// �e�N�X�`�����W�̐ݒ�
//			pVtx[20].tex = D3DXVECTOR2(0.0f, 0.0f);
//			pVtx[21].tex = D3DXVECTOR2(1.0f, 0.0f);
//			pVtx[22].tex = D3DXVECTOR2(0.0f, 1.0f);
//			pVtx[23].tex = D3DXVECTOR2(1.0f, 1.0f);
//		}
//
//		// ���_�f�[�^���A�����b�N����
//		D3DVtxBuffField->Unlock();
//	}
//
//}
