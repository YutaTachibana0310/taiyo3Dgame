//=============================================================================
//
// �v���C���[���� [child.cpp]
// Author : GP11A341_22_�c�����z
//
//=============================================================================
#include "child.h"
#include "input.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	CHILD_MODEL01		"data/MODEL/child01.x"				// �ǂݍ��ރ��f����
#define	CHILD_MODEL02		"data/MODEL/child02.x"				// �ǂݍ��ރ��f����

#define	TEXTURE_FILENAME ("data/TEXTURE/field003.jpg")		// �ǂݍ��ރ��f����
#define	VALUE_MOVE		(5.0f)								// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)					// ��]��

enum {
	MODEL_TYPE001,
	MODEL_TYPE002
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9	D3DTexture;		// �e�N�X�`���ւ̃|�C���^
static LPD3DXMESH			D3DMesh[CHILD_SET_MAX];		// ���b�V�����ւ̃|�C���^
static LPD3DXBUFFER			D3DXBuffMat[CHILD_SET_MAX];	// �}�e���A�����ւ̃|�C���^
static DWORD				NumMat[CHILD_SET_MAX];			// �}�e���A�����̐�


static int					g_shadownum;
static D3DXCOLOR			g_shadowcolor;			
static D3DXMATRIX			g_mtxWorld;				// ���[���h�}�g���b�N�X

CHILD						childWk[CHILD_SET_MAX];
//=============================================================================
// ����������
//=============================================================================
HRESULT InitChild(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CHILD *child = &childWk[0];

	for (int i = 0; i < CHILD_SET_MAX; i++)
	{
		D3DMesh[i] = NULL;
		D3DXBuffMat[i] = NULL;
		NumMat[i] = 0;

		for (int j = 0; j < CHILD_ONESET_MAX; j++)
		{
			// �ʒu�E��]�E�X�P�[���̏����ݒ�
			child[i].pos[j] = D3DXVECTOR3(-300.0f + (10.0f * j), 10.0f, 50.0f * i);
			child[i].rot[j] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			child[i].scl[j] = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
			child[i].use[j] = true;
			child[i].life[j] = 100;
		}
	}

	D3DTexture = NULL;

	// X�t�@�C���̓ǂݍ���
	if(FAILED(D3DXLoadMeshFromX(CHILD_MODEL01,				// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
								D3DXMESH_SYSTEMMEM,		// ���b�V���̍쐬�I�v�V�������w��
								pDevice,				// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
								NULL,					// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
								&D3DXBuffMat[MODEL_TYPE001],	// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^�@�e�N�X�`����J���[���
								NULL,					// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
								&NumMat[MODEL_TYPE001],		// D3DXMATERIAL�\���̂̐�	�o�^����Ă�}�e���A�����
								&D3DMesh[MODEL_TYPE001])))	// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X�@���_���̃f�[�^
	{
		return E_FAIL;
	}

	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(CHILD_MODEL02,				// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
		D3DXMESH_SYSTEMMEM,		// ���b�V���̍쐬�I�v�V�������w��
		pDevice,				// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
		NULL,					// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		&D3DXBuffMat[MODEL_TYPE002],	// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^�@�e�N�X�`����J���[���
		NULL,					// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
		&NumMat[MODEL_TYPE002],		// D3DXMATERIAL�\���̂̐�	�o�^����Ă�}�e���A�����
		&D3DMesh[MODEL_TYPE002])))	// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X�@���_���̃f�[�^
	{
		return E_FAIL;
	}

#if 0
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_FILENAME,		// �t�@�C���̖��O
								&D3DTexture);	// �ǂݍ��ރ������[
#endif

	//g_shadownum = CreateShadow(child[i].pos[j], 25.0f, 25.0f);
	//g_shadowcolor = D3DXCOLOR(1.5f,1.5f,1.5f,1.5f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitChild(void)
{
	if (D3DTexture != NULL)
	{// �e�N�X�`���̊J��
		D3DTexture->Release();
		D3DTexture = NULL;
	}

	for (int i = 0; i < CHILD_SET_MAX; i++)
	{
		if (D3DMesh != NULL)
		{// ���b�V���̊J��
			D3DMesh[i]->Release();
			D3DMesh[i] = NULL;
		}

		if (D3DXBuffMat != NULL)
		{// �}�e���A���̊J��
			D3DXBuffMat[i]->Release();
			D3DXBuffMat[i] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateChild(void)
{
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawChild(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	CHILD *child = &childWk[0];

	for (int i = 0; i < CHILD_SET_MAX; i++)
	{
		for (int j = 0; j < CHILD_ONESET_MAX; j++)
		{
			if (child[i].use[j] == true)
			{
				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_mtxWorld);

				// �X�P�[���𔽉f
				D3DXMatrixScaling(&mtxScl, child[i].scl[j].x, child[i].scl[j].y, child[i].scl[j].z);
				D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, child[i].rot[j].y, child[i].rot[j].x, child[i].rot[j].z);
				D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

				// �ړ��𔽉f
				D3DXMatrixTranslation(&mtxTranslate, child[i].pos[j].x, child[i].pos[j].y, child[i].pos[j].z);
				D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTranslate);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

				// ���݂̃}�e���A�����擾�@�i���ɖ߂����߂̃o�b�N�A�b�v�j
				pDevice->GetMaterial(&matDef);

				// �}�e���A�����ɑ΂���|�C���^���擾
				pD3DXMat = (D3DXMATERIAL*)D3DXBuffMat[i]->GetBufferPointer();

				// �}�e���A���̐����̕\�����K�v�Ȃ���FOR�����g�p
				for (int nCntMat = 0; nCntMat < (int)NumMat[i]; nCntMat++)
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, D3DTexture);

					// �`��
					D3DMesh[i]->DrawSubset(nCntMat);
				}

				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}

CHILD *GetChild(int index)
{
	return &childWk[index];
}

void ChildDamageManager(void)
{
	
}