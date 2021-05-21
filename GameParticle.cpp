
/*============================================================

　　　　　　　　　　　パーティクル

============================================================*/

#include"d3dx9.h"
#include "MeshField.h"
#include "TextureManager.h"
#include "GameParticle.h"
#include "Billboard.h"

Particle::Particle()
{
	m_ParticlePos = {0.0f,0.0f,0.0f};
	m_ParticleDir = {0.0f,0.0f,0.0f};
	m_IsEnable = false;
	m_Gravity = 0.15f;
}

Particle::~Particle()
{

}

/*============================================================
　　　　　　　　　　　パーティクルの生成
============================================================*/
void Particle::ParticleSpawn(D3DXVECTOR3 Pos,int textureID,float Size,float Speed)
{
	m_ParticleModelID = GetParticleModelID(textureID);
	m_ParticlePos = Pos;
	m_Gravity = 0.1f;
	m_ParticleDir = { (float)(rand() % 21 - 10) ,(float)(rand() % 21),(float)(rand() % 21 - 10) };
	m_IsEnable = true;
	m_Size = Size;
	m_Speed = Speed;
}

/*============================================================
　　　　　　　　　　　パーティクルの状態
============================================================*/
void Particle::ParticleStatus()
{


	D3DXVec3Normalize(&m_ParticleDir, &m_ParticleDir);

	m_ParticlePos += m_ParticleDir * 0.2f;
	m_ParticlePos.y -= m_Gravity;
	m_Gravity *= 1.03f;

	if (m_ParticlePos.y <= 0.0f)
	{
		m_IsEnable = false;
	}


}


/*============================================================
　　　　　　　　　　　パーティクルの描画
============================================================*/
void Particle::ParticleDraw()
{
	if (m_IsEnable == true) {
		if (m_ParticleModelID == GetParticleModelID(0))
		Billboard_SetColor(D3DCOLOR_RGBA(180,113,66,255));

		Billboard_Draw(m_ParticleModelID, m_ParticlePos.x, m_ParticlePos.y, m_ParticlePos.z, m_Size, m_Size, 1.0f);
		Billboard_SetColor(D3DCOLOR_RGBA(255,255,255, 255));
	}
}

/*============================================================
　　　　　　　　　　　パーティクルの存在を取得
============================================================*/
bool Particle::GetIsEnable()
{
	return m_IsEnable;
}

/*============================================================
　　　　　　　　　　　パーティクルの重力を設置
============================================================*/
void Particle::SetGravity(float g)
{
	m_Gravity = g;
}


