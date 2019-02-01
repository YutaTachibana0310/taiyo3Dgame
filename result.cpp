//=============================================================================
//
// ���U���g���� [result.cpp]
// Author : GP11A_341_22_�c�����z
//
//=============================================================================
#include "main.h"
#include "result.h"
#include "input.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexResult(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		pD3DTextureResult[RESULT_MAX];			// �e�N�X�`���ւ̃|���S��

VERTEX_2D				vertexWk_RESULT[NUM_VERTEX];		// ���_���i�[���[�N

D3DXVECTOR3				posResult;						// �|���S���̈ړ���
D3DXVECTOR3				rotResult;						// �|���S���̉�]��
static int				TextureNum;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitResult(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	posResult = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotResult = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_CLEAR,						// �t�@�C���̖��O
			&pD3DTextureResult[CLEAR]);			// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAMEOVER,					// �t�@�C���̖��O
			&pD3DTextureResult[GAMEOVER]);		// �ǂݍ��ރ������̃|�C���^

	}

	// ���_���̍쐬
	MakeVertexResult();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResult(void)
{
	if( pD3DTextureResult[TextureNum] != NULL )	//
	{	// �e�N�X�`���̊J��
		 pD3DTextureResult[TextureNum]->Release();
		 pD3DTextureResult[TextureNum] = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult(void)
{
	// �A�j���[�V����
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		SetStage(TITLE);
		InitGame();
	}

	if (IsButtonTriggered(0, BUTTON_A))
	{
		SetStage(TITLE);
		InitGame();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture( 0, pD3DTextureResult[TextureNum] );

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_RESULT, vertexWk_RESULT, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	vertexWk_RESULT[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertexWk_RESULT[1].vtx = D3DXVECTOR3(0.0f+TEXTURE_SAMPLE00_SIZE_X_RESULT, 0.0f, 0.0f);
	vertexWk_RESULT[2].vtx = D3DXVECTOR3(0.0f, 0.0f+TEXTURE_SAMPLE00_SIZE_Y_RESULT, 0.0f);
	vertexWk_RESULT[3].vtx = D3DXVECTOR3(0.0f+TEXTURE_SAMPLE00_SIZE_X_RESULT, 0.0f+TEXTURE_SAMPLE00_SIZE_Y_RESULT, 0.0f);

	// rhw�̐ݒ�
	vertexWk_RESULT[0].rhw =
	vertexWk_RESULT[1].rhw =
	vertexWk_RESULT[2].rhw =
	vertexWk_RESULT[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWk_RESULT[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk_RESULT[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk_RESULT[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk_RESULT[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexWk_RESULT[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk_RESULT[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWk_RESULT[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk_RESULT[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}


void SetTextureResult(int num)
{
	TextureNum = num;
}
