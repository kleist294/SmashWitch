#pragma once
#ifndef GAME_H_
#define GAME_H_






void Game_Init();

void Game_Update();

void Game_Draw();

void Game_Final(void);

int Get_Result();

bool GetPlaymode();
bool GetIsPause();
void PauseCancel();

void GameRestart();
void GameBackToTitle();
bool GetIsRestart();

float GetCursorX();
float GetCursorY();


#endif