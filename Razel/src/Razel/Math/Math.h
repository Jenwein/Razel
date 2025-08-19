#pragma once

#include <glm/glm.hpp>

namespace Razel::Math
{
	// �ֽ�任����
	bool DecomposeTransform(const glm::mat4& transform,
		glm::vec3& translation,
		glm::vec3& rotation,
		glm::vec3& scale);

}

