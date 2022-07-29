#pragma once
#include "../Math/Transform.h";

namespace JREngine
{
	class GameObject
	{
	public:

		GameObject() = default;
		GameObject(const Transform& transform) : transform_{ transform } {}

		virtual void Update() = 0;

		Transform& GetTransform() { return transform_; }

		Transform transform_;
	private:

	protected:

	};
}