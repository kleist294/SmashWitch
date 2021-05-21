#pragma once
#pragma once
#pragma once
#ifndef KEYLOGGER_H_
#define KEYLOGGER_H_

typedef enum KeyKind_tag
{
	//本アプリで使ったキー
	KL_UP,
	KL_DOWN,
	KL_LEFT,
	KL_RIGHT,
	KL_DECISION,
	KL_JUMP = KL_DECISION,
	KL_CANCEL,
	KL_SPECIAL = KL_CANCEL,
	KL_WEAPONCHANGE,
	KL_ATTACK,
	KL_TURN_LEFT,
	KL_TURN_RIGHT,
	KL_TURN_UP,
	KL_TURN_DOWN,
	KL_ESC,
	KL_NEAR,
	KL_FAR,
	KL_WIREFRAME_MODE,
	KL_MAX


}KeyKind;



void KeyLogger_Init();
void KeyLogger_Update();
void KeyLogger_Final(void);

bool KeyloggerPress(KeyKind kl);
bool KeyloggerTrigger(KeyKind kl);
bool KeyloggerRelease(KeyKind kl);

void Keylogger_RecordStart(int frame_max);
void Keylogger_RecordEnd(void);
void Keylogger_RecordLoad(void);

void Keylogger_RecordPlay(void);
bool Keylogger_IsRecordPlay(void);






#endif