//=============================================================================
//
// モデル処理 [model.h]
// Author : GP11A_341_22_田中太陽 
//
//=============================================================================
#ifndef _LEFTARM_H_
#define _LEFTARM_H_

#include "main.h"

typedef struct
{
	D3DXMATRIX			mtxWorld;			// ワールドマトリックス
	D3DXVECTOR3			pos;					// 現在の位置
	D3DXVECTOR3			rot;					// 現在の向き

	int					nIdxShadow;				// 影ID
	float				fSizeShadow;				// 影のサイズ
	D3DXCOLOR			colShadow;				// 影の色

}LEFTARM;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitLeftArm(void);
void UninitLeftArm(void);
void UpdateLeftArm(void);
void DrawLeftArm(void);

LEFTARM *GetLeftArm(int index);

#endif
