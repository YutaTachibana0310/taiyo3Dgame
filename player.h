//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : GP11A_341_22_田中太陽
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//=============================================================================
//マクロ定義
//=============================================================================

#define PLAYER_MAX				(2)
#define PLAYER_LIFE_MAX			(100.0f)
#define PLAYER_FALL_SPEED		(5.0f)


typedef struct {
	
	D3DXMATRIX					mtxWorld;			// ワールドマトリックス
	D3DXVECTOR3					pos;				// 現在の位置
	D3DXVECTOR3					prevPos;			// 過去の位置
	D3DXVECTOR3					move;				// 移動量
	D3DXVECTOR3					rot;				// 回転量
	D3DXVECTOR3					rotDest;			// 現在の向き
	D3DXVECTOR3					frontVec;			// 前方ベクトル
	bool						use;				// 使用状態
	float						speed;				// 移動の速さ
	float						life;				// 体力
	int							IdxShadow;			// 影ID
	float						SizeShadow;			// 影のサイズ
	D3DXCOLOR					colShadow;			// 影の色
	int							cntFrame;


}PLAYER;

enum {
	P1,
	P2
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(int type);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER *GetPlayer(int index);
bool PlayerDamageManager(int index);
bool CheckBlockInPlayer(int index);
void CheckNorPlayer(D3DXVECTOR3 nor0, int index);

#endif
