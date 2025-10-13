#pragma once

#include "Razel/Renderer/Buffer.h"
#include "Razel/Renderer/Shader.h"
#include "Razel/Renderer/Texture.h"
#include "Razel/Renderer/VertexArray.h"
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

namespace Razel
{
	constexpr auto MAX_BONE_INFLUENCE = 4; //限制了单个顶点最多可以受到多少个骨骼的影响
	// 顶点属性数据
	struct VertexData
	{
		glm::vec3 Position;                  //位置
		glm::vec3 Normal;                    //法线
		glm::vec2 TexCoords;                 //纹理坐标
		glm::vec3 Tangent;                   //切线
		glm::vec3 Bitangent;                 //副切线
		int m_BoneIDs[MAX_BONE_INFLUENCE];   //影响该顶点的骨骼的 ID
		float m_Weights[MAX_BONE_INFLUENCE]; //存储每个骨骼对该顶点的权重（影响力）
	};

	// 纹理数据
	struct TextureData
	{
		Ref<Texture2D> Texture;
		std::string Type;
		std::string Path;
	};

	// 表示一个 3D 网格模型
	class Mesh
	{
	public:
		//网格数据
		std::vector<VertexData> m_Vertices;
		std::vector<uint32_t> m_Indices;
		std::vector<TextureData> m_Textures;

		Mesh(std::vector<VertexData> vertices, std::vector<uint32_t> indices, std::vector<TextureData> textures);

		void Draw(Ref<Shader> shader);

	private:
		// 渲染数据
		Ref<VertexArray> m_VertexArray;

	private:
		void setupMesh();
	};
} // namespace Razel