#pragma once

#ifndef GAME_HAMMER_H_
#define GAME_HAMMER_H_

#include "d3dx9.h"

typedef struct
{

	bool IsEnable;
	bool IsAttacking;
	float AttackRotate;

}Hammer;



void GameHammer_Init();
void GameHammer_Update();
void GameHammer_Draw();
void GameHammer_Final();


#endif


