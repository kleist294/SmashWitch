
/*============================================================

　　　　　　ポーズの状態（一時停止）

============================================================*/



#include "TextureManager.h"
#include <d3dx9.h>
#include "sound.h"
#include "Billboard.h"
#include "Camera.h"
#include "game.h"
#include "GamePause.h"
#include "keylogger.h"
#include "sound.h"
#include "mouse.h"


static int g_TextureID = INVALID_TEXTURE_ID;
static int g_TextureIDBoard = INVALID_TEXTURE_ID;
static int g_TextureIDPause = INVALID_TEXTURE_ID;
static int g_TextureIDResume = INVALID_TEXTURE_ID;
static int g_TextureIDRestart = INVALID_TEXTURE_ID;
static int g_TextureIDBackTo = INVALID_TEXTURE_ID;
static int g_TextureIDArrow = INVALID_TEXTURE_ID;
static int g_TextureIDYes = INVALID_TEXTURE_ID;
static int g_TextureIDNo = INVALID_TEXTURE_ID;




static D3DXVECTOR3 g_BoardPos = { 0.0f,0.0f,0.0f };
static D3DXVECTOR3 g_BoardYesNoPos = { 0.0f,0.0f,0.0f };

static float g_BoardSpeed = 1.0f;
static float g_BoardHeight = 10.0f;
static float g_ArrowHeight = 2.8f;
static float g_ArrowRightOffSet = 0.0f;
static float g_ArrowRight = -2.0f;
static float g_ArrowBackToRight = 5.0f;
static D3DXCOLOR g_Alpha[9];
static D3DXCOLOR g_Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);;
static bool g_BackToTitle = false;
static bool g_PauseMoving = false;
static bool g_BackToYes = false;
static int g_PauseFrame = 0;
static int g_PauseArrowMove = 0;
static int g_PauseMoveFrame = 0;
static int g_PauseBackToFrame = 0;

static int g_PauseMode = MODE_RESUME;

static Mouse_State g_Mouse;


/*============================================================
　　　　　　　ポーズの初期化
============================================================*/

void Pause_Init()
{
	g_TextureID = Texture_SetTextureLoadFile("asset\\texture\\fade.png");
	g_TextureIDBoard = Texture_SetTextureLoadFile("asset\\texture\\board2.png");
	g_TextureIDPause = Texture_SetTextureLoadFile("asset\\texture\\pause.png");
	g_TextureIDResume = Texture_SetTextureLoadFile("asset\\texture\\resume.png");
	g_TextureIDRestart = Texture_SetTextureLoadFile("asset\\texture\\Restart.png");
	g_TextureIDBackTo = Texture_SetTextureLoadFile("asset\\texture\\backtotitle.png");
	g_TextureIDArrow = Texture_SetTextureLoadFile("asset\\texture\\PauseArrow.png");
	g_TextureIDYes = Texture_SetTextureLoadFile("asset\\texture\\Yes.png");
	g_TextureIDNo = Texture_SetTextureLoadFile("asset\\texture\\No.png");

	g_PauseFrame = 0;
	g_PauseMoveFrame = 0;
	g_PauseBackToFrame = 0;
	g_PauseArrowMove = 0;
	g_PauseMode = MODE_RESUME;
	g_BoardSpeed = 0.5f;
	g_BoardHeight = 10.0f;
	g_ArrowHeight = 3.0f;
	g_ArrowRightOffSet = 0.0f;
	g_ArrowRight = -2.0f;
	g_ArrowBackToRight = 5.0f;
	g_BackToTitle = false;
	g_PauseMoving = false;
	g_BackToYes = false;

	g_Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	for (int i = 0; i < 9; i++) {
		g_Alpha[i].r = 1.0f;
		g_Alpha[i].g = 1.0f;
		g_Alpha[i].b = 1.0f;
		g_Alpha[i].a = 0;
	}


	g_BoardPos = { Camera_GetPosition()->x + Camera_GetFrontVector()->x * 10.0f - Camera_GetRightVector()->x * 0.0f  + Camera_GetUpVector()->x * (1.0f + g_BoardHeight),
				   Camera_GetPosition()->y + Camera_GetFrontVector()->y * 10.0f - Camera_GetRightVector()->y * 0.0f  + Camera_GetUpVector()->y * (1.0f + g_BoardHeight),
				   Camera_GetPosition()->z + Camera_GetFrontVector()->z * 10.0f - Camera_GetRightVector()->z * 0.0f  + Camera_GetUpVector()->z * (1.0f + g_BoardHeight) };
	g_BoardYesNoPos = { Camera_GetPosition()->x + Camera_GetFrontVector()->x * 10.0f - Camera_GetRightVector()->x * 0.0f - Camera_GetUpVector()->x * 3.5f,
				        Camera_GetPosition()->y + Camera_GetFrontVector()->y * 10.0f - Camera_GetRightVector()->y * 0.0f - Camera_GetUpVector()->y * 3.5f,
				        Camera_GetPosition()->z + Camera_GetFrontVector()->z * 10.0f - Camera_GetRightVector()->z * 0.0f - Camera_GetUpVector()->z * 3.5f };

}

/*============================================================
　　　　　　　ポーズのアップデート
============================================================*/
void Pause_Update()
{

	Mouse_GetState(&g_Mouse);

	if (GetIsPause() == true)
	{
		float CursorX = GetCursorX();
		float CursorY = GetCursorY();




		if ((KeyloggerTrigger(KL_TURN_UP)|| KeyloggerTrigger(KL_UP) )&& g_BackToTitle == false)
		{
			PlaySound(SOUND_LABEL_SE_CURSOR);
			g_PauseMode--;
			if (g_PauseMode <= -1)
			{
				g_PauseMode = 2;
			}
		}

		if ((CursorX >= 300.0f && CursorX <= 1000.0f) && g_BackToTitle == false)
		{
			if(CursorY <= 235.0f && CursorY >= 122.0f)
			g_PauseMode = 0;
			else if(CursorY > 235.0f && CursorY <= 340.0f)
			g_PauseMode = 1;
			else if(CursorY > 340.0f && CursorY <= 460.0f)
			g_PauseMode = 2;
		}


		if ((KeyloggerTrigger(KL_TURN_DOWN) || KeyloggerTrigger(KL_DOWN)) && g_BackToTitle == false)
		{
			PlaySound(SOUND_LABEL_SE_CURSOR);
			g_PauseMode++;
			if (g_PauseMode >= 3)
			{
				g_PauseMode = 0;
			}
		}

		if ((KeyloggerTrigger(KL_TURN_LEFT) || KeyloggerTrigger(KL_LEFT)) && g_BackToTitle == true)
		{
			PlaySound(SOUND_LABEL_SE_CURSOR);
			if (g_BackToYes == false)
			{
				g_BackToYes = true;
			}
			else if(g_BackToYes == true)
			{
				g_BackToYes = false;
			}
		}
		else if ((KeyloggerTrigger(KL_TURN_RIGHT) || KeyloggerTrigger(KL_RIGHT)) && g_BackToTitle == true)
		{
			PlaySound(SOUND_LABEL_SE_CURSOR);
			if (g_BackToYes == false)
			{
				g_BackToYes = true;
			}
			else if (g_BackToYes == true)
			{
				g_BackToYes = false;
			}
		}

		if ((CursorY >= 520.0f && CursorY <= 635.0f) && g_BackToTitle == true)
		{
		if(CursorX >= 150.0f && CursorX <= 570.0f)
			g_BackToYes = true;
		else if(CursorX >= 725.0f && CursorX <= 1170.0f)
			g_BackToYes = false;

		}


		if (g_PauseMoving == true) {
			g_BoardHeight -= g_BoardSpeed;
			g_BoardSpeed *= 0.95f;

			if (g_BoardHeight <= 0.001)
			{
				g_BoardHeight = 0.001;
				g_PauseMoving = false;
			}

		}
		if (g_BackToTitle == false && KeyloggerTrigger(KL_DECISION))
		{
			switch (g_PauseMode)
			{
			case MODE_RESUME:
				
				PlaySound(SOUND_LABEL_SE_PAUSE);
				PauseCancel();
				break;
			case MODE_RESTART:
				PlaySound(SOUND_LABEL_SE_DECISION);
				g_BackToTitle = true;
				break;
			case MODE_BACKTOTITLE:
				PlaySound(SOUND_LABEL_SE_DECISION);
				g_BackToTitle = true;
				break;
			}


		}
		else if (g_BackToTitle == true && KeyloggerTrigger(KL_DECISION))
		{
			switch (g_PauseMode)
			{
			case MODE_RESTART:
				switch (g_BackToYes)
				{
				case true:
					PlaySound(SOUND_LABEL_SE_DECISION);
					GameRestart();
					break;
				case false:
					PlaySound(SOUND_LABEL_SE_CANCEL);
					g_BackToTitle = false;
					break;
				}
				break;
			case MODE_BACKTOTITLE:
				switch (g_BackToYes)
				{
				case true:
					PlaySound(SOUND_LABEL_SE_DECISION);
					GameBackToTitle();
					break;
				case false:
					PlaySound(SOUND_LABEL_SE_CANCEL);
					g_BackToTitle = false;
					break;
				}
				break;
			}
			
		}
		if (g_BackToTitle == false && g_Mouse.leftButton == true)
		{
			switch (g_PauseMode)
			{
			case MODE_RESUME:
				if (CursorX >= 300.0f && CursorX <= 1000.0f && CursorY <= 235.0f && CursorY >= 122.0f)
				{
					PlaySound(SOUND_LABEL_SE_PAUSE);
					PauseCancel();
				}
				break;
			case MODE_RESTART:
				if (CursorX >= 300.0f && CursorX <= 1000.0f && CursorY > 235.0f && CursorY <= 340.0f)
				{
					PlaySound(SOUND_LABEL_SE_DECISION);
					g_BackToTitle = true;
				}
				break;
			case MODE_BACKTOTITLE:
				if (CursorX >= 300.0f && CursorX <= 1000.0f && CursorY > 340.0f && CursorY <= 460.0f)
				{
					PlaySound(SOUND_LABEL_SE_DECISION);
					g_BackToTitle = true;
				}
				break;
			}


		}
		else if (g_BackToTitle == true && g_Mouse.leftButton == true)
		{
			switch (g_PauseMode)
			{
			case MODE_RESTART:
				switch (g_BackToYes)
				{
				case true:
					if (CursorY >= 520.0f && CursorY <= 635.0f && CursorX >= 150.0f && CursorX <= 570.0f) {
						PlaySound(SOUND_LABEL_SE_DECISION);
						GameRestart();
					}
					break;
				case false:
					if (CursorY >= 520.0f && CursorY <= 635.0f && CursorX >= 725.0f && CursorX <= 1170.0f) {
						PlaySound(SOUND_LABEL_SE_CANCEL);
						g_BackToTitle = false;
					}
					break;
				}
				break;
			case MODE_BACKTOTITLE:
				switch (g_BackToYes)
				{
				case true:
					if (CursorY >= 520.0f && CursorY <= 635.0f && CursorX >= 150.0f && CursorX <= 570.0f) {
						PlaySound(SOUND_LABEL_SE_DECISION);
						GameBackToTitle();
					}
					break;
				case false:
					if (CursorY >= 520.0f && CursorY <= 635.0f && CursorX >= 725.0f && CursorX <= 1170.0f) {
						PlaySound(SOUND_LABEL_SE_CANCEL);
						g_BackToTitle = false;
					}
					break;
				}
				break;
			}

		}




		
		if (g_PauseFrame >= 30) {
			g_Alpha[0].a += 0.1f;
			if (g_Alpha[0].a >= 1.0f)
			{
				g_Alpha[0].a = 1.0f;
			}
		}
		if (g_PauseFrame >= 60)
		{
			g_Alpha[1].a += 0.1f;
			if (g_Alpha[1].a >= 1.0f)
			{
				g_Alpha[1].a = 1.0f;
			}
		}
		if (g_PauseFrame >= 90)
		{
			g_Alpha[2].a += 0.1f;
			if (g_Alpha[2].a >= 1.0f)
			{
				g_Alpha[2].a = 1.0f;
			}
		}
		if (g_PauseFrame >= 120)
		{
			g_Alpha[3].a += 0.1f;
			if (g_Alpha[3].a >= 1.0f)
			{
				g_Alpha[3].a = 1.0f;
			}

			g_Alpha[4].a += 0.1f;
			if (g_Alpha[4].a >= 1.0f)
			{
				g_Alpha[4].a = 1.0f;
			}
		}


		if (g_BackToTitle == true)
		{
			g_Alpha[5].a += 0.1f;
			if (g_Alpha[5].a >= 1.0f)
			{
				g_Alpha[5].a = 1.0f;
			}

			if (g_PauseBackToFrame >= 30)
			{
				g_Alpha[6].a += 0.1f;
				if (g_Alpha[6].a >= 1.0f)
				{
					g_Alpha[6].a = 1.0f;
				}
			}

			if (g_PauseBackToFrame >= 60)
			{
				g_Alpha[7].a += 0.1f;
				

				if (g_Alpha[7].a >= 1.0f)
				{
					g_Alpha[7].a = 1.0f;
				}

				g_Alpha[8].a += 0.1f;
				if (g_Alpha[8].a >= 1.0f)
				{
					g_Alpha[8].a = 1.0f;
				}
			}

			switch (g_BackToYes)
			{
			case true:
				g_ArrowBackToRight = -7.0f;
				break;
			case false:
				g_ArrowBackToRight = 3.5f;
				break;
			}

			g_PauseBackToFrame++;
		}
		else if(g_BackToTitle == false)
		{
			for (int i = 5; i < 9; i++) {

				g_Alpha[i].a -= 0.2f;
				if (g_Alpha[i].a <= 0.0f)
				{
					g_Alpha[i].a = 0.0f;
				}
			}
			g_PauseBackToFrame = 0;
		}


		g_Color.a += 0.02f;
		if (g_Color.a >= 0.3f)
		{
			g_Color.a = 0.3f;
		}

		if (g_PauseArrowMove == 0)
		{
			g_ArrowRightOffSet -= 0.01f;
			if (g_ArrowRightOffSet <= -0.5f)
			{
				g_ArrowRightOffSet = -0.5f;
				g_PauseArrowMove = 1;
			}
		}
		else if (g_PauseArrowMove == 1)
		{
			g_ArrowRightOffSet += 0.01f;
			if (g_ArrowRightOffSet >= -0.1f)
			{
				g_ArrowRightOffSet = -0.1f;
				g_PauseArrowMove = 0;
			}
		}


		switch (g_PauseMode)
		{
		case MODE_RESUME:
			g_ArrowRight = -3.4f;
			g_ArrowHeight = 2.8f;
			break;
		case MODE_RESTART:
			g_ArrowRight = -3.6f;
			g_ArrowHeight = 1.05f;
			break;
		case MODE_BACKTOTITLE:
			g_ArrowRight = -5.2f;
			g_ArrowHeight = - 0.7f;
			break;
		}
		
		

		g_PauseFrame++;
	}
	else
	{

	g_PauseMode = MODE_RESUME;
	g_BackToTitle = false;
	g_BackToYes = false;
		if (g_PauseMoving == true) {			
			g_BoardHeight += g_BoardSpeed;
			g_BoardSpeed *= 0.95f;

			if (g_BoardHeight >= 9.9f)
			{
				g_BoardHeight = 9.9f;
				g_PauseMoving = false;
			}
		}

		for (int i = 0; i < 9; i++) {

			g_Alpha[i].a -= 0.2f;
			if (g_Alpha[i].a <= 0.0f)
			{
				g_Alpha[i].a = 0.0f;
			}
		}

		g_Color.a -= 0.02f;
		if (g_Color.a <= 0.0f)
		{
			g_Color.a = 0.0f;
		}

		g_PauseFrame = 0;
	}


	//g_PauseMoveFrame++;


	g_BoardPos = { Camera_GetPosition()->x + Camera_GetFrontVector()->x * 10.0f - Camera_GetRightVector()->x * 0.0f + Camera_GetUpVector()->x * (1.0f + g_BoardHeight),
				   Camera_GetPosition()->y + Camera_GetFrontVector()->y * 10.0f - Camera_GetRightVector()->y * 0.0f + Camera_GetUpVector()->y * (1.0f + g_BoardHeight),
				   Camera_GetPosition()->z + Camera_GetFrontVector()->z * 10.0f - Camera_GetRightVector()->z * 0.0f + Camera_GetUpVector()->z * (1.0f + g_BoardHeight) };
	
	g_BoardYesNoPos = { Camera_GetPosition()->x + Camera_GetFrontVector()->x * 10.0f - Camera_GetRightVector()->x * 0.0f - Camera_GetUpVector()->x * 3.5f,
				   Camera_GetPosition()->y + Camera_GetFrontVector()->y * 10.0f - Camera_GetRightVector()->y * 0.0f - Camera_GetUpVector()->y * 3.5f,
				   Camera_GetPosition()->z + Camera_GetFrontVector()->z * 10.0f - Camera_GetRightVector()->z * 0.0f - Camera_GetUpVector()->z * 3.5f };

}

/*============================================================
　　　　　　　ポーズの描画
============================================================*/
void Pause_Draw() 
{

	Billboard_SetColor(g_Color);
	Billboard_DrawNonZBuffer(g_TextureID, Camera_GetPosition()->x + Camera_GetFrontVector()->x * 0.2f, Camera_GetPosition()->y + Camera_GetFrontVector()->y * 0.2f, Camera_GetPosition()->z + Camera_GetFrontVector()->z * 0.2f, 1.0f, 1.0f, 100.0f);
	Billboard_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));

	Billboard_SetColor(g_Alpha[0]);
	Billboard_DrawAnimationNonZBuffer(g_TextureIDPause,
		Camera_GetPosition()->x + Camera_GetFrontVector()->x * 10.0f + Camera_GetRightVector()->x * 0.0f + Camera_GetUpVector()->x * 5.0f,
		Camera_GetPosition()->y + Camera_GetFrontVector()->y * 10.0f + Camera_GetRightVector()->y * 0.0f + Camera_GetUpVector()->y * 5.0f,
		Camera_GetPosition()->z + Camera_GetFrontVector()->z * 10.0f + Camera_GetRightVector()->z * 0.0f + Camera_GetUpVector()->z * 5.0f,
		2.19f, 1.21f, 0, 0, 219, 121);
	Billboard_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));

	Billboard_DrawAnimationNonZBuffer(g_TextureIDBoard, g_BoardPos.x, g_BoardPos.y , g_BoardPos.z,7.0f,3.0f,0, 0, 1280,536);



	Billboard_SetColor(g_Alpha[1]);
	Billboard_DrawAnimationNonZBuffer(g_TextureIDResume,
		Camera_GetPosition()->x + Camera_GetFrontVector()->x * 10.0f + Camera_GetRightVector()->x * 0.0f + Camera_GetUpVector()->x * 3.0f,
	    Camera_GetPosition()->y + Camera_GetFrontVector()->y * 10.0f + Camera_GetRightVector()->y * 0.0f + Camera_GetUpVector()->y * 3.0f,
	    Camera_GetPosition()->z + Camera_GetFrontVector()->z * 10.0f + Camera_GetRightVector()->z * 0.0f + Camera_GetUpVector()->z * 3.0f,
	    2.59f, 1.2f, 0, 0, 259, 120);

	Billboard_SetColor(g_Alpha[2]);
	Billboard_DrawAnimationNonZBuffer(g_TextureIDRestart, 
		Camera_GetPosition()->x + Camera_GetFrontVector()->x * 10.0f + Camera_GetRightVector()->x * 0.0f + Camera_GetUpVector()->x * 1.25f,
		Camera_GetPosition()->y + Camera_GetFrontVector()->y * 10.0f + Camera_GetRightVector()->y * 0.0f + Camera_GetUpVector()->y * 1.25f,
		Camera_GetPosition()->z + Camera_GetFrontVector()->z * 10.0f + Camera_GetRightVector()->z * 0.0f + Camera_GetUpVector()->z * 1.25f,
		2.89f, 1.2f, 0, 0, 289, 120);

	Billboard_SetColor(g_Alpha[3]);
	Billboard_DrawAnimationNonZBuffer(g_TextureIDBackTo, 
		Camera_GetPosition()->x + Camera_GetFrontVector()->x * 10.0f + Camera_GetRightVector()->x * 0.5f - Camera_GetUpVector()->x * 0.5f,
		Camera_GetPosition()->y + Camera_GetFrontVector()->y * 10.0f + Camera_GetRightVector()->y * 0.5f - Camera_GetUpVector()->y * 0.5f,
		Camera_GetPosition()->z + Camera_GetFrontVector()->z * 10.0f + Camera_GetRightVector()->z * 0.5f - Camera_GetUpVector()->z * 0.5f,
		4.91f, 1.28f, 0, 0, 491, 128);

	Billboard_SetColor(g_Alpha[4]);
	Billboard_DrawAnimationNonZBuffer(g_TextureIDArrow,
		Camera_GetPosition()->x + Camera_GetFrontVector()->x * 10.0f + Camera_GetRightVector()->x * (g_ArrowRight + g_ArrowRightOffSet) + Camera_GetUpVector()->x * g_ArrowHeight,
		Camera_GetPosition()->y + Camera_GetFrontVector()->y * 10.0f + Camera_GetRightVector()->y * (g_ArrowRight + g_ArrowRightOffSet) + Camera_GetUpVector()->y * g_ArrowHeight,
		Camera_GetPosition()->z + Camera_GetFrontVector()->z * 10.0f + Camera_GetRightVector()->z * (g_ArrowRight + g_ArrowRightOffSet) + Camera_GetUpVector()->z * g_ArrowHeight,
		1.0f, 0.5f, 0, 0, 905, 274);



	Billboard_SetColor(g_Alpha[5]);
	Billboard_DrawAnimationNonZBuffer(g_TextureIDBoard, g_BoardYesNoPos.x, g_BoardYesNoPos.y, g_BoardYesNoPos.z, 15.0f, 1.0f, 0, 0, 1280, 536);
	
	
	Billboard_SetColor(g_Alpha[6]);
	Billboard_DrawAnimationNonZBuffer(g_TextureIDYes,
		Camera_GetPosition()->x + Camera_GetFrontVector()->x * 10.0f + Camera_GetRightVector()->x * (-4.5f) -  Camera_GetUpVector()->x * 3.4f,
		Camera_GetPosition()->y + Camera_GetFrontVector()->y * 10.0f + Camera_GetRightVector()->y * (-4.5f) -  Camera_GetUpVector()->y * 3.4f,
		Camera_GetPosition()->z + Camera_GetFrontVector()->z * 10.0f + Camera_GetRightVector()->z * (-4.5f) -  Camera_GetUpVector()->z * 3.4f,
		1.91f, 1.2f, 0, 0, 191, 120);


	Billboard_SetColor(g_Alpha[7]);
	Billboard_DrawAnimationNonZBuffer(g_TextureIDNo,
		Camera_GetPosition()->x + Camera_GetFrontVector()->x * 10.0f + Camera_GetRightVector()->x * 5.5f - Camera_GetUpVector()->x * 3.5f,
		Camera_GetPosition()->y + Camera_GetFrontVector()->y * 10.0f + Camera_GetRightVector()->y * 5.5f - Camera_GetUpVector()->y * 3.5f,
		Camera_GetPosition()->z + Camera_GetFrontVector()->z * 10.0f + Camera_GetRightVector()->z * 5.5f - Camera_GetUpVector()->z * 3.5f,
		1.48f, 1.21f, 0, 0, 148, 121);
	Billboard_SetColor(g_Alpha[8]);
	Billboard_DrawAnimationNonZBuffer(g_TextureIDArrow,
		Camera_GetPosition()->x + Camera_GetFrontVector()->x * 10.0f + Camera_GetRightVector()->x * (g_ArrowBackToRight + g_ArrowRightOffSet) - Camera_GetUpVector()->x * 3.5f,
		Camera_GetPosition()->y + Camera_GetFrontVector()->y * 10.0f + Camera_GetRightVector()->y * (g_ArrowBackToRight + g_ArrowRightOffSet) - Camera_GetUpVector()->y * 3.5f,
		Camera_GetPosition()->z + Camera_GetFrontVector()->z * 10.0f + Camera_GetRightVector()->z * (g_ArrowBackToRight + g_ArrowRightOffSet) - Camera_GetUpVector()->z * 3.5f,
		1.0f, 0.5f, 0, 0, 905, 274);

	Billboard_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
}
void Pause_Final() 
{

}

void PauseAnimation()
{
	g_PauseMoving = true;
	g_BoardSpeed = 0.5f;
}