//=============================================================================
//
// AI [ai.h]
// Author : GP11A_341_22_c¾z
//
//=============================================================================
#ifndef _AI_H_
#define _AI_H_

#include "main.h"

#define MOVE_CMP_MAX			(3)

typedef struct {

	float	patternA;				// ärÌvl
	float	patternB;				//
	float   patternC;				//
	float	decision;				// ärÊ
	float	atc[MOVE_CMP_MAX];		// U
	float	chase[MOVE_CMP_MAX];	// ÇÕ
	float	escape[MOVE_CMP_MAX];	// ¦
	float	avoid[1];				// ñð
	float	wait[MOVE_CMP_MAX];

}AI;

//*****************************************************************************
// vg^Cvé¾
//*****************************************************************************
HRESULT InitAi(void);
void NonePlayerMove(void);
void NonePlayerAttack(void);

float FuzzyRightUp(float val, float x0, float x1);
float FuzzyRightDown(float val, float x0, float x1);
float FuzzyTriangle(float val, float x0, float x1, float x2);
float FuzzyTrapezoid(float val, float x0, float x1, float x2, float x3);

float And(float a, float b);
float Or(float a, float b);
float Not(float a, float b);

#endif
