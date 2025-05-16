#pragma once

#include <glm/glm.hpp>

namespace Razel::Math
{
	// �ֽ�任����
	bool DecomposeTransform(const glm::mat4& transform,
		glm::vec3& outTranslation,
		glm::vec3& outRotation,
		glm::vec3& outScale);

}

