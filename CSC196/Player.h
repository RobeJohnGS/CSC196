#pragma once
#include "Framework/Actor.h"

class Player : public JREngine::Actor
{
public:
	Player() = default;
	Player(const JREngine::Model& model, const JREngine::Transform& transform) : Actor(model, transform) {}

	void Update() override;
	void OnCollision(Actor* other) override;

	float m_health = 5;

private:
	float speed_{ 0 };
	float maxSpeed_{ 250 };
};
