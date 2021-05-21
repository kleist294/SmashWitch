#pragma once

#ifndef GAME_PARTICLE_H_
#define GAME_PARTICLE_H_


#include "d3dx9.h"
#include "MeshField.h"
#include "TextureManager.h"
#include "GameParticleEmitter.h"


#define EDGE_X ((float)(MESH_X * MESHSIZE / 2) + 0.5f)
#define EDGE_Z ((float)(MESH_Z * MESHSIZE / 2) + 0.5f)



class Particle
{
public:

	Particle();
	~Particle();


	void ParticleDraw();
	void ParticleSpawn(D3DXVECTOR3 Pos, int textureID,float size, float speed);
	void ParticleStatus();
	bool GetIsEnable();
	void SetGravity(float g);
	


private:


	int m_ParticleModelID = INVALID_TEXTURE_ID;

	D3DXVECTOR3 m_ParticlePos;
	D3DXVECTOR3 m_ParticleDir;
	bool m_IsEnable = false;
	float m_Gravity = 0.15f;
	float m_Size = 0.0f;
	float m_Speed = 0.0f;

};



#endif