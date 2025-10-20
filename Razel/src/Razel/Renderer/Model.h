#pragma once

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "Mesh.h"
#include "Shader.h"
#include <string>
#include <vector>

namespace Razel
{
	// 加载和管理 3D 模型
	class Model
	{
	public:
		Model(const std::string& path, bool flipUVs = true, bool gamma = false);
		void Draw(Ref<Shader> shader);

	private:
		std::vector<Mesh> m_Meshes;                 // 模型的各个网格部分
		std::vector<TextureData> m_TexturesLoaded; // 存储已加载的纹理,避免重复加载
		std::string m_Directory;                    // 模型文件所在的目录路径
		bool m_GammaCorrection;                     // 是否进行gamma矫正

	private:
		void LoadModel(const std::string& path, bool flipUVs);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<TextureData> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
	};
} // namespace Razel