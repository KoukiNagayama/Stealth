#include "stdafx.h"
#include "Player.h"

Player::Player() {

}

Player::~Player() {

}

bool Player::Start() {
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/human/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/human/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);
	

	m_modelRender.Init("Assets/modelData/human/Martha.tkm",m_animationClips,enAnimationClip_Num);
	m_charaCon.Init(10.0f,30.0f,m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetPosition(m_position);
	return true;
}

void Player::Update() {

	Move();

	Rotation();

	ManageState();

	PlayAnimation();

	m_modelRender.Update();
}

void Player::Move() {

	m_moveSpeed.x = 0.0f;
	m_moveSpeed.y = 0.0f;
	m_moveSpeed.z = 0.0f;

	Vector3 LStick;
	LStick.x = g_pad[0]->GetLStickXF();
	LStick.y = g_pad[0]->GetLStickYF();

	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	forward.y = 0.0f;
	right.y = 0.0f;

	right *= LStick.x * 100.0f;
	forward *= LStick.y * 100.0f;

	m_moveSpeed += right + forward;

	m_position = m_charaCon.Execute(m_moveSpeed, 1.0f / 60.0f);

	m_modelRender.SetPosition(m_position);
	
}

void Player::Rotation() {
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		m_modelRender.SetRotation(m_rotation);

		m_forward = Vector3::AxisZ;
		m_rotation.Apply(m_forward);
	}
}

void Player::ManageState() {
	if (fabsf(m_moveSpeed.x)>=0.001f || fabsf(m_moveSpeed.z)>=0.001f){
		m_playerState = 1;
	}
	else if (g_pad[0]->IsTrigger(enButtonA)) {
		m_playerState = 2;
		MakePushLeverCollision();
	}
	else {
		m_playerState = 0;
	}
}

void Player::PlayAnimation() {
	switch (m_playerState) {
	case 0:
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
	case 1:
		m_modelRender.PlayAnimation(enAnimationClip_Run);
		break;
	}
}

void Player::MakePushLeverCollision()
{
	CollisionObject* collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_position;
	collisionPosition += m_forward * 50.0f;
	collisionObject->CreateSphere(collisionPosition,
		Quaternion::Identity,
		70.0f);
	collisionObject->SetName("player_lever");
}

void Player::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}
