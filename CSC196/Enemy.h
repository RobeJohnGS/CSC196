#pragma once
#include "Framework/Actor.h"

class Enemy : public JREngine::Actor {
public:
	Enemy() = default;
	Enemy(const JREngine::Model& model, const JREngine::Transform& transform) : Actor{ model, transform } {
		Initialize();
	}

	void Initialize();
	void Update() override;

	void OnCollision(Actor* other) override;

private:
	float m_health = 2;
	float m_speed = 50;
	
	float m_fireTimer = 10;
};