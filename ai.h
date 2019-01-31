//=============================================================================
//
// AI���� [ai.h]
// Author : GP11A_341_22_�c�����z
//
//=============================================================================
#ifndef _AI_H_
#define _AI_H_

#include "main.h"


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
float FuzzyRightUp(float val, float x0, float x1);
float FuzzyRightDown(float val, float x0, float x1);
float FuzzyTriangle(float val, float x0, float x1, float x2);
float FuzzyTrapezoid(float val, float x0, float x1, float x2, float x3);

float And(float a, float b);
float Or(float a, float b);
float Not(float a, float b);
void NonePlayerMove(void);

#endif
