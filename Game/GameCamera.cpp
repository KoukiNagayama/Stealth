#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera() {

}

GameCamera::~GameCamera() {

}

bool GameCamera::Start() {
	m_toCameraPos.Set(-50.0f, 30.0f, 0.0f);
	m_player = FindGO<Player>("player");

	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(10000.0f);

	return true;
}

void GameCamera::Update() {
	target = m_player->GetPosition();
	target.y += 30.0f;

	Vector3 toCameraPosOld = m_toCameraPos;

	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();

	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 1.3f * x);
	qRot.Apply(m_toCameraPos);

	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 1.3f * y);
	qRot.Apply(m_toCameraPos);

	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -2.0f) {
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.9f) {
		m_toCameraPos = toCameraPosOld;
	}

	Vector3 position = target + m_toCameraPos;

	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(position);

	g_camera3D->Update();
}
