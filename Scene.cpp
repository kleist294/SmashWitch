
/*============================================================

　　　　　　　シーンの制御

============================================================*/


#include <d3d9.h>
#include <d3dx9.h>
#include "Sprite.h"
#include "Keyboard.h"
#include "Keylogger.h"
#include "TextureManager.h"
#include "Mydirect3d.h"
#include "Sound.h"
#include "Scene.h"
#include "Sousa.h"
#include "Game.h"
#include "Title.h"
#include "Result.h"
#include "ResultLose.h"


static e_Scene g_NowScene = SCENE_TITLE;//現在のシーン設置(デバッグ用)
static e_Scene g_Next_Scene = g_NowScene;

//関数のアドレス表記
//unsigned int a = (unsigned int)Scene_Init;
//関数が括弧をつけると関数を実行すると判断する

//     戻り値                  引数の型
typedef void (*SceneFunction)(void);

static const SceneFunction g_pSceneInit[] =
{
	Title_Init,
	Sousa_Init,
	Game_Init,
	Result_Init,
	ResultLose_Init
};

static const SceneFunction g_pSceneUpdate[] =
{
	Title_Update,
	Sousa_Update,
	Game_Update,
	Result_Update,
	ResultLose_Update
};

static const SceneFunction g_pSceneDraw[] =
{
	Title_Draw,
	Sousa_Draw,
	Game_Draw,
	Result_Draw,
	ResultLose_Draw
};

static const SceneFunction g_pSceneFinal[] =
{
	Title_Final,
	Sousa_Final,
	Game_Final,
	Result_Final,
	ResultLose_Final
};

void Scene_Init() 
{
	g_pSceneInit[g_NowScene]();

}
void Scene_Update()
{
	g_pSceneUpdate[g_NowScene]();
}

void Scene_Draw()
{
	g_pSceneDraw[g_NowScene]();
}
void Scene_Final(void)
{
	g_pSceneFinal[g_NowScene]();
}

void Scene_Change(e_Scene nextscene)
{
	g_Next_Scene = nextscene;
}
void Scene_ExecuteChange()
{
	//今のシーンと次のシーンがちがうものだったら
	if (g_NowScene == g_Next_Scene)return;
	

	//現在のシーン終了する
	Scene_Final();

	//現在のシーンを次のシーンにする
	g_NowScene = g_Next_Scene;

	//現在のシーンを初期化する
	Scene_Init();
}

e_Scene GetNowScene()
{
	return g_NowScene;
}

void SceneOffSet()
{
	g_NowScene = SCENE_TITLE;
}