#include "Player.h"
#include "Engine.h"
#include "Bullet.h"
#include <iostream>

void Player::Update()
{
	//Rotate
	if (JREngine::inputSystem_g.onKeyLeft(JREngine::InputSystem::KeyState::Held)) {
		//transform_.rotation -= (3.0f * JREngine::time_g.deltaTime);
		transform_.position.x -= (maxSpeed_ * JREngine::time_g.deltaTime);
	}

	if (JREngine::inputSystem_g.onKeyRight(JREngine::InputSystem::KeyState::Held)) {
		//transform_.rotation += (3.0f * JREngine::time_g.deltaTime);
		transform_.position.x += (maxSpeed_ * JREngine::time_g.deltaTime);
	}

	//Move
	if (JREngine::inputSystem_g.onKeyUp(JREngine::InputSystem::KeyState::Held)) {
		transform_.position.y -= (maxSpeed_ * JREngine::time_g.deltaTime);
	}

	if (JREngine::inputSystem_g.onKeyDown(JREngine::InputSystem::KeyState::Held)) {
		transform_.position.y += (maxSpeed_ * JREngine::time_g.deltaTime);
	}

	if (JREngine::inputSystem_g.GetButtonState(JREngine::buttonLeft) == JREngine::InputSystem::KeyState::Pressed) {
		JREngine::Transform transform = transform_;
		transform.scale = 1;
		std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(JREngine::Model{ "bullet.txt" }, transform);
		bullet->GetTag() = "player";
		m_scene->Add(std::move(bullet));
		JREngine::audioSystem_g.PlayAudio("lazer");
	}

	// Mouse
	//if (Engine::inputSystem_g.GetButtonState(Engine::button_right) == Engine::InputSystem::KeyState::Pressed)
	//{
	//	std::cout << "Mouse Position: (" << Engine::inputSystem_g.GetMousePosition().x << ", " << inputSystem.GetMousePosition().y << ")" << endl;
	//}

	// Face Target
	JREngine::Vector2 target = JREngine::inputSystem_g.GetMousePos();
	target = target - transform_.position; // Direction Vector Towards
	transform_.rotation = target.GetAngle();

	// Thrust Code
	JREngine::Vector2 direction{ 1,0 };
	direction = JREngine::Vector2::Rotate(direction, transform_.rotation);

	JREngine::Vector2 force = direction * speed_ * JREngine::time_g.deltaTime;

	m_velocity += force;

	m_velocity *= 1.0f / (1.0f + m_damping * JREngine::time_g.deltaTime);
	//transform_.position += m_velocity * JREngine::time_g.deltaTime;

	if (transform_.position.x > JREngine::renderer_g.GetWidth_()) {
		transform_.position.x = 0;
	}
	if (transform_.position.x < 0) {
		transform_.position.x = (float)JREngine::renderer_g.GetWidth_();
	}

	if (transform_.position.y > JREngine::renderer_g.GetWidth_()) {
		transform_.position.y = 0;
	}
	if (transform_.position.y < 0) {
		transform_.position.y = (float)JREngine::renderer_g.GetHeight_();
	}
}

void Player::OnCollision(Actor* other)
{
	if (dynamic_cast<Bullet*>(other) && other->GetTag() == "enemy") {
		m_health -= dynamic_cast<Bullet*>(other)->getDamage();
		if (m_health <= 0) {
			m_destroy = true;
			//play destroy sound
		}
	}
}
