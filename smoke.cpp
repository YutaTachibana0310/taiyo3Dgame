//=============================================================================
//
// �G�t�F�N�g���� [smoke.cpp]
// Author : GP11A_341_22_�c�����z GP11A341_22_�c�����z
//
//=============================================================================
#include "smoke.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "debugproc.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SMOKE		"data/TEXTURE/shadow.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	SMOKE_SIZE_X		(5.0f)						// �r���{�[�h�̕�
#define	SMOKE_SIZE_Y		(5.0f)						// �r���{�[�h�̍���
#define SMOKE_MAX			(35)						// ���G�t�F�N�g�̍ő吔
#define DEL_TIME			(60)						// �G�t�F�N�g�̎���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexSmoke(LPDIRECT3DDEVICE9 pDevice);
void SetVertexSmoke(int Index, float fSizeX, float fSizeY);
void SetDiffuseSmoke(int Index, float val);
void MoveSmoke(int mno);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureSmoke = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffSmoke = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

float					s_curveAngle[SMOKE_MAX];	// Sin�J�[�u�̊p�x
static int				cnt_frame;					// �t���[����
static float			dif_mi[SMOKE_MAX];			// ���ߒl
SMOKE					smokeWk[SMOKE_MAX];			// SMOKE�\���̗p�ϐ�

//=============================================================================
// ����������
//=============================================================================
HRESULT InitSmoke(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SMOKE *smoke = &smokeWk[0];

	// ���_���̍쐬
	MakeVertexSmoke(pDevice);

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
			TEXTURE_SMOKE,					// �t�@�C���̖��O
			&D3DTextureSmoke);			// �ǂݍ��ރ������[
	}

	for (int i = 0; i < SMOKE_MAX; i++)
	{
		smoke[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		smoke[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		smoke[i].time = DEL_TIME;
		smoke[i].Alpha = 0.0f;
		dif_mi[i] = INIT_ALPHA;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSmoke(void)
{
	if (D3DTextureSmoke != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureSmoke->Release();
		D3DTextureSmoke = NULL;
	}

	if (D3DVtxBuffSmoke != NULL)
	{// ���_�o�b�t�@�̊J��
		D3DVtxBuffSmoke->Release();
		D3DVtxBuffSmoke = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSmoke(void)
{
	SMOKE *smoke = &smokeWk[0];

	for (int i = 0; i < SMOKE_MAX; i++)
	{
		if (smoke[i].use == true)
		{
			MoveSmoke(i);			// ���G�t�F�N�g�̓���

				// �G�t�F�N�g�̊g��
			if (smoke[i].time % 5 == 0)
			{
				smoke[i].scl += D3DXVECTOR3(0.1f, 0.1f, 0.1f);
			}

			dif_mi[i] -= 0.01f;		// ���߂̒l
			smoke[i].time--;		// �������Ԃ��f�N�������g

			// ���Ŏ��ԂɂȂ��������
			if (smoke[i].time % DEL_TIME == 0)
			{
				dif_mi[i] = INIT_ALPHA;
				smoke[i].use = false;
				smoke[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
				s_curveAngle[i] = 0.0f;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSmoke(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;
	SMOKE *smoke = &smokeWk[0];

	// Z��r�Ȃ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 128);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	for (int i = 0; i < SMOKE_MAX; i++)
	{
		SetDiffuseSmoke(i, dif_mi[i]);

		// ���C���e�B���O�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// �ʏ�u�����h
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		if (smoke[i].use)
		{
			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&smoke[i].mtxWorld);

			// �|���S���𐳖ʂɌ�����
			smoke[i].mtxWorld._11 = mtxView._11;
			smoke[i].mtxWorld._12 = mtxView._21;
			smoke[i].mtxWorld._13 = mtxView._31;
			smoke[i].mtxWorld._21 = mtxView._12;
			smoke[i].mtxWorld._22 = mtxView._22;
			smoke[i].mtxWorld._23 = mtxView._32;
			smoke[i].mtxWorld._31 = mtxView._13;
			smoke[i].mtxWorld._32 = mtxView._23;
			smoke[i].mtxWorld._33 = mtxView._33;

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, smoke[i].scl.x,
				smoke[i].scl.y,
				smoke[i].scl.z);
			D3DXMatrixMultiply(&smoke[i].mtxWorld,
				&smoke[i].mtxWorld, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, smoke[i].pos.x,
				smoke[i].pos.y,
				smoke[i].pos.z);
			D3DXMatrixMultiply(&smoke[i].mtxWorld,
				&smoke[i].mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &smoke[i].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, D3DVtxBuffSmoke, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, D3DTextureSmoke);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (i * NUM_VERTEX), NUM_POLYGON);
		}
	}

	// ���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// �ʏ�u�����h
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			// ���� = �]����(SRC) + �]����(DEST)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_BOTHINVSRCALPHA);

	// Z��r����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexSmoke(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * SMOKE_MAX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&D3DVtxBuffSmoke,			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuffSmoke->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < SMOKE_MAX; i++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			SetVertexSmoke(i, SMOKE_SIZE_X, SMOKE_SIZE_Y);

			// �@���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		}
		// ���_�f�[�^���A�����b�N����
		D3DVtxBuffSmoke->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexSmoke(int Index, float fSizeX, float fSizeY)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuffSmoke->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (Index * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuffSmoke->Unlock();
	}
}

//============================================================================
// ���G�t�F�N�g�̓��ߏ���
//============================================================================
void SetDiffuseSmoke(int Index, float val)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuffSmoke->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (Index * 4);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse =
			pVtx[1].diffuse =
			pVtx[2].diffuse =
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, val);

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuffSmoke->Unlock();
	}
}

//==========================================================================
// ���G�t�F�N�g�̐ݒu
// ���@���FD3DXVECTOR3 pos(�ʒu), D3DXVECTOR3 rot(��]), float Dest(����)
// �߂�l�Fbool�^�@�g�p���Ȃ� false, ���g�p�Ȃ�true�@
//==========================================================================
bool SetSmoke(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Dest)
{
	SMOKE *smoke = &smokeWk[0];

	for (int i = 0; i < SMOKE_MAX; i++)
	{
		if (!smoke[i].use)
		{
			smoke[i].use = true;	// �g�p��
			smoke[i].pos.x = pos.x + sinf(rot.y) * Dest;
			smoke[i].pos.z = pos.z + cosf(rot.y) * Dest;
			smoke[i].pos.y = pos.y;

			SetVertexSmoke(i, 5.0f, 5.0f);

			return true;
		}
	}

	return false;
}

//==========================================================================
// ���G�t�F�N�g�̂��߂��̐���
// ���@���F int mno(���G�t�F�N�g�̃A�h���X�ԍ�)
// �߂�l�F �Ȃ�
//==========================================================================
void MoveSmoke(int mno)
{
	SMOKE *smoke = &smokeWk[mno];	// �A�h���X�̎擾

	// ��炬�̒l�������_���Ŏw��
	s_curveAngle[mno] = (float)(rand() % 101);

	// ��炬�̔��f
	smoke[mno].pos.x += sinf(s_curveAngle[mno]);
	smoke[mno].pos.y += 0.2f;
	smoke[mno].pos.z += cosf(s_curveAngle[mno]);

}

