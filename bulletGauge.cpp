//=============================================================================
//
// �`���[�g���A������ [Tutorial.cpp]
// Author : GP11A_341_22_�c�����z GP11A341_22_�c�����z
//
//=============================================================================
#include "main.h"
#include "tutorial.h"
#include "input.h"
#include "field.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

enum {
	TUTORIAL001,
	TUTORIAL002,
	TUTORIAL003
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTutorial(void);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9			D3DTextureTutorial[TEXTURE_MAX];	// �e�N�X�`���ւ̃|�C���^
static VERTEX_2D			vertexWk[NUM_VERTEX];				// ���_���i�[���[�N

static int					TextureNum;							// 

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTutorial(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
			TEXTURE_TUTORIAL1,						// �t�@�C���̖��O
			&D3DTextureTutorial[TUTORIAL001]);		// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
			TEXTURE_TUTORIAL2,						// �t�@�C���̖��O
			&D3DTextureTutorial[TUTORIAL002]);		// �ǂݍ��ރ������[
		
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
			TEXTURE_TUTORIAL3,						// �t�@�C���̖��O
			&D3DTextureTutorial[TUTORIAL003]);		// �ǂݍ��ރ������[

	}

	TextureNum = TUTORIAL001;

	// ���_���̍쐬
	MakeVertexTutorial();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTutorial(void)
{
	if (D3DTextureTutorial[TextureNum] != NULL)
	{	// �e�N�X�`���̊J��
		D3DTextureTutorial[TextureNum]->Release();
		D3DTextureTutorial[TextureNum] = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutorial(void)
{
	if (GetKeyboardTrigger(DIK_M) && TextureNum < TUTORIAL_MAX)
	{
		TextureNum++;	// 
	}
	else if(TextureNum == TUTORIAL_MAX)
	{
		//SetMakeField();
		SetStage(START);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTutorial(void)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//// ���_�t�H�[�}�b�g�̐ݒ�
	//pDevice->SetFVF(FVF_VERTEX_2D);

	//// �e�N�X�`���̐ݒ�
	//pDevice->SetTexture( 0, D3DTextureTutorial[TextureNum] );

	//// �|���S���̕`��
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_TUTORIAL, vertexWk, sizeof(VERTEX_2D));

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	vertexWk[0].vtx = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y, 0.0f);
	vertexWk[1].vtx = D3DXVECTOR3(TUTORIAL_POS_X + TEXTURE_TUTORIAL_SIZE_X, TUTORIAL_POS_Y, 0.0f);
	vertexWk[2].vtx = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y + TEXTURE_TUTORIAL_SIZE_Y, 0.0f);
	vertexWk[3].vtx = D3DXVECTOR3(TUTORIAL_POS_X + TEXTURE_TUTORIAL_SIZE_X, TUTORIAL_POS_Y + TEXTURE_TUTORIAL_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWk[0].rhw =
	vertexWk[1].rhw =
	vertexWk[2].rhw =
	vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureTutorial1(void)
{
	// �A�j���[�V�������Ȃ��e�N�X�`�����W�̐ݒ�
	int x = NULL;
	int y = NULL;
	float sizeX = 1.0f;
	float sizeY = 1.0f;

	vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}
