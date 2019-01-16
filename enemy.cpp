//=============================================================================
//
// �v���C���[���� [enemy.cpp]
// Author : GP11A341_22_�c�����z
//
//=============================================================================
#include "enemy.h"
#include "input.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ENEMY_CAR		"data/MODEL/model_body.x"							// �ǂݍ��ރ��f����
#define	TEXTURE_FILENAME ("data/TEXTURE/field003.jpg")							// �ǂݍ��ރ��f����
#define	VALUE_MOVE		(5.0f)											// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)								// ��]��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9	D3DTexture;		// �e�N�X�`���ւ̃|�C���^
static LPD3DXMESH			D3DMesh;		// ���b�V�����ւ̃|�C���^
static LPD3DXBUFFER			D3DXBuffMat;	// �}�e���A�����ւ̃|�C���^
static DWORD				NumMat;			// �}�e���A�����̐�


static int					g_shadownum;
static D3DXCOLOR			g_shadowcolor;			
static D3DXMATRIX			g_mtxWorld;				// ���[���h�}�g���b�N�X

ENEMY				enemy[ENEMY_MAX];
//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		enemy[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemy[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemy[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		enemy[i].use = true;
		enemy[i].life = 100;
	}

	D3DTexture = NULL;
	D3DMesh = NULL;
	D3DXBuffMat = NULL;
	NumMat = 0;

	// X�t�@�C���̓ǂݍ���
	if(FAILED(D3DXLoadMeshFromX(ENEMY_CAR,				// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
								D3DXMESH_SYSTEMMEM,		// ���b�V���̍쐬�I�v�V�������w��
								pDevice,				// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
								NULL,					// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
								&D3DXBuffMat,	// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^�@�e�N�X�`����J���[���
								NULL,					// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
								&NumMat,		// D3DXMATERIAL�\���̂̐�	�o�^����Ă�}�e���A�����
								&D3DMesh)))	// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X�@���_���̃f�[�^
	{
		return E_FAIL;
	}

#if 0
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_FILENAME,		// �t�@�C���̖��O
								&D3DTexture);	// �ǂݍ��ރ������[
#endif

	//g_shadownum = CreateShadow(enemy[i].pos, 25.0f, 25.0f);
	//g_shadowcolor = D3DXCOLOR(1.5f,1.5f,1.5f,1.5f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	if(D3DTexture != NULL)
	{// �e�N�X�`���̊J��
		D3DTexture->Release();
		D3DTexture = NULL;
	}

	if(D3DMesh != NULL)
	{// ���b�V���̊J��
		D3DMesh->Release();
		D3DMesh = NULL;
	}

	if(D3DXBuffMat != NULL)
	{// �}�e���A���̊J��
		D3DXBuffMat->Release();
		D3DXBuffMat = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	
	//SetPositionShadow(g_shadownum, enemy[i].pos);
	//SetColorShadow(g_shadownum, g_shadowcolor);

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].use == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, enemy[i].scl.x, enemy[i].scl.y, enemy[i].scl.z);
			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, enemy[i].rot.y, enemy[i].rot.x, enemy[i].rot.z);
			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, enemy[i].pos.x, enemy[i].pos.y, enemy[i].pos.z);
			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

			// ���݂̃}�e���A�����擾�@�i���ɖ߂����߂̃o�b�N�A�b�v�j
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)D3DXBuffMat->GetBufferPointer();

			// �}�e���A���̐����̕\�����K�v�Ȃ���FOR�����g�p
			for (int nCntMat = 0; nCntMat < (int)NumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, D3DTexture);

				// �`��
				D3DMesh->DrawSubset(nCntMat);
			}

			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

ENEMY *GetEnemy(int index)
{
	return &enemy[index];
}

void EnemyDamageManager(void)
{
	
}