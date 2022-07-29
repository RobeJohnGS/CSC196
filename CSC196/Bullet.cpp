#include "Bullet.h"
#include "Player.h"
#include "Engine.h"
#include "Enemy.h"

void Bullet::Update(){

	m_lifespan -= JREngine::time_g.deltaTime;
	if (m_lifespan <= 0) m_destroy = true;


	JREngine::Vector2 direction{ 1, 0 };
	direction = JREngine::Vector2::Rotate(direction, transform_.rotation);

	JREngine::Vector2 velocity = direction * m_speed * JREngine::time_g.deltaTime;

	transform_.position += velocity;
}

void Bullet::OnCollision(Actor* other)
{
	if (dynamic_cast<Player*>(other) && m_tag != "player")
	{
		m_destroy = true;
	}
	if (dynamic_cast<Enemy*>(other) && m_tag != "enemy")
	{
		m_destroy = true;
	}
}

