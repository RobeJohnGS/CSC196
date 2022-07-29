#pragma once
#include "Renderer.h"
#include <vector>
#include <string>

namespace JREngine
{
	class Model
	{

	public:

		Model() = default;
		Model(const std::vector<Vector2>& points, const Color& color) : points_{ points }, color_{ color }{}
		Model(const std::string& filename);

		void Draw(Renderer& renderer, const Vector2& position, float angle, float scale = 1);

		void Load(const std::string& filename);

		float GetRadius() {
			return m_radius;
		}

		float CalculateRadius();
	private:

		Color color_;
		std::vector<Vector2> points_;
		float m_radius = 0;
	};
}
