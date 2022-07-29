#include "SpaceShooter.h"
#include "Player.h"
#include "Enemy.h"
#include "Engine.h"
#include <memory>
#include <iostream>



void SpaceShooter::Initialize()
{
	m_scene = std::make_unique<JREngine::Scene>(this);

	//Create assets
	//Add audio files
	JREngine::audioSystem_g.AddAudio("lazer", "temp-lazer.wav");
	JREngine::audioSystem_g.AddAudio("explode", "temp-explode.wav");
	JREngine::audioSystem_g.AddAudio("background", "background-music.mp3");
	
	//Add text/font
	m_font = std::make_unique<JREngine::Font>("Fonts/Vonique_64.ttf", 36);
	m_titleText = std::make_unique<JREngine::Text>(m_font.get());
	m_titleText->Create(JREngine::renderer_g, "HAZRE", { 255, 0, 0, 255 });
	m_scoreText = std::make_unique<JREngine::Text>(m_font.get());
	m_scoreText->Create(JREngine::renderer_g, "000000", { 255, 0, 0, 255 });

	// Transform
	JREngine::Transform transform;
	transform.position = { 400, 300 };
	transform.rotation = 0;
	transform.scale = 5;

	std::unique_ptr<Player> player = std::make_unique<Player>(JREngine::Model{ "Player.txt" }, transform);
	player->GetTag() = "player";
	m_scene->Add(std::move(player));

	for (int i = 0; i < 5; i++) {
		transform.position.x = JREngine::Randomf(800);
		transform.position.y = JREngine::Randomf(600);
		transform.rotation = JREngine::Randomf(Math::twoPi);
		std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(JREngine::Model{ "Enemy.txt" }, transform);
		enemy->GetTag() = "enemy";
		m_scene->Add(std::move(enemy));
	}
}

void SpaceShooter::Shutdown(){

}

void SpaceShooter::Update(){

	m_spawnTimer -= JREngine::time_g.deltaTime;
	if (m_spawnTimer <= 0) {
		m_spawnTimer = 2;

		JREngine::Transform transform;

		transform.position.x = JREngine::Randomf(800);
		transform.position.y = JREngine::Randomf(600);
		transform.rotation = JREngine::Randomf(Math::twoPi);
		transform.scale = 3;
		std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(JREngine::Model{ "Enemy.txt" }, transform);
		m_scene->Add(std::move(enemy));
	}

	m_scene->Update();

	//update score
	m_scoreText->Create(JREngine::renderer_g, "Score: " + std::to_string(m_score), {255, 255, 255, 255});
}

void SpaceShooter::Draw(JREngine::Renderer& renderer){
	m_scene->Draw(renderer);
	m_titleText->Draw(renderer, { 370, 100 });
	m_scoreText->Draw(renderer, { 10, 10 });
}

