#pragma once
#include "Framework/Game.h"

//Forward Declaration
namespace JREngine {
	class Font;
	class Text;
}

class SpaceShooter : public JREngine::Game {
public:
	SpaceShooter() = default;
	~SpaceShooter() = default;

	virtual void Initialize() override;
	virtual void Shutdown() override;
	virtual void Update() override;
	virtual void Draw(JREngine::Renderer& renderer) override;

protected:
	//Enemy spawn
	float m_spawnTimer = 0;

	std::unique_ptr<JREngine::Font> m_font;
	std::unique_ptr<JREngine::Text> m_titleText;
	std::unique_ptr<JREngine::Text> m_scoreText;
};