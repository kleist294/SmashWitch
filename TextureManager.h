
#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_
#include<d3d9.h>

//無効な管理番号
#define INVALID_TEXTURE_ID -1
//最大テクスチャファイル名文字数
#define TEXTURE_FILENAME_MAX 64 


void TextureInit();

void TextureFinal();



//テクチャファイルの読み込み予約
//引数pFileName ...  ファイルネーム
//戻り値：テクスチャ管理番号
//最大管理数を超えていた場合は INVALID_TEXTURE_ID
int Texture_SetTextureLoadFile(const char* pFileName);


//テクスチャの読み込み
//予約されているファイルを読み込みます
//戻り値：読み込めなかったファイル数
//        または他の不具合が発生した場合 -1
int Texture_Load();


//テクスチャの部分解放
//
//引数：textureIDs[] ... 解放したいtextureIDが入ったint型配列の先頭アドレス
//
//count : 解放するテクスチャの数
//
//int textureIDs[] => int* ptextureIDs 
void Texture_Release(int textureIDs[], int count);

//テクスチャ全解放
void Texture_AllRelease();

//テクスチャ幅と高さの取得
//戻り値：テクスチャの幅と高さ
unsigned long Texture_GetTextureWidth(int textureID);
unsigned long Texture_GetTextureHeight(int textureID);

//テクスチャインタフェースポインターの取得
//
//引数：テクスチャ管理番号
//
//戻り値：テクスチャインタフェースポインター
LPDIRECT3DTEXTURE9 Texture_GetTexture(int textureID);

#endif