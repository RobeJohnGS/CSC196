#pragma once
#include "Framework/Actor.h"

class Bullet : public::JREngine::Actor {
public:
	Bullet() = default;
	Bullet(const JREngine::Model& model, const JREngine::Transform& transform, float damage = 1) : Actor{ model, transform }, m_dmg{ damage }{}

	void Update() override;
	void OnCollision(Actor* other) override;

	float getDamage() {
		return m_dmg;
	}
private:
	float m_dmg = 1.0f;

	float m_speed = 200;
	float m_lifespan = 5;
};