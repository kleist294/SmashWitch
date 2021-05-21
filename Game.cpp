
/*============================================================

　　　　　　ゲーム本体の制御

============================================================*/


#include <windows.h> 
#include <d3d9.h>
#include <d3dx9.h>
#include "config.h"
#include "Cube.h"
#include "game.h"
#include "mydirect3d.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "DebugFont.h"
#include "keyboard.h"
#include "keylogger.h"
#include "math.h"
#include "score.h"
#include "sound.h"
#include "scene.h"
#include "fade.h"
#include "Grid.h"
#include "Camera.h"
#include "MeshField.h"
#include "Wall.h"
#include "model_x.h"
#include "GamePlayerManager.h"
#include "GameEnemyManager.h"
#include "GamePlayerBullet.h"
#include "Billboard.h"
#include "Skybox.h"
#include "Shadow.h"
#include "GameCursor.h"
#include "GameJudgement.h"
#include "DropEffect.h"
#include "GameHammer.h"
#include "GameBombManager.h"
#include "GameBulletMode.h"
#include "GameHitEffect.h"
#include "GamePlayerHP.h"
#include "GameEffect.h"
#include "GamePause.h"
#include "GameWaveAnime.h"
#include "GameWaveFont.h"
#include "GameBikuri.h"
#include "GameParticleEmitter.h"
#include "Mouse.h"
#include "GameFloor.h"
#include "GameTree.h"
#include "GameGrass.h"
#include "GameStone.h"
#include "GameRadar.h"


#define WALK_ANIME_FRAME 13
#define STAND_ANIME_FRAME 15


/*============================================================
　　　　　　グローバル変数
============================================================*/
static int g_textureID = INVALID_TEXTURE_ID;
static int g_textureIDkobeni = INVALID_TEXTURE_ID;
static int g_score = 0;
static int g_countteki = 0;

static int g_result = 0;




static int mode = 0;
static float g_SizeX = 0;
static float g_SizeY = 0;
static float g_PosX = 0;
static float g_PosY = 0.1f;
static int g_wireframe = 0;

static int g_mesh_x = MESH_X;
static int g_mesh_z = MESH_Z;

static int g_b = false;

static int g_xmodel_grad = INVALID_MODEL_X_ID;
static int g_xmodel_cart = INVALID_MODEL_X_ID;

static int g_billboardId = INVALID_TEXTURE_ID;

static D3DXVECTOR3 g_vector = {0.0f,0.0f,0.0f};
static D3DXVECTOR3 g_dir = { 0.0f,0.0f,0.0f };

static bool g_flag_camera = false;

static bool IsPause = false;
static bool IsRestart = false;
static bool IsBackToTitle = false;

static Mouse_State g_MouseState;

static float CurSorX = 0;
static float CurSorY = 0;


typedef enum GameMode_tag
{

	GAMEFADE_IN,
	GAMESHOW,
	GAMEFADE_OUT,
	GAME_MAX
}GameMode;


static GameMode g_GameMode = GAMEFADE_IN;





/*============================================================
　　　　　　ゲーム本体の初期化
============================================================*/
void Game_Init()
{
	

	g_GameMode = GAMEFADE_IN;
	PlaySound(SOUND_LABEL_BGM000);

	g_mesh_x = MESH_X;
	g_mesh_z = MESH_Z;

	IsPause = false;
	IsRestart = false;
	IsBackToTitle = false;
	GameScore_Init(5, true, false);
	Cube_Init();
	Model_X_Init();
	GameFloor_Init();
	Camera_Init();
	
	GameTree_Init();
	GameGrass_Init();
	GamePlayer_Init();
	GameEnemy_Init();
	GameBombManager_Init();
	GameStone_Init();
	SkyBox_Init();
	Billboard_Init();
	GameJudgement_Init();
	DropEffect_Init();
	GameHammer_Init();
	GameHitEffect_Init();
	GameBulletMode_Init();
	GameWaveAnime_Init();
	Effect_Init();
	GameRadar_Init();
	GameCursor_Init();
	GamePlayerHP_Init();
	Pause_Init();
	GameWaveFont_Init();
	GameBikuri_Init();
	GameParticleEmitter_Init();
	
	

	MeshField_Init(g_mesh_z, g_mesh_x, MESHSIZE, MESHSIZE);
	Wall_Init(WALL_Z, WALL_X, WALLSIZE, WALLSIZE);

	GameBullet_Init();
	ShadowInit();
	if (Texture_Load() > 0)
	{
		MessageBox(NULL, "Direct3Dテクスチャの取得に失敗しました！！！", "エラー", MB_OK | MB_ICONHAND);
	}
	Grid_Init(1.0f,10,D3DCOLOR_RGBA(32,255,32,255));
	g_score = 0;
	g_countteki = 0;
	g_result = 2;
	g_wireframe = 0;
	//Keylogger_RecordStart(60 * 60 * 2);
	//Keylogger_RecordLoad();
	//Keylogger_RecordPlay();
	Fade_Start(FADE_IN, 0.0f, 0.0f, 0.0f, 60);

	Mouse_SetMode(MOUSE_POSITION_MODE_RELATIVE);

}


/*============================================================
　　　　　　ゲーム本体のアップデート
============================================================*/
void Game_Update()
{

	Mouse_GetState(&g_MouseState);

	CurSorX = g_MouseState.x;
	CurSorY = g_MouseState.y;


	if (KeyloggerTrigger(KL_CANCEL))
	{
		PauseAnimation();
		PlaySound(SOUND_LABEL_SE_PAUSE);
		if (IsPause == false)
		{
			
			IsPause = true;
			Mouse_SetMode(MOUSE_POSITION_MODE_ABSOLUTE);

			Mouse_SetVisible(true);
		}
		else if (IsPause == true)
		{
			IsPause = false;
			
			Mouse_SetVisible(false);
			Mouse_SetMode(MOUSE_POSITION_MODE_RELATIVE);
			
		}
	}

	if (IsPause == false) {
		D3DXVECTOR3 playerDir = { 0.0f,0.0f,0.0f };
		//プレイヤーに移動方向を渡す

		Camera_Update();
		if (KeyloggerPress(KL_UP))
		{
			D3DXVECTOR3 front = *Camera_GetFrontVector();
			front.y = 0.0f;
			playerDir += front;
			GamePlayerAccelerate();
		}
		if (KeyloggerPress(KL_DOWN))
		{
			D3DXVECTOR3 front = *Camera_GetFrontVector();
			front.y = 0.0f;
			playerDir -= front;
			GamePlayerAccelerate();
		}
		if (KeyloggerPress(KL_LEFT))
		{
			playerDir -= *Camera_GetRightVector();
			GamePlayerAccelerate();
		}
		if (KeyloggerPress(KL_RIGHT))
		{
			playerDir += *Camera_GetRightVector();
			GamePlayerAccelerate();
		}


		GamePlayerSetDir(D3DXVec3Normalize(&playerDir, &playerDir));


		if (KeyloggerTrigger(KL_CANCEL))
		{
			//Keylogger_RecordEnd();
			//Scene_Change(SCENE_RESULT);
		}
		if (KeyloggerTrigger(KL_WIREFRAME_MODE))
		{
			if (g_wireframe == 0)
			{
				g_wireframe = 1;
			}
			else if (g_wireframe == 1)
			{
				g_wireframe = 0;
			}
		}

		//GameEnemySpawner_Update();
		Cube_Update();
		Effect_Update();
		GameTree_Update();
		GamePlayer_Update();
		GameGrass_Update();
		GameBullet_Update();
		GameEnemy_Update();
		GameJudgement_Update();
		GameHitEffect_Update();
		GamePlayerHP_Update();
		GameWaveAnime_Update();
		GameWaveFont_Update();
		GameBikuri_Update();
		GameRadar_Update();
		GameBombManager_Update();
		GameFloor_Update();
		GameScore_Update();
		GameParticleEmitter_Update();
		//if (g_result == 3)
		//{
		//	Scene_Change(SCENE_RESULT);
		//}



		
		Billboard_SetViewMatrix(Camera_GetViewMatrix());


		if (GetDeadEnemyCount() >= 26)
		{
			switch (g_GameMode)
			{
			case GAMEFADE_IN:
				if (!Fade_IsFade())
				{
					g_GameMode = GAMESHOW;
				}
				break;
			case GAMESHOW:
				//Title_Key = 1;
				g_GameMode = GAMEFADE_OUT;
				Fade_Start(FADE_OUT, 0.0f, 0.0f, 0.0f, 60);

				break;
			case GAMEFADE_OUT:
				if (!Fade_IsFade())
				{
					Scene_Change(SCENE_RESULT);
				}
				break;
			}
		}

		if (GetPlayerHP() <= -1)
		{
			switch (g_GameMode)
			{
			case GAMEFADE_IN:
				if (!Fade_IsFade())
				{
					g_GameMode = GAMESHOW;
				}
				break;
			case GAMESHOW:
				//Title_Key = 1;
				g_GameMode = GAMEFADE_OUT;
				Fade_Start(FADE_OUT, 0.0f, 0.0f, 0.0f, 60);

				break;
			case GAMEFADE_OUT:
				if (!Fade_IsFade())
				{
					Scene_Change(SCENE_RESULTLOSE);
				}
				break;
			}
		}
	}
	
	if (IsRestart == true)
	{

		switch (g_GameMode)
		{
		case GAMEFADE_IN:
			if (!Fade_IsFade())
			{
				g_GameMode = GAMESHOW;
			}
			break;
		case GAMESHOW:
			//Title_Key = 1;
			g_GameMode = GAMEFADE_OUT;
			Fade_Start(FADE_OUT, 0.0f, 0.0f, 0.0f, 60);

			break;
		case GAMEFADE_OUT:
			if (!Fade_IsFade())
			{
				Scene_Change(SCENE_GAME);
				SceneOffSet();
			}
			break;
		}
	}
	if (IsBackToTitle == true)
	{
		switch (g_GameMode)
		{
		case GAMEFADE_IN:
			if (!Fade_IsFade())
			{
				g_GameMode = GAMESHOW;
			}
			break;
		case GAMESHOW:
			//Title_Key = 1;
			g_GameMode = GAMEFADE_OUT;
			Fade_Start(FADE_OUT, 0.0f, 0.0f, 0.0f, 60);

			break;
		case GAMEFADE_OUT:
			if (!Fade_IsFade())
			{
				Scene_Change(SCENE_TITLE);
			}
			break;
		}
	}

	GameCursor_Update();
	Pause_Update();

}


/*============================================================
　　　　　　ゲーム本体の描画
============================================================*/
void Game_Draw()
{

	float x = SCREEN_WIDTH - 7 * 32.0f;
	float y = 64.0f;

	Camera_SetMatrixToDevice();

	

	D3DXMATRIX mtxworld1, mtxSkyBox,mtxSkyBoxT,mtxSkyBoxScale,
		       mtxWallWorld1, mtxWallWorld2, mtxWallWorld3, mtxWallWorld4,
		       mtxWallT,mtxWallRX, mtxWallRY, mtxT22,mtxS;

	GameFloor_Draw();


	D3DXMatrixTranslation(&mtxSkyBoxT, 3.0f, 3.0f, 0.0f);
	D3DXMatrixScaling(&mtxSkyBoxScale, 250.0f, 250.0f, 250.0f);
	mtxSkyBox = mtxSkyBoxScale * mtxSkyBoxT;
	SkyBox_Draw(&mtxSkyBox);

	
	/*
	char teki[64];
	g_countteki = 10;

	sprintf(teki, "HP : %d", g_countteki);

	DebugFontDraw(450, 20, teki);
	*/
	GameTree_Draw();
	GameGrass_Draw();
	GameStone_Draw();
	GameBombManager_Draw();	
	GamePlayer_Draw();
	GameEnemy_Draw();
	GameHitEffect_Draw();
	GameBullet_Draw();
	Effect_Draw();
	GamePlayerHP_Draw();
	GameRadar_Draw();
	GameWaveFont_Draw();
	GameWaveAnime_Draw();

	GameParticleEmitter_Draw();
	GameScore_Draw(x, y);
	Pause_Draw();

	//ポーズ状態
	if(IsPause == true)
	GameCursor_Draw();
	//FPS 表示
	//char buf[64];
	//sprintf(buf, "X : %.2f  Y : %.2f", CurSorX, CurSorY);
	//
	////この行を実行したらバグ
	//DebugFontDraw(0, 0, buf);
	
}

/*============================================================
　　　　　　ゲーム本体の描画
============================================================*/
void Game_Final(void)
{
	StopSound(SOUND_LABEL_BGM000);
	Effect_Final();
	Model_x_ReleaseAll();
	SkyBox_Final();
	Sprite_Final();
}

int Get_Result()
{
	return g_result;
}

bool GetPlaymode()
{
	return g_b;
}

bool GetIsPause()
{
	return IsPause;
}

void PauseCancel()
{
	PauseAnimation();
	Mouse_SetMode(MOUSE_POSITION_MODE_RELATIVE);
	playerStopAttack();
    IsPause = false;
}

void GameRestart()
{
	IsRestart = true;
}

void GameBackToTitle()
{
	IsBackToTitle = true;

}

bool GetIsRestart()
{
	return IsRestart;
}

float GetCursorX()
{
	return CurSorX;
}

float GetCursorY()
{
	return CurSorY;
}