
/*============================================================

�@�@�@�@�@�@�@�V�[���̐���

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


static e_Scene g_NowScene = SCENE_TITLE;//���݂̃V�[���ݒu(�f�o�b�O�p)
static e_Scene g_Next_Scene = g_NowScene;

//�֐��̃A�h���X�\�L
//unsigned int a = (unsigned int)Scene_Init;
//�֐������ʂ�����Ɗ֐������s����Ɣ��f����

//     �߂�l                  �����̌^
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
	//���̃V�[���Ǝ��̃V�[�������������̂�������
	if (g_NowScene == g_Next_Scene)return;
	

	//���݂̃V�[���I������
	Scene_Final();

	//���݂̃V�[�������̃V�[���ɂ���
	g_NowScene = g_Next_Scene;

	//���݂̃V�[��������������
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