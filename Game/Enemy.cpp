#include "stdafx.h"
#include "Enemy.h"

#include "Player.h"
#include "EnemyPath.h"

namespace
{
	const float SERACH_PLAYER_DISTANCE = 1000.0f;
	const float SERACH_PLAYER_ANGLE = 0.25f;

}


Enemy::Enemy() {

}

Enemy::~Enemy() {

}

bool Enemy::Start() {

	m_animationClips[0].Load("Assets/animData/enemy/walk.tka");
	m_animationClips[0].SetLoopFlag(true);

	m_modelRender.Init("Assets/modelData/enemy/Alex.tkm",m_animationClips,1);
	m_player = FindGO<Player>("player");

	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);

	m_enemypath.Init("Assets/path/enemypath1.tkl");
	m_point = m_enemypath.GetFirstPoint();

	m_sphereCollider.Create(1.0f);
	
	return true;
}


void Enemy::Update() {

	SearchPlayer();

	Move();

	Rotation();

	PlayAnimation();
	
	m_modelRender.Update();

}

void Enemy::Move() {
	Vector3 diff = m_point->s_position - m_position;
	if (diff.Length() <= 30.0f) {
		if (m_point->s_number == m_enemypath.GetPointListSize()-1) {
			m_point = m_enemypath.GetFirstPoint();
		}
		else {
			m_point = m_enemypath.GetNextPoint(m_point->s_number);
		}
	
	}
	Vector3 moveSpeed = m_point->s_position - m_position;
	moveSpeed.Normalize();
	m_moveVector = moveSpeed;
	moveSpeed *= 1.0f;
	m_position += moveSpeed;

	m_modelRender.SetPosition(m_position);
}

struct SweepResultWall :public btCollisionWorld::ConvexResultCallback {
	bool isHit = false;

	virtual btScalar  addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace) {
		if (convexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Wall) {
			return 0.0f;
		}
		isHit = true;
		return 0.0f;
	}
};


void Enemy::SearchPlayer() {
	m_isSearchPlayer = false;
	Vector3 playerPosition = m_player->GetPosition();

	m_toPlayer = playerPosition - m_position;
	if (m_toPlayer.Length() < SERACH_PLAYER_DISTANCE) {
		m_toPlayer.Normalize();

		float angle = acosf(m_toPlayer.Dot(m_moveVector));
		if (Math::PI * SERACH_PLAYER_ANGLE <= fabsf(angle)) {
			state = 0;
			return;
		}

		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		start.setOrigin(btVector3(m_position.x, m_position.y + 70.0f, m_position.z));
		end.setOrigin(btVector3(playerPosition.x, playerPosition.y + 70.0f, playerPosition.z));

		SweepResultWall callback;

		PhysicsWorld::GetInstance()->ConvexSweepTest((const btConvexShape*)m_sphereCollider.GetBody(), start, end, callback);

		if (callback.isHit == true) {
			state = 0;
			return;
		}

		m_isSearchPlayer = true;
		state = 1;
	}
}

void Enemy::PlayAnimation() {
	m_modelRender.PlayAnimation(0);
}

void Enemy::Rotation() {
	
	m_moveVector.y = 0.0f;
	m_rotation.SetRotationYFromDirectionXZ(m_moveVector);
	m_modelRender.SetRotation(m_rotation);
	
}

void Enemy::Render(RenderContext& rc) {

	m_modelRender.Draw(rc);

}
