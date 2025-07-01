#include "rzpch.h"
#include "Razel/Renderer/Renderer2D.h"
#include "Razel/Renderer/VertexArray.h"
#include "Razel/Renderer/Shader.h"
#include "Razel/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Razel
{
	// �ı��ζ�������
	struct QuadVertex
	{
		glm::vec3 Position;		// λ��
		glm::vec4 Color;		// ��ɫ
		glm::vec2 TexCoord;		// ��������
		float TexIndex;			// ��������
		float TilingFactor;	// ƽ������,��ֵԽ��,�����ظ�չʾ�Ĵ���Խ��
	};

	// ��Ⱦ����
	struct Renderer2DData
	{
		static const uint32_t MaxQuads = 10000;						// ÿ���������Ⱦ����,�����������µĻ��Ƶ���
		static const uint32_t MaxVertices = MaxQuads * 4;			// ��󶥵���
		static const uint32_t MaxIndices = MaxQuads * 6;			// ���������
		static const uint32_t MaxTextureSlots = 32;					// ����������(TODO:RenderCaps)

		Ref<VertexArray> QuadVertexArray;							// �ı��ζ�������
		Ref<VertexBuffer> QuadVertexBuffer;							// �ı��ζ��㻺������
		
		Ref<Shader> TextureShader;									// ������ɫ��
		Ref<Texture2D> WhiteTexture;								// Ĭ�ϰ�ɫ����
		
		uint32_t QuadIndexCount = 0;								// ��¼��ǰ�������Ѿ���ӵ���������
		QuadVertex* QuadVertexBufferBase = nullptr;					// �洢��ǰ�����������ı��εĶ������ݡ�
		QuadVertex* QuadVertexBufferPtr = nullptr;					// ָ�� QuadVertexBufferBase �е�ǰд��λ�õ�ָ��
	
		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;	// �洢��ǰ�󶨵����� ID
		uint32_t TextureSlotIndex = 1;								// ׷����һ�����õ������λ��(������������ĩβλ��)��Ĭ�ϵ� 0 �����Ϊ��ɫ����
	
		glm::vec4 QuadVertexPositions[4] = {};						// �ı����ĸ�����λ��
		Renderer2D::Statistics Stats;								// ͳ����Ⱦ

	};

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		RZ_PROFILE_FUNCTION();

		s_Data.QuadVertexArray = VertexArray::Create();
		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));

		s_Data.QuadVertexBuffer->SetLayout({
			{ShaderDataType::Float3, "a_Position" },
			{ShaderDataType::Float4, "a_Color" },
			{ShaderDataType::Float2, "a_TexCrood" },
			{ShaderDataType::Float,  "a_TexIndex" },
			{ShaderDataType::Float,  "a_TilingFactor" }
		});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];	
		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];		// ���ڴ洢��������
		
		uint32_t offset = 0;	// ׷�ٵ�ǰ������ı��ε���ʼ��������
		// Ԥ���������п��ܵ�����,ÿ��ѭ��������һ���ı���,Ҳ���������������������������˳��
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;		// ׷���ı��εĶ�����ʼ����
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[]quadIndices;

		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		// ��ʼ������������ɫ������(0~31)
		int32_t samplers[s_Data.MaxTextureSlots];
		for (uint32_t i = 0;i < s_Data.MaxTextureSlots;i++)
		{
			samplers[i] = i;
		}

		s_Data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetIntArray("u_Textures", samplers,s_Data.MaxTextureSlots);
		// ���õ�һ�������Ϊ0
		s_Data.TextureSlots[0] = s_Data.WhiteTexture;				

		s_Data.QuadVertexPositions[0] = { -0.5, -0.5, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[1] = {  0.5, -0.5, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[2] = {  0.5,  0.5, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[3] = { -0.5,  0.5, 0.0f, 1.0f };

	}

	void Renderer2D::Shutdown()
	{
		RZ_PROFILE_FUNCTION();
		delete[] s_Data.QuadVertexBufferBase;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		RZ_PROFILE_FUNCTION();

		// �����������
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		StartBatch();
	}	

	void Renderer2D::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
		RZ_PROFILE_FUNCTION();

		glm::mat4 viewProj = camera.GetProjection() * glm::inverse(transform);

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", viewProj);

		StartBatch();

	}

	void Renderer2D::BeginScene(const EditorCamera& camera)
	{
		RZ_PROFILE_FUNCTION();

		glm::mat4 viewProj = camera.GetViewProjection();

		// �����������
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", viewProj);

		StartBatch();

	}

	void Renderer2D::EndScene()
	{
		RZ_PROFILE_FUNCTION();

		Flush();	//ʵ�ʵ���DrawCall
	}

	void Renderer2D::Flush()
	{
		if (s_Data.QuadIndexCount == 0)
			return; // Nothing to draw


		uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);		// �ϴ�VB��OpenGL

		// ������
		for (uint32_t i = 0;i < s_Data.TextureSlotIndex;i++)
		{
			s_Data.TextureSlots[i]->Bind(i);
		}

		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
		s_Data.Stats.DrawCalls++;
	}

	void Renderer2D::StartBatch()
	{
		// ����������״̬
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		// ���ٵ�ǰ���һ������λ��(ĩβ)
		s_Data.TextureSlotIndex = 1;
	}

	void Renderer2D::NextBatch()
	{
		Flush();
		StartBatch();
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{

		DrawQuad({ position.x,position.y,0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		RZ_PROFILE_FUNCTION();

		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x , size.y,1.0f });

		DrawQuad(transform, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		RZ_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, color);
	}

	void Renderer2D::DrawQuad(const glm::mat4 transform, glm::vec4 color)
	{
		RZ_PROFILE_FUNCTION();

		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		constexpr size_t quadVertexCount = 4;
		const float textureIndex = 0.0f;		// ��ɫ����
		const float tilingFactor = 1.0f;	// ƽ������

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
		{
			NextBatch();
		}

		for (uint32_t i = 0; i < quadVertexCount; ++i)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;
		s_Data.Stats.QuadCount++;
	}


	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor /*= 1.0f*/, const glm::vec4& tintColor /*= glm::vec4(1.0f)*/)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor /*= 1.0f*/, const glm::vec4& tintColor /*= glm::vec4(1.0f)*/)
	{
		RZ_PROFILE_FUNCTION();

		// �����ı��ε��ĸ�����,������������
		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x , size.y,1.0f });

		DrawQuad(transform, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		RZ_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, texture, tilingFactor, tintColor);

	}

	void Renderer2D::DrawQuad(const glm::mat4 transform, const Ref<Texture2D>& texture, float tilingFactor /*= 1.0f*/, const glm::vec4& tintColor /*= glm::vec4(1.0f)*/)
	{
		RZ_PROFILE_FUNCTION();

		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		constexpr size_t quadVertexCount = 4;
		//constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };	// Ĭ�ϰ�ɫ�����ڳ�������ı�,����Ϊconstexpr�����δ���
		float textureIndex = 0.0f;								// ������ǰ����λ��

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
		{
			NextBatch();
		}

		// ��������Ƿ��Ѿ�������s_Data.TextureSlots��
		for (uint32_t i = 1; i < s_Data.TextureSlotIndex;++i)
		{
			if (*s_Data.TextureSlots[i] == *texture)
			{
				// ����Ѵ���,����������ָ�������λ��
				textureIndex = (float)i;
				break;
			}
		}

		// ���µ�������
		if (textureIndex == 0.0f)		// �������δ��
		{
			if (s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
			{
				NextBatch();
			}

			textureIndex = (float)s_Data.TextureSlotIndex;			// ���µ�ǰ����������λ��
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;	// �󶨵��ò�
			s_Data.TextureSlotIndex++;								// ���������¼λ��
		}


		for (uint32_t i = 0; i < quadVertexCount; ++i)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = tintColor;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;
		s_Data.Stats.QuadCount++;

	}


	void Renderer2D::ResetStats()
	{
		memset(&s_Data.Stats, 0, sizeof(Statistics));
	}

	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return s_Data.Stats;
	}

}