


/*============================================================

�@�@�@�@�@�@�@�@�@�@�@�p�[�e�B�N���̐���

============================================================*/


#include"d3dx9.h"
#include "TextureManager.h"
#include "GameParticle.h"


static int g_TextureIDParticleDrop = INVALID_TEXTURE_ID;
static int g_TextureIDParticleBomb = INVALID_TEXTURE_ID;

static Particle* g_Particle[MAX_PARTICLE];





/*============================================================
�@�@�@�@�@�@�@�@�@�@�@�p�[�e�B�N������̏�����
============================================================*/
void GameParticleEmitter_Init()
{
	g_TextureIDParticleDrop = Texture_SetTextureLoadFile("asset\\texture\\bullet000.png");
	g_TextureIDParticleBomb = Texture_SetTextureLoadFile("asset\\texture\\bullet002.png");

	if (Texture_Load() > 0)
	{
		MessageBox(NULL, "Direct3D�e�N�X�`���̎擾�Ɏ��s���܂����I�I�I", "�G���[", MB_OK | MB_ICONHAND);
	}

	for (int i = 0; i < MAX_PARTICLE; i++) {
		g_Particle[i] = new Particle;
	}




}

/*============================================================
�@�@�@�@�@�@�@�@�@�@�@�p�[�e�B�N������̃A�b�v�f�[�g
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
�@�@�@�@�@�@�@�@�@�@�@�p�[�e�B�N���̕`��𐧌䂷��
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
�@�@�@�@�@�@�@�@�@�@�@�p�[�e�B�N���̐����𐧌䂷��
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
�@�@�@�@�@�@�p�[�e�B�N������̃e�N�X�`�������߂�
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

