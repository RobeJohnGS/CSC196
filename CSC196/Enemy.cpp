#include "Enemy.h"
#include "Engine.h"
#include "Bullet.h"
#include "Player.h"

#include <iostream>

void Enemy::Initialize(){
	m_fireTimer = JREngine::Randomf(2, 6);
	m_speed = JREngine::Randomf(20, 100);
}

void Enemy::Update(){
	m_fireTimer -= JREngine::time_g.deltaTime;
	if (m_fireTimer <= 0) {
		m_fireTimer = JREngine::Randomf(2, 6);
		std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(JREngine::Model{ "Bullet.txt" }, transform_);
		bullet->GetTag() = "enemy";
		m_scene->Add(std::move(bullet));
	}

	Player* player = m_scene->GetActor<Player>();
	if (player) {
		JREngine::Vector2 direction = player->transform_.position - transform_.position;
		transform_.rotation = direction.GetAngle();
	}

	JREngine::Vector2 direction(1.0f, 0.0f);
	direction = JREngine::Vector2::Rotate(direction, transform_.rotation);

	m_velocity = direction * (m_speed * JREngine::time_g.deltaTime);
	transform_.position += m_velocity;

	if (transform_.position.x > JREngine::renderer_g.GetWidth_()) {
		transform_.position.x = 0;
	}
	if (transform_.position.x < 0) {
		transform_.position.x = JREngine::renderer_g.GetWidth_();
	}
	if (transform_.position.y > JREngine::renderer_g.GetHeight_()) {
		transform_.position.y = 0;
	}
	if (transform_.position.y < 0) {
		transform_.position.y = JREngine::renderer_g.GetHeight_();
	}
}

void Enemy::OnCollision(Actor* other)
{
	if (dynamic_cast<Bullet*>(other) && other->GetTag() == "player")
	{
		m_health -= dynamic_cast<Bullet*>(other)->getDamage();

		if (m_health <= 0) m_destroy = true;
	}
}
