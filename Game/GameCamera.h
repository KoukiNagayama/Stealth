#pragma once
class Player;

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

private:
	Player* m_player;
	Vector3 m_toCameraPos;
	Vector3 target;
};

