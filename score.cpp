//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author�FGP11A341_22_�c�����z 
//=============================================================================
#include "main.h"
#include "score.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexScore(void);
void SetTextureScore(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureScore = NULL;		// �e�N�X�`���ւ̃|���S��
VERTEX_2D				VertexWkScore[SCORE_DIGIT][NUM_VERTEX];	// ���_���i�[���[�N

D3DXVECTOR3				PosScore;					// �|���S���̈ړ���

int						Score;						// �X�R�A

//=============================================================================
// ����������
//=============================================================================
HRESULT InitScore(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_SCORE,				// �t�@�C���̖��O
			&g_pD3DTextureScore);				// �ǂݍ��ރ������̃|�C���^
	}
	for (int i = 0; i < SCORE_DIGIT; i++)
	{

		PosScore = D3DXVECTOR3((float)SCORE_POS_X - 16.0f, (float)SCORE_POS_Y, 0.0f);
		Score = 0;

		// ���_���̍쐬
		MakeVertexScore();
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	if( g_pD3DTextureScore != NULL )
	{	// �e�N�X�`���̊J��
		g_pD3DTextureScore->Release();
		g_pD3DTextureScore = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{
	// ���t���[�����s����鏈�����L�q����
	SetTextureScore();

	if (Score == 100) 
	{
		SetStage(RESULT);
	}

	if (GetKeyboardPress(DIK_L))
	{
		Score += 1;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int i, DigitMax = 1;


	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture( 0, g_pD3DTextureScore );
	// �X�R�A
	for (int j = 1; j < SCORE_DIGIT; j++, DigitMax++)
	{
		if (Score < pow(10, j))
		{
			break;
		}
	}

	for( i = 0; i < DigitMax; i++ )
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_SCORE, VertexWkScore[i], sizeof(VERTEX_2D));
	}

	// ���e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexScore(void)
{
	int i;
	float haba_x = 16.0f;	// �����̉���
	
	// ��������������
	for( i = 0; i < SCORE_DIGIT; i++ )
	{
		// ���_���W�̐ݒ�
		VertexWkScore[i][0].vtx.x = -haba_x * i + PosScore.x;
		VertexWkScore[i][0].vtx.y = PosScore.y;
		VertexWkScore[i][0].vtx.z = 0.0f;
		VertexWkScore[i][1].vtx.x = -haba_x * i + PosScore.x + TEXTURE_SCORE00_SIZE_X;
		VertexWkScore[i][1].vtx.y = PosScore.y;
		VertexWkScore[i][1].vtx.z = 0.0f;
		VertexWkScore[i][2].vtx.x = -haba_x * i + PosScore.x;
		VertexWkScore[i][2].vtx.y = PosScore.y + TEXTURE_SCORE00_SIZE_Y;
		VertexWkScore[i][2].vtx.z = 0.0f;
		VertexWkScore[i][3].vtx.x = -haba_x * i + PosScore.x + TEXTURE_SCORE00_SIZE_X;
		VertexWkScore[i][3].vtx.y = PosScore.y + TEXTURE_SCORE00_SIZE_Y;
		VertexWkScore[i][3].vtx.z = 0.0f;

		// rhw�̐ݒ�
		VertexWkScore[i][0].rhw =
		VertexWkScore[i][1].rhw =
		VertexWkScore[i][2].rhw =
		VertexWkScore[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		VertexWkScore[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkScore[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkScore[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkScore[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		VertexWkScore[i][0].tex = D3DXVECTOR2( 0.0f, 0.0f );
		VertexWkScore[i][1].tex = D3DXVECTOR2( 1.0f, 0.0f );
		VertexWkScore[i][2].tex = D3DXVECTOR2( 0.0f, 1.0f );
		VertexWkScore[i][3].tex = D3DXVECTOR2( 1.0f, 1.0f );
	}

	return S_OK;
}
//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetTextureScore(void)
{
	int i;
	int number = Score;
	
	for( i = 0; i < SCORE_DIGIT; i++ )
	{
		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(number % 10);
		VertexWkScore[i][0].tex = D3DXVECTOR2( 0.1f * x, 0.0f );
		VertexWkScore[i][1].tex = D3DXVECTOR2( 0.1f * ( x + 1 ),	 0.0f );
		VertexWkScore[i][2].tex = D3DXVECTOR2( 0.1f * x, 1.0f );
		VertexWkScore[i][3].tex = D3DXVECTOR2( 0.1f * ( x + 1 ),	 1.0f );
		number /= 10;
	}

}
//=============================================================================
// �X�R�A�f�[�^���Z�b�g����
// ����:add :�ǉ�����_���B�}�C�i�X���\�A�������ȂǂɁB
//=============================================================================
void AddScore( int add )
{
	Score += add;
	if( Score > SCORE_MAX )
	{
		Score = SCORE_MAX;
	}
	else if( Score < 0 )
	{
		Score = 0;
	}

}
