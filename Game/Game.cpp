#include "stdafx.h"
#include "Game.h"

#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "Enemy.h"
#include "Lever.h"
#include "Door.h"


bool Game::Start()
{
	//レベル
	//読み込み
	m_levelRender.Init("Assets/level3D/stage1.tkl",[&](LevelObjectData& objData)
	{
		//プレイヤーキャラクター
		if (objData.EqualObjectName(L"player") == true) {
			m_player = NewGO<Player>(0, "player");
			m_player->SetPosition(objData.position);
			m_player->SetScale(objData.scale);
			m_player->SetRotation(objData.rotation);
			return true;
		}
		//ステージ
		else if (objData.EqualObjectName(L"stage1") == true) {
			m_backGround = NewGO<BackGround>(0, "backGround");
			m_backGround->SetPosition(objData.position);
			m_backGround->SetScale(objData.scale);
			m_backGround->SetRotation(objData.rotation);
			return true;
		}
		//エネミー
		else if (objData.EqualObjectName(L"enemy") == true) {
			m_enemy = NewGO<Enemy>(0, "enemy");
			m_enemy->SetPosition(objData.position);
			m_enemy->SetScale(objData.scale);
			m_enemy->SetRotation(objData.rotation);
			m_enemy->SetEnemyNumber(objData.number);
			return true;
		}
		//レバー
		else if (objData.ForwardMatchName(L"lever") == true) {
			auto lever = NewGO<Lever>(0, "lever");
			lever->SetPosition(objData.position);
			lever->SetScale(objData.scale);
			lever->SetRotation(objData.rotation);
			m_leverVector.push_back(lever);
			lever->SetLeverNumber(objData.number);
			return true;
		}
		//ドア
		else if (objData.ForwardMatchName(L"door") == true) {
			auto door = NewGO<Door>(0, "door");
			door->SetPosition(objData.position);
			door->SetScale(objData.scale);
			door->SetRotation(objData.rotation);
			m_doorVector.push_back(door);
			door->SetDoorNumber(objData.number);
			return true;
		}
		return true;
	});
	
	//カメラ
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	return true;
}

void Game::Update()
{
	UpdateFont();
}

void Game::UpdateFont()
{
	m_enemy = FindGO<Enemy>("enemy");

	wchar_t lookPlayer[256];
	swprintf_s(lookPlayer, 256, L"視界:%d",m_enemy->GetState());
	m_enemyStateFont.SetText(lookPlayer);
	m_enemyStateFont.SetPosition(Vector3(-600.0f, 320.0f, 0.0f));
	m_enemyStateFont.SetScale(1.0f);
	m_enemyStateFont.SetColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Game::Render(RenderContext& rc)
{
	m_enemyStateFont.Draw(rc);
}