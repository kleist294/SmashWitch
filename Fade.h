#pragma once
#ifndef FADE_H_
#define FADE_H_






void Fade_Init();
void Fade_Update();
void Fade_Draw();
void Fade_Final(void);

typedef enum Fademode_tag
{
	FADE_NONE,
	FADE_IN,
	FADE_OUT,
	FADE_MAX

}FadeMode;

void Fade_Start(FadeMode mode,float r,float g , float b,int frame);
bool Fade_IsFade(void);

#endif