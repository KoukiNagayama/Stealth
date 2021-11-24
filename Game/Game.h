#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class BackGround;
class GameCamera;
class Enemy;
class Lever;
class Door;

class Game : public IGameObject
{
public:
	Game() {}
	~Game() {}
	bool Start();
	void Update();
	void UpdateFont();
	void Render(RenderContext& rc);

private:
	Player*             m_player;
	BackGround*         m_backGround;
	GameCamera*         m_gameCamera;
	Enemy*              m_enemy;
	std::vector<Lever*> m_leverVector;
	std::vector<Door*>  m_doorVector;
	ModelRender         m_modelRender;
	FontRender          m_enemyStateFont;
	LevelRender         m_levelRender;
};

