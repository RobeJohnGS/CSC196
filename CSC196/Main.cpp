#include "Player.h"
#include "Enemy.h"
#include "Engine.h"
#include "SpaceShooter.h"

using namespace std;

int main()
{
	//Memory Init
	JREngine::InitializeMemory();

	JREngine::SetFilePath("../Assets");

	//Initialize Engine
	JREngine::renderer_g.Initialize();
	JREngine::inputSystem_g.Initialize();
	JREngine::audioSystem_g.Initialize();

	// Create A Window And Set Background Color
	JREngine::renderer_g.CreateWindow("Engine", 800, 600); // Creates the window with parameters
	JREngine::renderer_g.SetClearColor(JREngine::Color{ 255, 125, 125, 255 });

	{
		SpaceShooter game;
		game.Initialize();



		//Update Loop
		bool quit = false;
		while (!quit)
		{
			// Update
			JREngine::time_g.Tick();
			JREngine::inputSystem_g.Update();
			JREngine::audioSystem_g.Update();

			if (JREngine::inputSystem_g.onKeyEsc(JREngine::InputSystem::KeyState::Pressed)) {
				quit = true;
			}

			//Update Game Objects
			game.Update();

			// Render
			JREngine::renderer_g.BeginFrame();

			game.Draw(JREngine::renderer_g);

			JREngine::renderer_g.EndFrame();
		}
	}

	JREngine::audioSystem_g.Shutdown();
	JREngine::renderer_g.Shutdown();
}
