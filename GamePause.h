#pragma once
#ifndef PAUSE_H_
#define PAUSE_H_


typedef enum
{
	MODE_RESUME,
	MODE_RESTART,
	MODE_BACKTOTITLE,
	MODE_MAX

}PAUSEMODE;


void Pause_Init();
void Pause_Update();
void Pause_Draw();
void Pause_Final(void);
void PauseAnimation();



#endif