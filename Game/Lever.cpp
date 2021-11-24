#include "stdafx.h"
#include "Lever.h"

#include "Door.h"

#include "collision/CollisionObject.h"

Lever::Lever()
{

}

Lever::~Lever()
{
	DeleteGO(m_collisionObject);
}

bool Lever::Start()
{
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/lever/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Push].Load("Assets/animData/lever/push.tka");
	m_animationClips[enAnimationClip_Push].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Pull].Load("Assets/animData/lever/pull.tka");
	m_animationClips[enAnimationClip_Pull].SetLoopFlag(false);

	m_modelRender.Init("Assets/modelData/lever/lever.tkm", m_animationClips, enAnimationClip_Num);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);

	m_collisionObject = NewGO<CollisionObject>(0);
	m_collisionObject->CreateBox(m_position, m_rotation, Vector3::One * 70.0f);
	m_collisionObject->SetName("lever");
	m_collisionObject->SetIsEnableAutoDelete(false);

	return true;
}

void Lever::Update()
{
	PlayAnimation();

	ManageState();

	m_modelRender.Update();
}

void Lever::ProcessTransitionPushState()
{
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_lever");

	for (auto collision : collisions)
	{
		if (collision->IsHit(m_collisionObject) == true)
		{
			m_leverState = enLeverState_Push;

		}
	}

}

void Lever::ProcessTransitionPullState()
{
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_lever");

	for (auto collision : collisions)
	{
		if (collision->IsHit(m_collisionObject) == true)
		{
			m_leverState = enLeverState_Pull;
		}
	}
}

void Lever::PlayAnimation()
{
	switch (m_leverState)
	{
	case enLeverState_Idle:
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
	case enLeverState_Push:
		m_modelRender.PlayAnimation(enAnimationClip_Push);
		break;
	case enLeverState_Pull:
		m_modelRender.PlayAnimation(enAnimationClip_Pull);
		break;
	default:
		break;
	}
}

void Lever::ProcessTransitionPushIdleState()
{
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		auto doors = FindGOs<Door>("door");

		for (auto door : doors)
		{
			if (m_leverNumber == door->GetDoorNumber())
			{
				door->NotifyOpen();
				m_leverState = enLeverState_Push_Idle;
				break;
			}
		}
	}
}

void Lever::ProcessTransitionPullIdleState()
{
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		auto doors = FindGOs<Door>("door");
		for (auto door : doors)
		{
			if (m_leverNumber == door->GetDoorNumber())
			{
				door->NotifyClose();
				m_leverState = enLeverState_Pull_Idle;
				break;
			}
		}
	}
}

void Lever::ProcessIdleStateTransition()
{
	ProcessTransitionPushState();
}

void Lever::ProcessPushStateTransition()
{
	ProcessTransitionPushIdleState();
}

void Lever::ProcessPushIdleStateTransition()
{
	ProcessTransitionPullState();
}

void Lever::ProcessPullStateTransition()
{
	ProcessTransitionPullIdleState();
}

void Lever::ProcessPullIdleStateTransition()
{
	ProcessTransitionPushState();
}

void Lever::ManageState()
{
	switch (m_leverState)
	{
	case enLeverState_Idle:
		ProcessIdleStateTransition();
		break;
	case enLeverState_Push:
		ProcessPushStateTransition();
		break;
	case enLeverState_Push_Idle:
		ProcessPushIdleStateTransition();
		break;
	case enLeverState_Pull:
		ProcessPullStateTransition();
		break;
	case enLeverState_Pull_Idle:
		ProcessPullIdleStateTransition();
		break;
	default:
		break;
	}
}

void Lever::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
