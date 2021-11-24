#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround() {

}

BackGround::~BackGround() {

}

bool BackGround::Start() {
	m_modelRender.Init("Assets/modelData/stage/stage1-2.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();
	m_phyStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	m_phyStaticObject.GetbtCollisionObject()->setUserIndex(enCollisionAttr_Wall);
	return true;
}

void BackGround::Update() {

}

void BackGround::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}
