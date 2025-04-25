#pragma once

#include <glm/glm.hpp>
#include "SceneCamera.h"
namespace Razel
{
	struct TagComponent
	{
		std::string Tag;
		glm::mat4 Transform{ 1.0f };
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			:Tag(tag)
		{
		}
	};

	struct TransformComponent
	{
		glm::mat4 Transform{ 1.0f };
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			:Transform(transform)
		{ }

		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () const { return Transform; }
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f ,1.0f, 1.0f, 1.0f };
		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			:Color(color)
		{}
	};

	struct CameraComponent
	{
		Razel::SceneCamera Camera;

		// 是否是主相机
		bool Primary = true;			//TODO: 考虑移动到Scene中
		bool FixedAspectRadio = false;	//固定宽高比


		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};
}
