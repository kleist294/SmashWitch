


/*============================================================

　　　　　　　　　　　パーティクルの制御

============================================================*/


#include"d3dx9.h"
#include "TextureManager.h"
#include "GameParticle.h"


static int g_TextureIDParticleDrop = INVALID_TEXTURE_ID;
static int g_TextureIDParticleBomb = INVALID_TEXTURE_ID;

static Particle* g_Particle[MAX_PARTICLE];





/*============================================================
　　　　　　　　　　　パーティクル制御の初期化
============================================================*/
void GameParticleEmitter_Init()
{
	g_TextureIDParticleDrop = Texture_SetTextureLoadFile("asset\\texture\\bullet000.png");
	g_TextureIDParticleBomb = Texture_SetTextureLoadFile("asset\\texture\\bullet002.png");

	if (Texture_Load() > 0)
	{
		MessageBox(NULL, "Direct3Dテクスチャの取得に失敗しました！！！", "エラー", MB_OK | MB_ICONHAND);
	}

	for (int i = 0; i < MAX_PARTICLE; i++) {
		g_Particle[i] = new Particle;
	}




}

/*============================================================
　　　　　　　　　　　パーティクル制御のアップデート
============================================================*/
void GameParticleEmitter_Update()
{
	for (int i = 0; i < MAX_PARTICLE; i++) {
		if (g_Particle[i]->GetIsEnable())
			g_Particle[i]->ParticleStatus();
	}
	//GameParticleEmitter_Spawn({ 0.0f,0.5f,0.0f }, 0);
}

/*============================================================
　　　　　　　　　　　パーティクルの描画を制御する
============================================================*/
void GameParticleEmitter_Draw()
{
	for (int i = 0; i < MAX_PARTICLE; i++) {
		if (g_Particle[i]->GetIsEnable())
			g_Particle[i]->ParticleDraw();
	}
}
void GameParticleEmitter_Final()
{

}

/*============================================================
　　　　　　　　　　　パーティクルの生成を制御する
============================================================*/
void GameParticleEmitter_Spawn(D3DXVECTOR3 Pos,int TextureID,float size,float speed)
{
	for (int i = 0; i < MAX_PARTICLE; i++) {
		if (g_Particle[i]->GetIsEnable()) continue;

		g_Particle[i]->ParticleSpawn(Pos,TextureID,size,speed);
		break;
	}
}

/*============================================================
　　　　　　パーティクル制御のテクスチャを決める
============================================================*/
int GetParticleModelID(int textureID)
{
	switch (textureID)
	{
	case 0:
		return g_TextureIDParticleDrop;
		break;
	case 1:
		return g_TextureIDParticleBomb;
		break;
	}
}

