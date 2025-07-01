#include "rzpch.h"
#include "Razel/Renderer/Renderer2D.h"
#include "Razel/Renderer/VertexArray.h"
#include "Razel/Renderer/Shader.h"
#include "Razel/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Razel
{
	// 四边形顶点属性
	struct QuadVertex
	{
		glm::vec3 Position;		// 位置
		glm::vec4 Color;		// 颜色
		glm::vec2 TexCoord;		// 纹理坐标
		float TexIndex;			// 纹理索引
		float TilingFactor;	// 平铺因子,数值越大,纹理被重复展示的次数越多
	};

	// 渲染数据
	struct Renderer2DData
	{
		static const uint32_t MaxQuads = 10000;						// 每批次最大渲染数量,超过将进行新的绘制调用
		static const uint32_t MaxVertices = MaxQuads * 4;			// 最大顶点数
		static const uint32_t MaxIndices = MaxQuads * 6;			// 最大索引数
		static const uint32_t MaxTextureSlots = 32;					// 最大纹理槽数(TODO:RenderCaps)

		Ref<VertexArray> QuadVertexArray;							// 四边形顶点数组
		Ref<VertexBuffer> QuadVertexBuffer;							// 四边形顶点缓冲数组
		
		Ref<Shader> TextureShader;									// 纹理着色器
		Ref<Texture2D> WhiteTexture;								// 默认白色纹理
		
		uint32_t QuadIndexCount = 0;								// 记录当前批次中已经添加的索引数量
		QuadVertex* QuadVertexBufferBase = nullptr;					// 存储当前批次中所有四边形的顶点数据。
		QuadVertex* QuadVertexBufferPtr = nullptr;					// 指向 QuadVertexBufferBase 中当前写入位置的指针
	
		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;	// 存储当前绑定的纹理 ID
		uint32_t TextureSlotIndex = 1;								// 追踪下一个可用的纹理槽位置(标记纹理槽数组末尾位置)，默认第 0 个插槽为白色纹理。
	
		glm::vec4 QuadVertexPositions[4] = {};						// 四边形四个顶点位置
		Renderer2D::Statistics Stats;								// 统计渲染

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
		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];		// 用于存储索引数据
		
		uint32_t offset = 0;	// 追踪当前处理的四边形的起始顶点索引
		// 预先生成所有可能的索引,每次循环会设置一个四边形,也就是两个三角形六个顶点的索引顺序
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;		// 追踪四边形的顶点起始索引
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[]quadIndices;

		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		// 初始化纹理数组着色器参数(0~31)
		int32_t samplers[s_Data.MaxTextureSlots];
		for (uint32_t i = 0;i < s_Data.MaxTextureSlots;i++)
		{
			samplers[i] = i;
		}

		s_Data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetIntArray("u_Textures", samplers,s_Data.MaxTextureSlots);
		// 设置第一个纹理槽为0
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

		// 设置相机参数
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

		// 设置相机参数
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", viewProj);

		StartBatch();

	}

	void Renderer2D::EndScene()
	{
		RZ_PROFILE_FUNCTION();

		Flush();	//实际调用DrawCall
	}

	void Renderer2D::Flush()
	{
		if (s_Data.QuadIndexCount == 0)
			return; // Nothing to draw


		uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);		// 上传VB给OpenGL

		// 绑定纹理
		for (uint32_t i = 0;i < s_Data.TextureSlotIndex;i++)
		{
			s_Data.TextureSlots[i]->Bind(i);
		}

		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
		s_Data.Stats.DrawCalls++;
	}

	void Renderer2D::StartBatch()
	{
		// 重置批处理状态
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		// 跟踪当前最后一个纹理位置(末尾)
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
		const float textureIndex = 0.0f;		// 白色纹理
		const float tilingFactor = 1.0f;	// 平铺因子

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

		// 设置四边形的四个顶点,并设置其属性
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
		//constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };	// 默认白色将属于常量不会改变,设置为constexpr避免多次创建
		float textureIndex = 0.0f;								// 索引当前纹理位置

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
		{
			NextBatch();
		}

		// 检查纹理是否已经存在于s_Data.TextureSlots中
		for (uint32_t i = 1; i < s_Data.TextureSlotIndex;++i)
		{
			if (*s_Data.TextureSlots[i] == *texture)
			{
				// 如果已存在,则纹理索引指向该纹理位置
				textureIndex = (float)i;
				break;
			}
		}

		// 绑定新的纹理到槽
		if (textureIndex == 0.0f)		// 如果纹理未绑定
		{
			if (s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
			{
				NextBatch();
			}

			textureIndex = (float)s_Data.TextureSlotIndex;			// 更新当前纹理索引的位置
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;	// 绑定到该槽
			s_Data.TextureSlotIndex++;								// 更新纹理记录位置
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