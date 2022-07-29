#include "Scene.h"
#include <algorithm>

namespace JREngine {
	void Scene::Update(){

		auto iter = m_actors.begin();
		while (iter != m_actors.end()) {
			(*iter)->Update();
			if ((*iter)->m_destroy) {
				//delete &iter;
				iter = m_actors.erase(iter);
			}
			else {
				iter++;
			}
		}
	}

	void Scene::Draw(Renderer& renderer){
		for (auto& actor : m_actors) {
			actor->Draw(renderer);
		}
	}
	
	void Scene::Add(std::unique_ptr<Actor> actor){
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
	}
}