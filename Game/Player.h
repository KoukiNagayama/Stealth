#pragma once
class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void SetPosition(const Vector3& position) {
		m_position = position;
	}
	void SetScale(const Vector3& scale) {
		m_scale = scale;
	}
	const Vector3& GetPosition() const{
		return m_position;
	}
	void SetRotation(const Quaternion& rotation) {
		m_rotation = rotation;
	}

private:
	void Move();
	void Rotation();
	void ManageState();
	void PlayAnimation();
	void MakePushLeverCollision();

	ModelRender         m_modelRender;
	CharacterController m_charaCon;
	Vector3             m_position;
	Vector3             m_moveSpeed;
	Vector3             m_scale;
	Vector3             m_forward = Vector3::AxisZ;
	Quaternion          m_rotation;
	enum EnPlayerState
	{
		enAnimationClip_Idle,
		enAnimationClip_Run,
		enAnimationClip_Num
	};
	AnimationClip m_animationClips[enAnimationClip_Num];
	int m_playerState;
};

