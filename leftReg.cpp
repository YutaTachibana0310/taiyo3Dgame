//=============================================================================
//
// �������f������ [leftReg.cpp]
// Author : GP11A_341_22_�c�����z 
//
//=============================================================================
#include "leftReg.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "debugproc.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	PLAYER_AIRPLANE		"data/MODEL/model_reg.x"	// �ǂݍ��ރ��f����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9	D3DTexture;			// �e�N�X�`���ǂݍ��ݏꏊ
static LPD3DXMESH			D3DXMesh;			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
static LPD3DXBUFFER		D3DXBuffMat;		// ���b�V���̃}�e���A�������i�[
static DWORD				NumMat;				// �������̑���


LEFTREG				leftReg[PLAYER_MAX];
//=============================================================================
// ����������
//=============================================================================
HRESULT InitLeftReg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DTexture = NULL;
	D3DXMesh = NULL;
	D3DXBuffMat = NULL;
	
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		leftReg[i].pos = D3DXVECTOR3(-7.0f, -20.0f, 0.0f);
		leftReg[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(PLAYER_AIRPLANE,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&D3DXBuffMat,
		NULL,
		&NumMat,
		&D3DXMesh)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitLeftReg(void)
{
	if (D3DTexture != NULL)
	{// �e�N�X�`���̊J��
		D3DTexture ->Release();
		D3DTexture = NULL;
	}

	if (D3DXMesh != NULL)
	{// ���b�V���̊J��
		D3DXMesh ->Release();
		D3DXMesh = NULL;
	}

	if (D3DXBuffMat != NULL)
	{// �}�e���A���̊J��
		D3DXBuffMat ->Release();
		D3DXBuffMat = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateLeftReg(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawLeftReg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	D3DXMATERIAL *D3DXMat;
	D3DMATERIAL9 matDef;
	PLAYER *player = GetPlayer(0);

	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (player->use)
		{

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&leftReg[i].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, leftReg[i].rot.y, leftReg[i].rot.x, leftReg[i].rot.z);
			D3DXMatrixMultiply(&leftReg[i].mtxWorld, &leftReg[i].mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, leftReg[i].pos.x, leftReg[i].pos.y, leftReg[i].pos.z);
			D3DXMatrixMultiply(&leftReg[i].mtxWorld, &leftReg[i].mtxWorld, &mtxTranslate);


			D3DXMatrixMultiply(&leftReg[i].mtxWorld, &leftReg[i].mtxWorld, &player->mtxWorld);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &leftReg[i].mtxWorld);


			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			D3DXMat = (D3DXMATERIAL*)D3DXBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)NumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&D3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, D3DTexture);

				// �`��
				D3DXMesh->DrawSubset(nCntMat);
			}

			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}
