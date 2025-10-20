#include "rzpch.h"

#include "Model.h"
#include "Renderer.h"

#include <filesystem> 

namespace Razel
{
	Model::Model(const std::string& path, bool flipUVs, bool gamma)
		: m_GammaCorrection(gamma)
	{
		LoadModel(path, flipUVs);
	}

	void Model::Draw(Ref<Shader> shader)
	{
		for (auto& mesh : m_Meshes)
		{
			mesh.Draw(shader);
		}
	}

	void Model::LoadModel(const std::string& path, bool flipUVs)
	{
		Assimp::Importer importer;
		unsigned int processFlags =
			aiProcess_Triangulate |
			aiProcess_GenSmoothNormals |
			aiProcess_CalcTangentSpace;
		if (flipUVs)
		{
			processFlags |= aiProcess_FlipUVs;
		}
		const aiScene* scene = importer.ReadFile(path, processFlags);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			RZ_CORE_ERROR("ASSIMP ERROR: {0}", importer.GetErrorString());
			return;
		}

		m_Directory = std::filesystem::path(path).parent_path().string();
		processNode(scene->mRootNode, scene);
	}

	void Model::processNode(aiNode* node, const aiScene* scene)
	{
		for (size_t i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_Meshes.push_back(processMesh(mesh, scene));
		}

		for (size_t i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}

	Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<VertexData> vertices;
		std::vector<uint32_t> indices;
		std::vector<TextureData> textures;

		vertices.reserve(mesh->mNumVertices);
		for (size_t i = 0; i < mesh->mNumVertices; i++)
		{
			VertexData vertex;
			vertex.Position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };

			if (mesh->HasNormals())
			{
				vertex.Normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
			}

			if (mesh->mTextureCoords[0])
			{
				vertex.TexCoords = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
			}
			else
			{
				vertex.TexCoords = { 0.0f, 0.0f };
			}

			if (mesh->HasTangentsAndBitangents())
			{
				vertex.Tangent = { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z };
				vertex.Bitangent = { mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z };
			}
			// Bone data can be processed here if needed
			// ...

			vertices.push_back(vertex);
		}

		for (size_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (size_t j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			std::vector<TextureData> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

			std::vector<TextureData> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

			std::vector<TextureData> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
			textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

			std::vector<TextureData> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
			textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
		}

		return Mesh(vertices, indices, textures);
	}

	std::vector<TextureData> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
	{
		std::vector<TextureData> textures;
		for (size_t i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			bool skip = false;

			// Check if texture was loaded before
			for (const auto& loadedTexture : m_TexturesLoaded)
			{
				if (std::strcmp(loadedTexture.Path.data(), str.C_Str()) == 0)
				{
					textures.push_back(loadedTexture);
					skip = true;
					break;
				}
			}

			if (!skip)
			{
				// If texture hasn't been loaded already, load it
				std::filesystem::path fullPath = std::filesystem::path(m_Directory) / std::filesystem::path(str.C_Str());

				TextureData textureData;
				textureData.Texture = Texture2D::Create(fullPath.string());
				textureData.Type = typeName;
				textureData.Path = str.C_Str();
				textures.push_back(textureData);
				m_TexturesLoaded.push_back(textureData);
			}
		}
		return textures;
	}

} // namespace Razel