//=============================================================================
//
// ���C������ [main.cpp]
// Author : GP11A_341_22_�c�����z
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "light.h"
#include "camera.h"
#include "player.h"
#include "shadow.h"
#include "debugproc.h"
#include "effect.h"
#include "bullet.h"
#include "title.h"
#include "tutorial.h"
#include "result.h"
#include "score.h"
#include "field.h"
#include "checkhit.h"
#include "explosion.h"
#include "smoke.h"
#include "leftArm.h"
#include "rightArm.h"
#include "leftReg.h"
#include "rightReg.h"
#include "head.h"
#include "block.h"
#include "bulletGauge.h"
#include "lifeGauge.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"		// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"�A�v����i"		// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3D �I�u�W�F�N�g
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// Device�I�u�W�F�N�g(�`��ɕK�v)
#ifdef _DEBUG
int					g_nCountFPS;			// FPS�J�E���^
#endif
bool				g_bDispDebug = true;	// �f�o�b�O�\��ON/OFF
int					StageSelect;

//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND hWnd;
	MSG msg;
	
	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindowEx(0,
						CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
						NULL,
						NULL,
						hInstance,
						NULL);

	// ����������(�E�B���h�E���쐬���Ă���s��)
	if(FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// �t���[���J�E���g������
	timeBeginPeriod(1);				// ����\��ݒ�
	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	dwFrameCount = 0;

	// �E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// ���b�Z�[�W���[�v
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
			{
#ifdef _DEBUG
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
#ifdef _DEBUG
				PrintDebugProc("FPS:%d\n", g_nCountFPS);
#endif

				dwExecLastTime = dwCurrentTime;

				// �X�V����
				Update();

				// �`�揈��
				Draw();

				dwFrameCount++;
			}
		}
	}
	
	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	Uninit();

	timeEndPeriod(1);				// ����\��߂�

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
    D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
    if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferCount			= 1;						// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth			= SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight			= SCREEN_HEIGHT;			// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat			= d3ddm.Format;				// �J���[���[�h�̎w��
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed					= bWindow;					// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil	= TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				// �f�v�X�o�b�t�@�Ƃ���16bit���g��

	if(bWindow)
	{// �E�B���h�E���[�h
		d3dpp.FullScreen_RefreshRateInHz = 0;								// ���t���b�V�����[�g
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	}
	else
	{// �t���X�N���[�����[�h
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
	}

	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
									D3DDEVTYPE_HAL, 
									hWnd, 
									D3DCREATE_HARDWARE_VERTEXPROCESSING, 
									&d3dpp, &g_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp, &g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp, &g_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �����_�����O�X�e�[�g�p�����[�^�̐ݒ�
    g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	// �e�N�X�`���X�e�[�W���Z��������
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

	// ���͏����̏�����
	InitInput(hInstance, hWnd);

	// �f�o�b�O�\�������̏�����
	InitDebugProc();

	// ���C�g�̏�����
	InitLight();

	// �J�����̏�����
	InitCamera();

	// �e�̏�����
	InitShadow(0);

	// �v���C���[�̏�����
	InitPlayer(0);

	// �o���b�g�̏�����
	InitBullet(0);

	// �G�t�F�N�g�̏�����
	InitEffect(0);

	//
	InitExplosion(0);

	// �X�R�A�̏�����
	InitScore(0);

	// �^�C�g���̏�����
	InitTitle(0);

	// ���U���g�̏�����
	InitResult(0);

	// �`���[�g���A���̏�����
	InitTutorial(0);

	// �t�B�[���h�̏�����
	InitField(0);
	
	InitSmoke(0);

	InitLeftArm();

	InitLeftReg();

	InitRightArm();

	InitRightReg();

	InitHead();

	//
	InitBlock(0);

	//
	InitBulletGauge(0);

	//
	InitLifeGauge(0);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	if(g_pD3DDevice != NULL)
	{// �f�o�C�X�̊J��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if(g_pD3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	// ���͏����̏I������
	UninitInput();

	// �f�o�b�O�\�������̏I������
	UninitDebugProc();

	// �e�̏I������
	UninitShadow();

	// �o���b�g�̏I������
	UninitBullet();

	// �v���C���[�̏I������
	UninitPlayer();

	// �G�t�F�N�g�̏I������
	UninitEffect();

	// �^�C�g���̏I������
	UninitTitle();

	// ���U���g�̏I������
	UninitResult();

	// �`���[�g���A���̏I������
	UninitTutorial();

	//
	UninitField();

	//
	UninitExplosion();

	//
	UninitSmoke();

	UninitLeftArm();

	UninitLeftReg();

	UninitRightArm();

	UninitRightReg();

	UninitHead();

	//
	UninitBlock();

	//
	UninitBulletGauge();

	//
	UninitLifeGauge();

}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	if(GetKeyboardTrigger(DIK_F1))
	{// �f�o�b�O�\��ON/OFF
		g_bDispDebug = g_bDispDebug ? false: true;
	}

	// ���͍X�V
	UpdateInput();
	//ImGui_ImplDX9_NewFrame();

	switch (StageSelect)
	{
		case TITLE:
		{
			// �^�C�g���̏I������
			UpdateTitle();

			break;
		}
		case TUTORIAL:
		{
			// �`���[�g���A���̏I������
			UpdateTutorial();
			//
			//// 
			//UpdateField();

			//// �e�����̍X�V
			//UpdateShadow();

			//// �J�����X�V
			//UpdateCamera();

			//// �G�l�~�[�̍X�V
			//UpdateTarget();

			//// ���f�������̍X�V
			//UpdatePlayer();
			
			//// ���r�̍X�V
			//UpdateLeftArm();

			//// �����̍X�V
			//UpdateLeftReg();

			//// �E�r�̍X�V
			//UpdateRightArm();

			//// �E���̍X�V
			//UpdateRightReg();

			//// ���̍X�V
			//UpdateHead();

			//// �G�t�F�N�g�̍X�V
			//UpdateEffect();

			////
			//Updateexplosion();

			//// 
			//UpdateSmoke();

			//// �o���b�g�̍X�V
			//UpdateBullet();

			//CheckHit();

			break;
		}
		case START:
		{
			// 
			UpdateField();

			//
			UpdateBlock();

			// �e�����̍X�V
			UpdateShadow();

			// �J�����X�V
			UpdateCamera();

			// ���f�������̍X�V
			UpdatePlayer();
			
			// ���r�̍X�V
			UpdateLeftArm();
			
			// �����̍X�V
			UpdateLeftReg();
			
			// �E�r�̍X�V
			UpdateRightArm();
		
			// �E���̍X�V
			UpdateRightReg();
			
			// ���̍X�V
			UpdateHead();

			// �G�t�F�N�g�̍X�V
			UpdateEffect();

			// �e���̍X�V
			UpdateExplosion();

			// ���̍X�V
			UpdateSmoke();

			// �o���b�g�̍X�V
			UpdateBullet();

			// �X�R�A�̍X�V
			//UpdateScore();
			
			// 
			UpdateBulletGauge();

			//
			UpdateLifeGauge();

			// �����蔻��
			CheckHit();

			break;
		}
		case RESULT:
		{
			// ���U���g�̍X�V
			UpdateResult();

			break;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(75, 144, 205, 180), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (StageSelect)
		{
			case TITLE:
			{
				// �^�C�g���̏I������
				DrawTitle();

				break;
			}
			case TUTORIAL:
			{
				// �`���[�g���A���̏I������
				DrawTutorial();
				
				//// �J�����̐ݒ�
				//SetCamera();

				////
				//DrawField();

				//// �e�����̕`��
				//DrawShadow();

				//// �^�[�Q�b�g�̕`��
				//DrawTarget();

				//// �o���b�g�̕`��
				//DrawBullet();

				//// �K���G�t�F�N�g�̕`��
				//DrawEffect();

				//// 
				//Drawexplosion();

				////
				//DrawSmoke();

				//// �v���C���[�����̕`��
				//DrawPlayer();

				//// ���r�̍X�V
				//DrawLeftArm();

				//// �����̍X�V
				//DrawLeftReg();

				//// �E�r�̍X�V
				//DrawRightArm();

				//// �E���̍X�V
				//DrawRightReg();

				//// ���̍X�V
				//DrawHead();


				break;
			}
			case START:
			{
				// �J�����̐ݒ�
				SetCamera();
				
				//
				DrawField();

				//
				DrawBlock();

				// �e�����̕`��
				DrawShadow();

				// �o���b�g�̕`��
				DrawBullet();

				// �K���G�t�F�N�g�̕`��
				DrawEffect();

				// �e���̕`��
				DrawExplosion();

				// ���̕`��
				DrawSmoke();

				// �v���C���[�����̕`��
				DrawPlayer();

				// ���̕`��
				DrawHead();

				// ���r�̕`��
				DrawLeftArm();

				// �E�r�̕`��
				DrawRightArm();

				// �����̕`��
				DrawLeftReg();

				// �E���̕`��
				DrawRightReg();

				// �X�R�A�̕`��
				//DrawScore();

				//
				DrawLifeGauge();

				//
				DrawBulletGauge();


				// �f�o�b�O�\�������̕`��
				if (g_bDispDebug)
				{
					DrawDebugProc();
				}

				break;
			}
			case RESULT:
			{
				// ���U���g�̏I������
				DrawResult();

				break;
			}


		}

		// Direct3D�ɂ��`��̏I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// �f�o�C�X�̎擾
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}



//============================================================================
// �Q�[���J�ڂ̐ݒu
// �����F int Stage(�J�ڐ�̔ԍ�)
// �߂�l�F�Ȃ�
//============================================================================
void SetStage(int Stage)
{
	StageSelect = Stage;
}

//============================================================================
// �Q�[���J�ڂ̎擾
// �����F int Stage(�J�ڐ�̔ԍ�)
// �߂�l�F�Ȃ�
//============================================================================
int GetStage(void)
{
	return StageSelect;
}


//============================================================================
// �Q�[���̍ď�����
//
//============================================================================
void InitGame(void)
{

	// ���C�g�̏�����
	InitLight();

	// �J�����̏�����
	InitCamera();

	// �e�̏�����
	InitShadow(INIT_GAME);

	// �v���C���[�̏�����
	InitPlayer(INIT_GAME);

	// �o���b�g�̏�����
	InitBullet(INIT_GAME);

	// �G�t�F�N�g�̏�����
	InitEffect(INIT_GAME);

	// �X�R�A�̏�����
	InitScore(INIT_GAME);

	// �^�C�g���̏�����
	InitTitle(0);

	// ���U���g�̏�����
	InitResult(INIT_GAME);

	// �`���[�g���A���̏�����
	InitTutorial(INIT_GAME);

	// �t�B�[���h�̏�����
	InitField(INIT_GAME);

}

