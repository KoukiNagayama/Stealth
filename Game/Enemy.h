#pragma once

class Player;
#include "EnemyPath.h"

class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	int GetState()
	{
		return state;
	}
	void SetPosition(const Vector3& position) {
		m_position = position;
	}
	void SetScale(const Vector3& scale) {
		m_scale = scale;
	}
	void SetRotation(const Quaternion& rotation) {
		m_rotation = rotation;
	}
	void SetEnemyNumber(const int enemyNumber) {
		m_enemyNumber = enemyNumber;
	}
private:
	void Move();
	void Rotation();
	void SearchPlayer();
	void PlayAnimation();

	Player*        m_player;
	EnemyPath      m_enemypath;
	ModelRender    m_modelRender;
	Vector3        m_position;
	Vector3        m_toPlayer;
	Quaternion     m_rotation;
	Vector3        m_scale;
	Point*         m_point;
	Vector3        m_moveVector;
	AnimationClip  m_animationClips[1];
	bool           m_isSearchPlayer = false;
	SphereCollider m_sphereCollider;

	int m_enemyNumber = 0;
	int state;
};

