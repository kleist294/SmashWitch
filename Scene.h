#pragma once
#pragma once
#ifndef SCENE_H_
#define SCENE_H_

typedef enum Scene_tag
{
	SCENE_TITLE,
	SCENE_SOUSA,
	SCENE_GAME,
	SCENE_RESULT,
	SCENE_RESULTLOSE,
	SCENE_MAX,
}e_Scene;




void Scene_Init();
void Scene_Update();
void Scene_Draw();
void Scene_Final(void);

void Scene_Change(e_Scene nextscene);
void Scene_ExecuteChange();
e_Scene GetNowScene();
void SceneOffSet();

#endif