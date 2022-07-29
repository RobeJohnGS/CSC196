#include "Model.h"
#include "../Core/File.h"

#include <iostream>
#include <sstream>

namespace JREngine
{
	void Model::Draw(Renderer& renderer, const Vector2& position, float angle, float scale)
	{

		for (int i = 0; i < points_.size() - 1; i++)
		{
			Vector2 p1 = Vector2::Rotate((points_[i] * scale), angle) + position;
			Vector2 p2 = Vector2::Rotate((points_[i + 1] * scale), angle) + position;
			renderer.DrawLine(p1, p2, color_);
		}
	}

	void Model::Load(const std::string& filename)
	{
		std::string buffer;
		JREngine::ReadFile(filename, buffer);

		std::istringstream stream(buffer);
		stream >> color_;

		std::string line;
		std::getline(stream, line);
		size_t numPoints = std::stoi(line);

		for (size_t i = 0; i < numPoints; i++)
		{
			Vector2 point;

			stream >> point;
			points_.push_back(point);
		}
	}

	float Model::CalculateRadius()
	{
		float radius = 0;

		for (auto& point : points_) {
			if (point.Length() > radius) {
				radius = point.Length();
			}
		}

		return radius;
	}

	Model::Model(const std::string& filename)
	{
		Load(filename);
		m_radius = CalculateRadius();
		std::cout << m_radius << std::endl;
	}
}