#pragma once
#ifndef MYDIRECT3D_H_
#define MYDIRECT3D_H_

//Direct3D9の初期化

//戻り値 失敗したらfalse
bool MyDirect3D_Init(HWND hWnd);



//Direct3D9の終了処理
void MyDirect3D_Final(void);


//Direct3Dデバイスの取得
LPDIRECT3DDEVICE9 MyDirect3D_GetDevice(void);
//アクセサー



#endif