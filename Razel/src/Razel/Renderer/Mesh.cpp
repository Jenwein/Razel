#include "rzpch.h"
#include "Mesh.h"

#include "Razel/Renderer/RenderCommand.h"

namespace Razel
{
	Mesh::Mesh(std::vector<VertexData> vertices, std::vector<uint32_t> indices, std::vector<TextureData> textures)
		: m_Vertices(std::move(vertices)), m_Indices(std::move(indices)), m_Textures(std::move(textures))
	{
		setupMesh();
	}

	void Mesh::Draw(Ref<Shader> shader)
	{
		uint32_t diffuseNr = 1;
		uint32_t specularNr = 1;
		uint32_t normalNr = 1;
		uint32_t heightNr = 1;

		for (uint32_t i = 0; i < m_Textures.size(); i++)
		{
			std::string number;
			std::string name = m_Textures[i].Type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);
			else if (name == "texture_normal")
				number = std::to_string(normalNr++);
			else if (name == "texture_height")
				number = std::to_string(heightNr++);

			shader->SetInt("u_" + name + number, i);
			m_Textures[i].Texture->Bind(i);
		}

		m_VertexArray->Bind();
		RenderCommand::DrawIndexed(m_VertexArray, m_Indices.size());
		m_VertexArray->UnBind();
	}

	void Mesh::setupMesh()
	{
		m_VertexArray = VertexArray::Create();

		uint32_t bufferSize = m_Vertices.size() * sizeof(VertexData);
		Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(bufferSize);
		vertexBuffer->SetData(m_Vertices.data(), bufferSize);

		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float3, "a_Normal"},
			{ShaderDataType::Float2, "a_TexCoords"},
			{ShaderDataType::Float3, "a_Tangent"},
			{ShaderDataType::Float3, "a_Bitangent"},
			{ShaderDataType::Int4, "a_BoneIDs"},
			{ShaderDataType::Float4, "a_Weights"} };
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(m_Indices.data(), m_Indices.size());
		m_VertexArray->SetIndexBuffer(indexBuffer);
	}
}