#include "Actor.h"

namespace JREngine
{
	void Actor::Draw(Renderer& renderer)
	{
		m_model.Draw(renderer, transform_.position, transform_.rotation, transform_.scale);
	}
}
