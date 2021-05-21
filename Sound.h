//=============================================================================
//
// サウンド処理 [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <windows.h>
#include "xaudio2.h"						// サウンド処理で必要

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000,		    // BGM0
	SOUND_LABEL_SE_SHOT,		// 弾発射音
	SOUND_LABEL_SE_EXPLOSION,	// 爆発音
	SOUND_LABEL_SE_DECISION,
	SOUND_LABEL_SE_LANDING,
	SOUND_LABEL_SE_HAMMER,
	SOUND_LABEL_SE_BULLET,
	SOUND_LABEL_SE_FALLHIT,
	SOUND_LABEL_SE_LOCKON,
	SOUND_LABEL_SE_SUMMON,
	SOUND_LABEL_BGM_WIN,
	SOUND_LABEL_BGM_TITLE,
	SOUND_LABEL_BGM_LOSE,
	SOUND_LABEL_SE_CANCEL,
	SOUND_LABEL_SE_PAUSE,
	SOUND_LABEL_SE_CURSOR,
	SOUND_LABEL_SE_CHANGEWEAPON,
	SOUND_LABEL_SE_BOMBDROP,
	SOUND_LABEL_SE_BOMBEXPLODE,
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool InitSound(HWND hWnd);
void UninitSound(void);
void PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
