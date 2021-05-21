#pragma once
#ifndef MODEL_X_H_
#define MODEL_X_H_

#include <d3dx9.h>


//無効なXモデル管理番号
#define INVALID_MODEL_X_ID -1

void Model_X_Init();

void Model_X_Final();
//Xファイルの読み込み
//
//戻り値：整理番号
//
int Model_X_Load(const char *pFileName);

//モデルの解放
//
//引数：pIDs...解放したいモデル整理番号が入ったメモリー領域の先頭
//      count...解放したいモデル整理番号の個数
void Model_x_Release(const int *pIDs,int count);
void Model_x_ReleaseAll();

//モデルの描画
void Model_X_Draw(int ID, D3DXMATRIX *mtxmodel);
LPD3DXMESH* Model_X_GetMesh(int index);

#endif