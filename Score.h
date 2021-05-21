#pragma once


#ifndef _SCORE_H_
#define _SCORE_H_





void GameScore_Init(int dig, bool zerofill, bool left);
void GameScore_Update();
void GameScore_Draw(float x, float y);
void GameScore_AddScore(int score);
int GameScore_GetScore(int score);
void GameScore_ConfirmScore();
void DrawNumber(int n, float x, float y);

#endif